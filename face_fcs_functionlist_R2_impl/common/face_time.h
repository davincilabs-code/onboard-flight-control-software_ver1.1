#ifndef FACE_TIME_H
#define FACE_TIME_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
uint64_t face_time_now_us(void);
void face_time_sleep_us(uint64_t us);
#ifdef __cplusplus
}
#endif
#endif
