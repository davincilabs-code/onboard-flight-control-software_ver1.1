#include "face_context.h"

void pcs_flight_management_rotating_mode_step(FaceContext* ctx)
{
    if (ctx->mode != FLIGHT_MODE_AUTO) return;
    // In lift+cruise, "rotating" is treated as part of transition prep.
    if (ctx->phase == FLIGHT_PHASE_TRANSITION){
        // keep altitude while accelerating
        ctx->ref.z_ref_m = ctx->hover_alt_m;
    }
}
