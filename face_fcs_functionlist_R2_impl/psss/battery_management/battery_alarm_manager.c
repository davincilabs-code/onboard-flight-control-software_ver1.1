#include "face_context.h"
#include "face_log.h"

void psss_battery_management_battery_alarm_manager_step(FaceContext* ctx)
{
    if (ctx->alarms.battery_low){
        face_log_warn("BAT: low battery alarm");
        ctx->faults.battery_fault = true;
    }
}
