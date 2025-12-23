#include "face_context.h"
#include <string.h>

void face_context_init(FaceContext* ctx)
{
    memset(ctx, 0, sizeof(*ctx));
    ctx->dt_s = 0.01;
    ctx->mode = FLIGHT_MODE_MANUAL;
    ctx->phase = FLIGHT_PHASE_GROUND;
    ctx->active_fcc = 0;
    ctx->wow = true;

    ctx->takeoff_alt_m = 30.0;
    ctx->hover_alt_m = 50.0;
    ctx->cruise_speed_m_s = 25.0;

    ctx->pilot_in.stick_throttle = 0.0;
    ctx->pilot_in.mode_switch = 0;
    ctx->air.ok = true;
    ctx->gps.fix_ok = true;
    ctx->ralt.ok = true;
}
