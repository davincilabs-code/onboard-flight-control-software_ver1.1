#include "face_context.h"
#include <math.h>

static double clamp(double x, double lo, double hi){ return x<lo?lo:(x>hi?hi:x); }

void pcs_fcl_management_lift_mode_controller_step(FaceContext* ctx)
{
    // Simple P controller for altitude + attitude to generate actuator commands.
    double ez = ctx->ref.z_ref_m - ctx->nav.z_m;
    double thrust = 0.55 + 0.02 * ez - 0.01 * ctx->nav.vz_m_s;
    ctx->act.lift_thrust = clamp(thrust, 0.0, 1.0);

    // Attitude commands track yaw + small tilt for velocity
    double vx_err = ctx->ref.vx_ref_m_s - ctx->nav.vx_m_s;
    double vy_err = ctx->ref.vy_ref_m_s - ctx->nav.vy_m_s;

    ctx->act.pitch_cmd = clamp(0.05 * vx_err, -0.3, 0.3);
    ctx->act.roll_cmd  = clamp(-0.05 * vy_err, -0.3, 0.3);
    ctx->act.yaw_cmd   = clamp(ctx->ref.yaw_ref_rad, -1.5, 1.5);
}
