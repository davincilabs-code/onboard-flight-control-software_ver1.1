#include "face_context.h"
#include "face_bus.h"

typedef struct {
    int mode;
    int phase;
    double x, y, z;
    double airspeed;
} FlightStatus;

void pcs_flight_management_flight_status_management_step(FaceContext* ctx)
{
    FlightStatus st = {(int)ctx->mode,(int)ctx->phase, ctx->nav.x_m, ctx->nav.y_m, ctx->nav.z_m, ctx->air.airspeed_m_s};
    face_bus_publish(TOPIC_TEXT_EVENT, ctx->now_us, "PCS: Status updated", 18);
    (void)st;
}
