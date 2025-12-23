#include "face_context.h"
#include <math.h>

void pcs_guidance_and_navigation_management_collision_avoidance_management_step(FaceContext* ctx)
{
    // Demo: collision risk if too low altitude during forward motion
    ctx->alarms.collision_risk = (ctx->nav.z_m < 10.0 && (fabs(ctx->nav.vx_m_s)+fabs(ctx->nav.vy_m_s) > 5.0));
    if (ctx->alarms.collision_risk){
        // push altitude up
        ctx->ref.z_ref_m = fmax(ctx->ref.z_ref_m, 20.0);
    }
}
