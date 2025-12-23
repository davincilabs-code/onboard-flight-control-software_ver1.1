#include "face_context.h"
#include "face_bus.h"
#include "face_log.h"
#include <math.h>

void ioss_sensor_data_management_air_data_sensor_step(FaceContext* ctx)
{
    // Demo airspeed follows commanded cruise speed with first-order lag
    double target = (ctx->mode==FLIGHT_MODE_AUTO && (ctx->phase==FLIGHT_PHASE_CRUISE || ctx->phase==FLIGHT_PHASE_TRANSITION))
                    ? ctx->cruise_speed_m_s : 0.0;
    double tau = 1.5;
    ctx->air.airspeed_m_s += (target - ctx->air.airspeed_m_s) * (ctx->dt_s / tau);
    ctx->air.ok = !ctx->faults.sensor_fault;

    face_bus_publish(TOPIC_TEXT_EVENT, ctx->now_us, "IOSS: AirData updated", 20);
}
