#include "face_context.h"
#include "face_bus.h"
#include "face_log.h"
#include <math.h>

void psss_communication_management_rc_communication_manager_step(FaceContext* ctx)
{
    // Demo RC profile: 0-2s manual hover, 2-4s auto takeoff, then cruise
    double t = (double)ctx->now_us * 1e-6;
    if (t < 2.0){
        ctx->pilot_in.mode_switch = 0;
        ctx->pilot_in.stick_throttle = 0.2;
    } else if (t < 4.0){
        ctx->pilot_in.mode_switch = 1;
        ctx->pilot_in.stick_throttle = 0.6;
    } else {
        ctx->pilot_in.mode_switch = 1;
        ctx->pilot_in.stick_throttle = 0.5;
    }
    ctx->alarms.comm_lost = false;
    face_bus_publish(TOPIC_PILOT_INPUT, ctx->now_us, &ctx->pilot_in, sizeof(ctx->pilot_in));
}
