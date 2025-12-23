#include "face_context.h"
#include <math.h>

static double clamp(double x, double lo, double hi){ return x<lo?lo:(x>hi?hi:x); }

void pcs_guidance_and_navigation_management_taget_posture_generator_step(FaceContext* ctx)
{
    // Generate targets based on manual vs auto
    if (ctx->mode == FLIGHT_MODE_MANUAL){
        ctx->ref.yaw_ref_rad = clamp(ctx->pilot_in.stick_yaw, -1.0, 1.0) * 0.5;
        ctx->ref.z_ref_m = ctx->nav.z_m + (ctx->pilot_in.stick_throttle-0.5)*2.0; // small climb command
        ctx->ref.vx_ref_m_s = clamp(ctx->pilot_in.stick_pitch, -1.0, 1.0) * 2.0;
        ctx->ref.vy_ref_m_s = clamp(ctx->pilot_in.stick_roll, -1.0, 1.0) * 2.0;
    } else {
        // auto keeps ref from path planner
        // yaw faces velocity
        ctx->ref.yaw_ref_rad = atan2(ctx->ref.vy_ref_m_s, ctx->ref.vx_ref_m_s);
    }
}
