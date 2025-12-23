#include "face_log.h"
#include <stdio.h>
#include <stdarg.h>

static void vlog(const char* tag, const char* fmt, va_list ap)
{
    fprintf(stdout, "[%s] ", tag);
    vfprintf(stdout, fmt, ap);
    fprintf(stdout, "\n");
}

void face_log_info(const char* fmt, ...)
{
    va_list ap; va_start(ap, fmt);
    vlog("INFO", fmt, ap);
    va_end(ap);
}
void face_log_warn(const char* fmt, ...)
{
    va_list ap; va_start(ap, fmt);
    vlog("WARN", fmt, ap);
    va_end(ap);
}
void face_log_error(const char* fmt, ...)
{
    va_list ap; va_start(ap, fmt);
    vlog("ERR", fmt, ap);
    va_end(ap);
}
