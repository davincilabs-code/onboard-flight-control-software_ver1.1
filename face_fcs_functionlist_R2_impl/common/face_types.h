#ifndef FACE_TYPES_H
#define FACE_TYPES_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    FACE_OK = 0,
    FACE_ERR = -1
} FaceStatus;

typedef enum {
    FLIGHT_MODE_MANUAL = 0,
    FLIGHT_MODE_AUTO = 1,
    FLIGHT_MODE_EMERGENCY = 2
} FlightMode;

typedef enum {
    FLIGHT_PHASE_GROUND = 0,
    FLIGHT_PHASE_TAKEOFF,
    FLIGHT_PHASE_HOVER,
    FLIGHT_PHASE_TRANSITION,
    FLIGHT_PHASE_CRUISE,
    FLIGHT_PHASE_LAND,
    FLIGHT_PHASE_RTL
} FlightPhase;

typedef struct {
    double roll_rad;
    double pitch_rad;
    double yaw_rad;
    double p_rad_s;
    double q_rad_s;
    double r_rad_s;
    double ax_m_s2;
    double ay_m_s2;
    double az_m_s2;
} AhrsSample;

typedef struct {
    double lat_deg;
    double lon_deg;
    double alt_m;
    double vn_m_s;
    double ve_m_s;
    double vd_m_s;
    bool   fix_ok;
} GpsSample;

typedef struct {
    double airspeed_m_s;
    bool   ok;
} AirDataSample;

typedef struct {
    double alt_m;
    bool   ok;
} RaltSample;

typedef struct {
    // Raw I/O inputs (normalized -1..1) for demo
    double stick_roll;
    double stick_pitch;
    double stick_yaw;
    double stick_throttle; // 0..1
    int    mode_switch;    // 0 manual, 1 auto, 2 emergency
} PilotInput;

typedef struct {
    // Estimated navigation state
    double x_m;
    double y_m;
    double z_m;      // altitude positive up
    double vx_m_s;
    double vy_m_s;
    double vz_m_s;
    double roll_rad;
    double pitch_rad;
    double yaw_rad;
} NavState;

typedef struct {
    // Guidance targets
    double x_ref_m;
    double y_ref_m;
    double z_ref_m;
    double vx_ref_m_s;
    double vy_ref_m_s;
    double vz_ref_m_s;
    double yaw_ref_rad;
} GuidanceRef;

typedef struct {
    // Actuator commands (normalized) for demo
    double lift_thrust;     // 0..1 total lift
    double roll_cmd;
    double pitch_cmd;
    double yaw_cmd;
} ActuatorCmd;

typedef struct {
    bool sensor_fault;
    bool comm_fault;
    bool battery_fault;
    bool engine_fault;
} FaultFlags;

typedef struct {
    bool battery_low;
    bool engine_warn;
    bool comm_lost;
    bool collision_risk;
} Alarms;

#ifdef __cplusplus
}
#endif

#endif
