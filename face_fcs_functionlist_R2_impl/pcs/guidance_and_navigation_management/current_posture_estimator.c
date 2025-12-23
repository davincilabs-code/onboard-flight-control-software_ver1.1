#include "face_context.h"
#include <math.h>

void pcs_guidance_and_navigation_management_current_posture_estimator_step(FaceContext* ctx)
{
    // Simple vertical dynamics from lift thrust (demo physics)
    // z_dot += (thrust - hover)*g
    const double g = 9.806;
    const double hover_thrust = 0.55;  // tuning
    double az = (ctx->act.lift_thrust - hover_thrust) * g;
    ctx->nav.vz_m_s += az * ctx->dt_s;
    ctx->nav.z_m += ctx->nav.vz_m_s * ctx->dt_s;
    if (ctx->nav.z_m < 0){ ctx->nav.z_m = 0; ctx->nav.vz_m_s = 0; }

    // crude horizontal velocity toward ref
    double vx = (ctx->ref.vx_ref_m_s);
    double vy = (ctx->ref.vy_ref_m_s);
    ctx->nav.vx_m_s += (vx - ctx->nav.vx_m_s) * 0.1;
    ctx->nav.vy_m_s += (vy - ctx->nav.vy_m_s) * 0.1;
    ctx->nav.x_m += ctx->nav.vx_m_s * ctx->dt_s;
    ctx->nav.y_m += ctx->nav.vy_m_s * ctx->dt_s;
}
