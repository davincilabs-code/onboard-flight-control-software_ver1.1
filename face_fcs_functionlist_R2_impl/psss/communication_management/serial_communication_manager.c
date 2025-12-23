#include "face_context.h"
#include "face_log.h"

void psss_communication_management_serial_communication_manager_step(FaceContext* ctx)
{
    // Demo: link is healthy unless forced by ctx->faults.comm_fault
    if (ctx->faults.comm_fault) {
        ctx->alarms.comm_lost = true;
        face_log_warn("COMM: Serial Communication Manager lost");
    } else {
        ctx->alarms.comm_lost = false;
    }
}
