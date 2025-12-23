#include "face_time.h"
#include <time.h>

uint64_t face_time_now_us(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec*1000000ull + (uint64_t)(ts.tv_nsec/1000ull);
}

void face_time_sleep_us(uint64_t us)
{
    struct timespec req;
    req.tv_sec = (time_t)(us/1000000ull);
    req.tv_nsec = (long)((us%1000000ull)*1000ull);
    nanosleep(&req, NULL);
}
