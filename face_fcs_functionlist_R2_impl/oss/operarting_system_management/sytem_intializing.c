#include "face_context.h"
#include "face_bus.h"
#include "face_log.h"
#include "oss_kernel.h"

void oss_operarting_system_management_sytem_intializing_step(FaceContext* ctx)
{
    face_log_info("OSS: System initializing");
    face_context_init(ctx);
    face_bus_init();
    oss_kernel_init(ctx);
}
