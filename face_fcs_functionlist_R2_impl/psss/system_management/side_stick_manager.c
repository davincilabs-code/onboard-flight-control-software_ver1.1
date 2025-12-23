#include "face_context.h"
#include <math.h>

static double lpf(double prev, double x, double alpha){ return prev + alpha*(x-prev); }

void psss_system_management_side_stick_manager_step(FaceContext* ctx)
{
    // Smooth pilot stick inputs (demo)
    static PilotInput filt;
    filt.stick_roll     = lpf(filt.stick_roll, ctx->pilot_in.stick_roll, 0.2);
    filt.stick_pitch    = lpf(filt.stick_pitch, ctx->pilot_in.stick_pitch, 0.2);
    filt.stick_yaw      = lpf(filt.stick_yaw, ctx->pilot_in.stick_yaw, 0.2);
    filt.stick_throttle = lpf(filt.stick_throttle, ctx->pilot_in.stick_throttle, 0.2);
    filt.mode_switch    = ctx->pilot_in.mode_switch;

    ctx->pilot_in = filt;
}
