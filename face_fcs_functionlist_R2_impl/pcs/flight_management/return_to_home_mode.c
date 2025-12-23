#include "face_context.h"
#include <math.h>

void pcs_flight_management_return_to_home_mode_step(FaceContext* ctx)
{
    if (ctx->mode != FLIGHT_MODE_AUTO) return;
    if (ctx->phase == FLIGHT_PHASE_RTL){
        ctx->ref.x_ref_m = 0.0;
        ctx->ref.y_ref_m = 0.0;
        ctx->ref.z_ref_m = ctx->hover_alt_m;
    }
}
