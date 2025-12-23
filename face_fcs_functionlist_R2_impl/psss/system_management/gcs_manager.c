#include "face_context.h"
#include "face_bus.h"
#include "face_log.h"

void psss_system_management_gcs_manager_step(FaceContext* ctx)
{
    // Demo: publish status messages that a GCS could subscribe to
    (void)face_bus_publish(TOPIC_NAV_STATE, ctx->now_us, &ctx->nav, sizeof(ctx->nav));
    (void)face_bus_publish(TOPIC_GUIDANCE_REF, ctx->now_us, &ctx->ref, sizeof(ctx->ref));
}
