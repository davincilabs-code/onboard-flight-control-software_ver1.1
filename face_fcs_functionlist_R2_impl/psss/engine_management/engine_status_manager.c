#include "face_context.h"
#include "face_bus.h"

void psss_engine_management_engine_status_manager_step(FaceContext* ctx)
{
    // Demo: engine warn if sustained high thrust
    ctx->alarms.engine_warn = (ctx->act.lift_thrust > 0.85);
    (void)face_bus_publish(TOPIC_TEXT_EVENT, ctx->now_us, "PSSS: Engine status", 19);
}
