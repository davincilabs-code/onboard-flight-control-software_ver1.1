#include "face_context.h"
#include "face_bus.h"
#include <math.h>

void ioss_sensor_data_management_ahrs_sensor_step(FaceContext* ctx)
{
    // Simple attitude dynamics: follow actuator commands with lag
    double tau = 0.5;
    ctx->ahrs.roll_rad  += (ctx->act.roll_cmd  - ctx->ahrs.roll_rad)  * (ctx->dt_s / tau);
    ctx->ahrs.pitch_rad += (ctx->act.pitch_cmd - ctx->ahrs.pitch_rad) * (ctx->dt_s / tau);
    ctx->ahrs.yaw_rad   += (ctx->act.yaw_cmd   - ctx->ahrs.yaw_rad)   * (ctx->dt_s / tau);
    ctx->ahrs.p_rad_s = 0.0; ctx->ahrs.q_rad_s = 0.0; ctx->ahrs.r_rad_s = 0.0;
    ctx->ahrs.ax_m_s2 = 0.0; ctx->ahrs.ay_m_s2 = 0.0; ctx->ahrs.az_m_s2 = 0.0;
    face_bus_publish(TOPIC_TEXT_EVENT, ctx->now_us, "IOSS: AHRS updated", 17);
}
