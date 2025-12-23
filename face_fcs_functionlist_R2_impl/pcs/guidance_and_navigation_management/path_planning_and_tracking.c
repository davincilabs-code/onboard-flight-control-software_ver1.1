#include "face_context.h"
#include <math.h>

void pcs_guidance_and_navigation_management_path_planning_and_tracking_step(FaceContext* ctx)
{
    // Demo: fixed point-to-point waypoint at (200,0,hover_alt)
    ctx->ref.x_ref_m = 200.0;
    ctx->ref.y_ref_m = 0.0;
    ctx->ref.z_ref_m = (ctx->phase==FLIGHT_PHASE_CRUISE) ? ctx->hover_alt_m : ctx->takeoff_alt_m;

    // velocity command toward waypoint
    double dx = ctx->ref.x_ref_m - ctx->nav.x_m;
    double dy = ctx->ref.y_ref_m - ctx->nav.y_m;
    double dist = sqrt(dx*dx + dy*dy) + 1e-6;
    double v = (ctx->mode==FLIGHT_MODE_AUTO) ? fmin(ctx->cruise_speed_m_s, dist) : 0.0;
    ctx->ref.vx_ref_m_s = v * dx / dist;
    ctx->ref.vy_ref_m_s = v * dy / dist;
    ctx->ref.vz_ref_m_s = 0.0;
}
