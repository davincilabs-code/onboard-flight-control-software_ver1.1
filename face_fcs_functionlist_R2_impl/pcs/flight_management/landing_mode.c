#include "face_context.h"

void pcs_flight_management_landing_mode_step(FaceContext* ctx)
{
    if (ctx->mode != FLIGHT_MODE_AUTO) return;
    if (ctx->phase == FLIGHT_PHASE_LAND){
        ctx->ref.z_ref_m = 0.0;
        ctx->ref.vx_ref_m_s = 0.0;
        ctx->ref.vy_ref_m_s = 0.0;
    }
}
