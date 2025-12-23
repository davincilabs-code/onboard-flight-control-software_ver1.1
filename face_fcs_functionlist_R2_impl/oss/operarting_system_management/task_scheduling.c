#include "face_context.h"
#include "face_log.h"

void oss_operarting_system_management_task_scheduling_step(FaceContext* ctx)
{
    (void)ctx;
    // Fixed-priority scheduling is applied inside oss_kernel_step().
    face_log_info("OSS: Task scheduling configured (fixed priority)");
}
