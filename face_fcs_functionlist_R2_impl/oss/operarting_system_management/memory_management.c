#include "face_context.h"
#include "face_log.h"
#include <stdint.h>

static uint32_t g_heap_used = 0;

void oss_operarting_system_management_memory_management_step(FaceContext* ctx)
{
    (void)ctx;
    face_log_info("OSS: Memory used=%u bytes (demo)", g_heap_used);
}

void oss_heap_account(uint32_t delta){ g_heap_used += delta; }
