// Path: cpp/DavinciFC/main.cpp
// Env: Ubuntu 20.04+, g++ 9.4+, C++17, POSIX
// Build (example):
//   g++ -O2 -std=gnu++17 -pthread -I../cpp -o davinci_fc ../cpp/DavinciFC/main.cpp
// Run:
//   ./davinci_fc [/dev/ttyUSB0] [/dev/ttyUSB1] [can0] [/dev/ttyUSB2] [9999]
// Docs:
//   - Linux SocketCAN: https://docs.kernel.org/networking/can.html
//   - POSIX termios:   https://man7.org/linux/man-pages/man3/termios.3.html
//   - VectorNav SDK:   https://www.vectornav.com/resources

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include <string>
#include <atomic>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

// Ensure PWM sysfs macros/arrays/helpers are available BEFORE tools.h uses them
#include "hal/MTpwm/MTpwm.h"   // provides SYSFS_PWM_DIR, pwm_chips, pwm_channels, write_sysfs
#include "tools.h"

#include "VN300/VN300.h"       // init_vn300, processSensorData

#include "fcc.h"                // FCC_Data_Print 안에서 LIHAI까지 함께 출력되도록 수정됨
#include "udp.h"              

extern "C" {
#include "UAM_Flight_control.h"
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "rtiostream.h"
FCCData_t g_fcc;
}

#ifndef rtmGetNumSampleTimes
#define rtmGetNumSampleTimes(rtm) 3
#endif

#include "SimulinkGen/fcc_mapper.h"
#include "sbus/SBUS.h"
#include "lihai/lihai.h"       // lihai_open_serial_115200, send_all_packets_serial, read_state_errors_packet20
#include "BMS/bms.h"           // open_can, UpdateBMSData_test
#include "keti/keti.h"
#include <atomic>
#include <mutex>
#include <ctime>
// ====== Device Enable Flags ======
#define ENABLE_VN300   1
#define ENABLE_SBUS    1
#define ENABLE_BMS     0
#define ENABLE_LIHAI   0
#define ENABLE_KETI    0



// --- ADD: 6채널 바이너리 프레임 (총 20바이트)
struct __attribute__((packed)) SBUS6_Frame {
    uint8_t  sync1;  // 0xAA
    uint8_t  sync2;  // 0x55
    uint8_t  ver;    // 0x01
    uint8_t  len;    // 0x0E (=14)
    uint16_t ch[6];  // roll,pitch,thr,yaw,trigger,aux (0..2047), LE
    uint8_t  flags;  // bit0: lost, bit1: failsafe
    uint8_t  seq;    // rolling
    uint16_t crc_le; // CRC16/XMODEM over [ver..seq], LE
};
static constexpr int SBUS6_FRAME_SIZE = 20;
// SBUS 입력 보호용 뮤텍스 (다른 입력 스레드와 공유한다면 보호 권장)
std::mutex g_in_mtx;
std::atomic<bool> g_run{true};


// 마지막 수신 시각(ns)과 수신 프레임 시퀀스(디버그/모니터링 용)
static std::atomic<uint64_t> g_sbus_last{0};
static std::atomic<uint64_t> g_sbus_seq{0};


// ====== Global resources ======


static int   g_lihai_fd  = -1;
static int   g_can_fd    = -1;
static int   g_sbus_fd   = -1;
static char  g_vn_port[128]    = "/dev/ttyUSB0";
static char  g_sbus_port[128]  = "/dev/ttyACM0";
static char  g_can_if[32]      = "can0";
static char  g_lihai_port[128] = "/dev/ttyUSB2";
static std::string g_keti_host = "0.0.0.0";
static uint16_t g_keti_port    = 9999;

// ====== Global thread handles ======
static pthread_t vn_thread{};
static pthread_t sbus_thread{};
static pthread_t bms_thread{};
static pthread_t lihai_tx_thread{};
static pthread_t lihai_rx_thread{};
static pthread_t keti_thread{};
static pthread_t control_thread{};

#ifndef NUMST
#define NUMST 3 // sample time count
#endif

// Simulink config
static double simTime = 0.0;
static const double stepSize = 0.005; // 200Hz

// Simulink external mode arguments
const char_T* extArgs[] = {
    "GroundTest",
    "-w",
    "-tf", "inf",
    "-hostname", "0.0.0.0",
    "-port", "17725"
};
int extArgc = sizeof(extArgs) / sizeof(extArgs[0]);

// VN-300 object
using namespace VN;
static Sensor g_sensor;
static Registers::System::BinaryOutput1 g_binOut1;

// LiHai state error buffer
// ❗ static 제거: fcc.h의 extern State_Error_t g_state_err; 과 매칭
State_Error_t g_state_err{};
static inline uint64_t now_ns() {
    timespec ts{};
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ull + (uint64_t)ts.tv_nsec;
}
static inline double sbus2047_to_us(int v2047) {
    int v = v2047;
    if (v < 172)  v = 172;
    if (v > 1810) v = 1810;
    return 1000.0 + (double)(v - 172) * (1000.0 / (1810.0 - 172.0));
}

// Utility
static inline uint16_t clamp_pwm_us(double v) {
    if (!std::isfinite(v)) return 1000;
    if (v < 1000.0) v = 1000.0;
    else if (v > 2000.0) v = 2000.0;
    return static_cast<uint16_t>(std::lround(v));
}

// ================= Threads =================

// KETI server receive thread
static void* keti_thread_fn(void*) {
    keti::Server s; std::string err;
    if (!s.open(g_keti_host, g_keti_port, &err)) {
        std::fprintf(stderr, "[KETI] open fail: %s\n", err.c_str());
        return nullptr;
    }
    std::printf("[KETI] listening %s:%u\n", g_keti_host.c_str(), g_keti_port);

    while (g_run.load()) {
        auto pkt = s.recv_once(50, &err); // timeout=50ms
        if (!pkt.has_value()) continue;

        keti::Parsed p;
        if (!keti::parse_frame(pkt->bytes, p, &err)) continue;

        if (p.is_heartbeat) {
            std::printf("HB=%u from %s:%u\n",
                        (unsigned)p.heartbeat, pkt->peer_ip.c_str(), pkt->peer_port);
        } else {
            std::printf("OBJ=%u from %s:%u\n",
                        (unsigned)p.count, pkt->peer_ip.c_str(), pkt->peer_port);
        }
    }
    return nullptr;
}

// VN-300 RX thread (400Hz)
static void* vn300_thread_fn(void*) {
    while (g_run.load()) {
        processSensorData(g_fcc, g_sensor, g_binOut1);
        usleep(2500); // 400 Hz
    }
    return nullptr;
}

// RC handling thread
static void* sbus_thread_fn(void*) {
    // g_sbus_fd는 이미 init_serial로 open됨
    // 비블로킹 read + 텍스트 섞여와도 OK 하게 링버퍼 운용
    static char  rb[4096];
    static size_t head = 0, tail = 0;       // 유효 범위: [tail, head)
    auto RB_SZ = sizeof(rb);

    auto rb_count = [&](){ return head - tail; };
    auto rb_push  = [&](char c){ rb[head++ % RB_SZ] = c; };
    auto rb_peek  = [&](size_t i){ return rb[(tail + i) % RB_SZ]; };
    auto rb_popn  = [&](size_t n){ tail += n; };

    while (g_run.load()) {
        // 1) 비블로킹 read
        char tmp[512];
        ssize_t n = ::read(g_sbus_fd, tmp, sizeof(tmp));
        if (n > 0) {
            for (ssize_t i = 0; i < n; ++i) rb_push(tmp[i]);
        }

        // 2) 먼저: 바이너리 프레임(AA 55 + 고정 20B) 추출/파싱
        while (rb_count() >= 2) {
            size_t cnt = rb_count();
            // sync 찾기
            size_t i = 0;
            for (; i + 1 < cnt; ++i) {
                if ((uint8_t)rb_peek(i) == 0xAA && (uint8_t)rb_peek(i+1) == 0x55) break;
            }
            if (i + 1 >= cnt) break;             // sync 미발견 → 더 읽기
            if (i > 0) rb_popn(i);               // sync 전 텍스트/잡음 폐기

            if (rb_count() < (size_t)SBUS6_FRAME_SIZE) break; // 덜 도착 → 다음 read

            // 프레임 복사
            uint8_t f[SBUS6_FRAME_SIZE];
            for (int k = 0; k < SBUS6_FRAME_SIZE; ++k) f[k] = (uint8_t)rb_peek(k);

            // 기본 필드 검사
            if (f[2] != 0x01 || f[3] != 0x0E) {
                rb_popn(2);                      // 버전/길이 불일치 → 재동기화
                continue;
            }
            // CRC: [ver..seq] 16바이트
            uint16_t crc_calc = crc16_xmodem(&f[2], 16);
            uint16_t crc_recv = (uint16_t)f[18] | ((uint16_t)f[19] << 8);
            if (crc_calc != crc_recv) {
                rb_popn(2);                      // CRC 불일치 → 재동기화
                continue;
            }

            // 채널 6개(LE) 읽기
            uint16_t ch_raw[6];
            for (int c = 0; c < 6; ++c) {
                int off = 4 + c * 2;
                ch_raw[c] = (uint16_t)f[off] | ((uint16_t)f[off + 1] << 8);
            }
            uint8_t flags = f[16];

            // 0..2047 → us 변환
            double rc_us[6];
            for (int c = 0; c < 6; ++c) rc_us[c] = sbus2047_to_us((int)ch_raw[c]);

            {
                std::lock_guard<std::mutex> lk(g_in_mtx);
                // 표준 맵핑: roll, pitch, throttle, yaw, trigger, aux/emergency
                g_fcc.rc[0] = rc_us[0];
                g_fcc.rc[1] = rc_us[1];
                g_fcc.rc[2] = rc_us[2];
                g_fcc.rc[3] = rc_us[3];
                g_fcc.rc[4] = rc_us[4];
                g_fcc.rc[5] = rc_us[5];

                // 링크 상태: failsafe면 0, 아니면 1
                g_fcc.rc_link = (flags & 0x02) ? 0 : 1;

                // 필요 시 fcc.h에 별도 필드 추가 후 저장 가능
                // g_fcc.rc_lost = (flags & 0x01) ? 1 : 0;
                // g_fcc.rc_failsafe = (flags & 0x02) ? 1 : 0;
            }
            g_sbus_last.store(now_ns(), std::memory_order_relaxed);
            g_sbus_seq.fetch_add(1, std::memory_order_relaxed);

            rb_popn(SBUS6_FRAME_SIZE);          // 이 프레임 소비

            // (선택) 여기서만 주기적으로 출력하고 싶다면:
            // FCC_Data_Print(&g_fcc);
        }

        // 3) 남은 텍스트 라인(예: "RX\n", " sent frame\n")은 그냥 버퍼에서 비워주자
        //    필요 없다면 주석 처리해도 무방
        while (rb_count() > 0) {
            size_t cnt = rb_count();
            size_t i = 0; bool found = false;
            for (; i < cnt; ++i) {
                if (rb_peek(i) == '\n') { found = true; break; }
            }
            if (!found) break;
            rb_popn(i + 1); // 한 줄 버림
        }

        // 너무 바쁘게 돌지 않게
        usleep(1000); // 1ms
    }
    return nullptr;
}


// BMS RX thread (20Hz)
static void* bms_thread_fn(void*) {
    while (g_run.load()) {
        UpdateBMSData_test(g_can_fd, &g_fcc);
        usleep(50 * 1000); // 20 Hz
    }
    return nullptr;
}

// LiHai TX thread (100Hz)
static void* lihai_tx_thread_fn(void*) {
    while (g_run.load()) {
        int txrc = send_all_packets_serial(g_lihai_fd, &g_fcc);
        if (txrc != 0) std::fprintf(stderr, "[LiHai] send error=%d\n", txrc);
        usleep(10 * 1000); // 100 Hz
    }
    return nullptr;
}

// LiHai RX thread (polling ~100Hz)
static void* lihai_rx_thread_fn(void*) {
    while (g_run.load()) {
        if (read_state_errors_packet20(g_lihai_fd, g_state_err, 20)) {
            // ������ 직접 출력은 제거(중복 방지). FCC_Data_Print에서 한 줄로 출력됨.
            // FCC_Errors_Print(&g_state_err);
        }
        usleep(10 * 1000);
    }
    return nullptr;
}

//  Simulink Control Thread
//  Simulink Control Thread 
static void* control_thread_fn(void*) {
    // External Mode init
    rtParseArgsForExtMode(extArgc, extArgs);

    printf("[EXT] Initializing model...\n");
    UAM_Flight_control_initialize();

    rtSetTFinalForExtMode(&rtmGetTFinal(UAM_Flight_control_M));
    rtExtModeCheckInit(NUMST);

    // -Non-blocking wait for start
    printf("[EXT] Waiting for start packet (Ctrl+C to abort)...\n");
    boolean_T stopReq = false;
    
    while (g_run.load() && !stopReq) {
        rtExtModeWaitForStartPkt(UAM_Flight_control_M->extModeInfo,
                                rtmGetNumSampleTimes(UAM_Flight_control_M),
                                &stopReq);

        if (!stopReq && !rtmGetStopRequested(UAM_Flight_control_M)) {
            // start packet recive
            break;
        }

        usleep(10000); // 10ms 
    }

    if (stopReq || !g_run.load()) {
        rtmSetStopRequested(UAM_Flight_control_M, true);
        printf("[EXT] terminated before start\n");
        UAM_Flight_control_terminate();
        rtExtModeShutdown(NUMST);
        return nullptr;
    }

    printf("[EXT] Connected! Sending start message...\n");
    rtERTExtModeStartMsg();


    // --- Control loop (200 Hz) ---
    while (g_run.load() && !rtmGetStopRequested(UAM_Flight_control_M)) {
        boolean_T rtmStopReq = false;
        rtExtModeOneStep(UAM_Flight_control_M->extModeInfo,
                         rtmGetNumSampleTimes(UAM_Flight_control_M),
                         &rtmStopReq);

        if (rtmStopReq) {
            rtmSetStopRequested(UAM_Flight_control_M, true);
            break;
        }

        // (1) Input mapping
        fcc_to_bus(&g_fcc, &UAM_Flight_control_U);
        //  printf("[IN ] roll=%.2f pitch=%.2f yaw=%.2f alt=%.2f\n",
        //          g_fcc.roll, g_fcc.pitch, g_fcc.yaw, g_fcc.altitude);

        // (2) Simulink steps
        UAM_Flight_control_step0();
        if (UAM_Flight_control_M->Timing.RateInteraction.TID0_1)
            UAM_Flight_control_step1();

        // (3) Output mapping
        bus_to_fcc(&UAM_Flight_control_Y, &g_fcc);
        // printf("[OUT] m[0..5]=%.1f %.1f %.1f %.1f %.1f %.1f\n",
        //     g_fcc.m[0], g_fcc.m[1], g_fcc.m[2],
        //     g_fcc.m[3], g_fcc.m[4], g_fcc.m[5]);

        // (4) PWM output
        for (int i = 0; i < 6; i++)
            pwm_out(i, clamp_pwm_us(g_fcc.m[i]));

        // (5) Debug
        //FCC_Data_Print(&g_fcc);

        simTime += stepSize;
        usleep(5 * 1000); // 200 Hz
    }

    // --- Termination ---
    UAM_Flight_control_terminate();
    rtExtModeShutdown(NUMST);
    std::puts("[Exit] control thread terminated.");
    return nullptr;
}


static void on_sig(int) {
    g_run = false;

    // Simulink external mode 소켓 닫기
    rtExtModeShutdown(NUMST);

    // 디바이스 포트 닫기
    if (g_sbus_fd >= 0) { close(g_sbus_fd); g_sbus_fd = -1; }
    if (g_can_fd  >= 0) { close(g_can_fd);  g_can_fd  = -1; }
    if (g_lihai_fd>= 0) { close(g_lihai_fd);g_lihai_fd= -1; }

    pwm_all_disable();
    std::puts("[Exit] signal caught, ports closed.");
}

// ================= main =================
int main(int argc, char* argv[]) {
    // 표준출력 버퍼링 정책(멀티스레드에서도 줄 단위로 바로 보이게)
    setvbuf(stdout, nullptr, _IOLBF, 0);
    setvbuf(stderr, nullptr, _IONBF, 0);

    // Parse CLI arguments
    if (argc > 1) std::snprintf(g_vn_port,   sizeof(g_vn_port),   "%s", argv[1]);
    if (argc > 2) std::snprintf(g_sbus_port, sizeof(g_sbus_port), "%s", argv[2]);
    if (argc > 3) std::snprintf(g_can_if,    sizeof(g_can_if),    "%s", argv[3]);
    if (argc > 4) std::snprintf(g_lihai_port,sizeof(g_lihai_port),"%s", argv[4]);
    if (argc > 5) g_keti_port = static_cast<uint16_t>(std::stoi(argv[5]));

    // PWM init
    if (pwm_all_init() < 0) {
        printf("[PWM] init failed\n");
        return -1;
    }

   // usleep(1500000); // 1.5sec wattion
    for(int i = 0; i < 6; i++)
    pwm_out(i, 1000);    // min pwm
    usleep(1500000);

    // === Start sensor/IO threads ===
    #if ENABLE_VN300
        if (init_vn300(g_vn_port, g_sensor, g_binOut1) != 0) {
            std::fprintf(stderr, "[VN300] init error\n");
            return -2;
        }
        std::puts("[VN300] ready.");
        pthread_create(&vn_thread, nullptr, vn300_thread_fn, nullptr);
    #endif

    #if ENABLE_SBUS
        g_sbus_fd = init_serial(g_sbus_port, 230400); // SBUS.h 안의 init_serial 사용
        if (g_sbus_fd < 0) {
            std::fprintf(stderr, "[SBUS] open fail\n");
            return -5;
        }
        std::printf("[SBUS] %s opened (BINARY mode).\n", g_sbus_port);
        pthread_create(&sbus_thread, nullptr, sbus_thread_fn, nullptr);
    #endif

    #if ENABLE_BMS
        g_can_fd = open_can(std::string(g_can_if));
        if (g_can_fd < 0) {
            std::fprintf(stderr, "[CAN] open fail\n");
            return -4;
        }
        int flags = fcntl(g_can_fd, F_GETFL, 0);
        fcntl(g_can_fd, F_SETFL, flags | O_NONBLOCK);
        std::printf("[CAN] %s opened.\n", g_can_if);
        pthread_create(&bms_thread, nullptr, bms_thread_fn, nullptr);
    #endif

    #if ENABLE_LIHAI
        g_lihai_fd = lihai_open_serial_115200(g_lihai_port);
        if (g_lihai_fd < 0) {
            std::fprintf(stderr, "[LiHai] open fail\n");
            return -3;
        }
        std::printf("[LiHai] %s opened.\n", g_lihai_port);
        pthread_create(&lihai_tx_thread, nullptr, lihai_tx_thread_fn, nullptr);
        pthread_create(&lihai_rx_thread, nullptr, lihai_rx_thread_fn, nullptr);
    #endif

    #if ENABLE_KETI
        pthread_create(&keti_thread, nullptr, keti_thread_fn, nullptr);
    #endif
    udp_start();
    // === Start control thread ===
    pthread_create(&control_thread, nullptr, control_thread_fn, nullptr);

    // === Wait for threads ===
    pthread_join(control_thread, nullptr);
    g_run = false;
    udp_stop(); 

    #if ENABLE_VN300
        pthread_join(vn_thread, nullptr);
        g_sensor.disconnect();
    #endif
    #if ENABLE_SBUS
        pthread_join(sbus_thread, nullptr);
        if (g_sbus_fd >= 0) close(g_sbus_fd);
    #endif
    #if ENABLE_BMS
        pthread_join(bms_thread, nullptr);
        if (g_can_fd >= 0) close(g_can_fd);
    #endif
    #if ENABLE_LIHAI
        pthread_join(lihai_tx_thread, nullptr);
        pthread_join(lihai_rx_thread, nullptr);
        if (g_lihai_fd >= 0) close(g_lihai_fd);
    #endif
    #if ENABLE_KETI
        pthread_join(keti_thread, nullptr);
    #endif

    pwm_all_disable();
    std::puts("[Exit] devices closed, process terminated.");
    return 0;
}
