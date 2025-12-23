#include "face_context.h"
#include "face_log.h"

void psss_system_management_health_fault_manager_step(FaceContext* ctx)
{
    // Aggregate health -> emergency decision
    if (ctx->faults.sensor_fault || ctx->faults.comm_fault || ctx->faults.engine_fault || ctx->faults.battery_fault){
        face_log_warn("HEALTH: fault detected -> EMERGENCY");
        ctx->mode = FLIGHT_MODE_EMERGENCY;
    }
}
