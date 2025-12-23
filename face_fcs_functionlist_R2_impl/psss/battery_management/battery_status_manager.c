#include "face_context.h"
#include "face_bus.h"

static double g_soc = 1.0;

void psss_battery_management_battery_status_manager_step(FaceContext* ctx)
{
    // Simple drain: proportional to thrust
    g_soc -= 0.0005 * (0.2 + ctx->act.lift_thrust) * (ctx->dt_s / 0.01);
    if (g_soc < 0.0) g_soc = 0.0;
    ctx->alarms.battery_low = (g_soc < 0.15);
    (void)face_bus_publish(TOPIC_TEXT_EVENT, ctx->now_us, "PSSS: Battery status", 20);
}
