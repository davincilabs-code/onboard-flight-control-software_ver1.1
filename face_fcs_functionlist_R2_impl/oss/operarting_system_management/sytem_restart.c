#include "face_context.h"
#include "face_log.h"
#include "oss_kernel.h"

void oss_operarting_system_management_sytem_restart_step(FaceContext* ctx)
{
    face_log_warn("OSS: System restart requested (re-init context + kernel)");
    face_context_init(ctx);
    oss_kernel_init(ctx);
}
