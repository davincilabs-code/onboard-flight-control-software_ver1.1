#ifndef OSS_KERNEL_H
#define OSS_KERNEL_H

#include <stdint.h>
#include <stdbool.h>
#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*FaceTaskFn)(FaceContext*);

typedef struct {
    const char* name;
    FaceTaskFn  fn;
    uint32_t    period_us;
    uint64_t    next_release_us;
    uint8_t     priority; // lower is higher priority
    bool        enabled;
} OssTask;

void oss_kernel_init(FaceContext* ctx);
bool oss_kernel_add_task(const char* name, FaceTaskFn fn, uint32_t period_us, uint8_t priority);
void oss_kernel_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif
#endif
