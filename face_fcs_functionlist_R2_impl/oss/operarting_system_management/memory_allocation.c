#include "face_context.h"
#include "face_log.h"
#include <stdlib.h>
#include <stdint.h>

void oss_heap_account(uint32_t delta);

void* oss_malloc(size_t n)
{
    void* p = malloc(n);
    if (p) oss_heap_account((uint32_t)n);
    return p;
}

void oss_operarting_system_management_memory_allocation_step(FaceContext* ctx)
{
    (void)ctx;
    // Demo: allocate nothing; real system would manage pools/partitions.
    face_log_info("OSS: Memory allocation service available (demo)");
}
