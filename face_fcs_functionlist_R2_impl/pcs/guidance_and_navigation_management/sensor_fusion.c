#include "face_context.h"
#include "face_bus.h"

void pcs_guidance_and_navigation_management_sensor_fusion_step(FaceContext* ctx)
{
    // Combine AHRS attitude + GPS altitude (demo) into nav estimate.
    if (ctx->gps.fix_ok){
        ctx->nav.z_m = ctx->gps.alt_m;
    } else if (ctx->ralt.ok){
        ctx->nav.z_m = ctx->ralt.alt_m;
    }
    ctx->nav.roll_rad = ctx->ahrs.roll_rad;
    ctx->nav.pitch_rad = ctx->ahrs.pitch_rad;
    ctx->nav.yaw_rad = ctx->ahrs.yaw_rad;

    face_bus_publish(TOPIC_NAV_STATE, ctx->now_us, &ctx->nav, sizeof(ctx->nav));
}
