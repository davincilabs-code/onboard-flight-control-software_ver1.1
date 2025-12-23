#include "face_context.h"
#include "oss_kernel.h"

void oss_operarting_system_management_task_execution_step(FaceContext* ctx)
{
    // Execute due tasks (cooperative)
    oss_kernel_step(ctx);
}
