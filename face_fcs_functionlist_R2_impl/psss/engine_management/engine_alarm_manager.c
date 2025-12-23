#include "face_context.h"
#include "face_log.h"

void psss_engine_management_engine_alarm_manager_step(FaceContext* ctx)
{
    if (ctx->alarms.engine_warn){
        face_log_warn("ENG: warn alarm");
        ctx->faults.engine_fault = true;
    }
}
