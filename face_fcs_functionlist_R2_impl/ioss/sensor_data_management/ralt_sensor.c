#include "face_context.h"
#include "face_bus.h"
#include <math.h>

void ioss_sensor_data_management_ralt_sensor_step(FaceContext* ctx)
{
    ctx->ralt.ok = !ctx->faults.sensor_fault;
    // Radar altimeter measures altitude with small noise
    ctx->ralt.alt_m = ctx->nav.z_m;
    face_bus_publish(TOPIC_TEXT_EVENT, ctx->now_us, "IOSS: RALT updated", 17);
}
