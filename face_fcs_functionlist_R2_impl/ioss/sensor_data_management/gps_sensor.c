#include "face_context.h"
#include "face_bus.h"
#include <math.h>

void ioss_sensor_data_management_gps_sensor_step(FaceContext* ctx)
{
    // Integrate position from nav velocity (demo)
    ctx->gps.fix_ok = !ctx->faults.sensor_fault;
    // Fake lat/lon update using local meters (very rough, for demo only)
    ctx->gps.lat_deg += (ctx->nav.vx_m_s * ctx->dt_s) * 1e-5;
    ctx->gps.lon_deg += (ctx->nav.vy_m_s * ctx->dt_s) * 1e-5;
    ctx->gps.alt_m = ctx->nav.z_m;
    ctx->gps.vn_m_s = ctx->nav.vx_m_s;
    ctx->gps.ve_m_s = ctx->nav.vy_m_s;
    ctx->gps.vd_m_s = -ctx->nav.vz_m_s;

    face_bus_publish(TOPIC_TEXT_EVENT, ctx->now_us, "IOSS: GPS updated", 16);
}
