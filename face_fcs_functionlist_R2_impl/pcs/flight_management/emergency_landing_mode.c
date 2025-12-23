#include "face_context.h"
#include <math.h>

void pcs_flight_management_emergency_landing_mode_step(FaceContext* ctx)
{
    if (ctx->mode != FLIGHT_MODE_EMERGENCY) return;
    // Descend at a gentle rate until ground
    double z_target = ctx->nav.z_m - 0.5 * ctx->dt_s;
    if (z_target < 0.0) z_target = 0.0;
    ctx->ref.z_ref_m = z_target;
    ctx->ref.vx_ref_m_s = 0.0;
    ctx->ref.vy_ref_m_s = 0.0;
}
