#include "face_context.h"
#include "face_log.h"

void pcs_flight_management_flight_alarm_management_step(FaceContext* ctx)
{
    if (ctx->alarms.comm_lost) face_log_warn("ALARM: comm lost");
    if (ctx->alarms.battery_low) face_log_warn("ALARM: battery low");
    if (ctx->alarms.collision_risk) face_log_warn("ALARM: collision risk");
}
