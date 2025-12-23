#ifndef FACE_LOG_H
#define FACE_LOG_H

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

void face_log_info(const char* fmt, ...);
void face_log_warn(const char* fmt, ...);
void face_log_error(const char* fmt, ...);

#ifdef __cplusplus
}
#endif
#endif
