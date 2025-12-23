#include "face_context.h"

void pcs_flight_management_take_off_mode_step(FaceContext* ctx)
{
    if (ctx->mode != FLIGHT_MODE_AUTO) return;
    if (ctx->phase == FLIGHT_PHASE_TAKEOFF){
        ctx->ref.z_ref_m = ctx->takeoff_alt_m;
        ctx->ref.vx_ref_m_s = 0.0;
        ctx->ref.vy_ref_m_s = 0.0;
    }
}
