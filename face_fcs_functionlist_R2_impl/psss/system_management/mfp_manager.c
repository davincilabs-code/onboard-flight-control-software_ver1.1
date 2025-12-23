#include "face_context.h"
#include "face_bus.h"

// MFP = Multi-Function Processor (display / HMI). Demo publishes alarms.
void psss_system_management_mfp_manager_step(FaceContext* ctx)
{
    (void)face_bus_publish(TOPIC_ALARMS, ctx->now_us, &ctx->alarms, sizeof(ctx->alarms));
}
