#include "face_context.h"
#include "face_log.h"

void ioss_operarting_system_management_device_driver_manager_step(FaceContext* ctx)
{
    // In a real build, this would probe and manage driver instances.
    // Here we sanity-check the required sensor interfaces are "alive".
    bool ok = ctx->air.ok || ctx->ralt.ok || ctx->gps.fix_ok;
    if (!ok){
        ctx->faults.sensor_fault = true;
        face_log_warn("IOSS: no viable altitude/airspeed sources -> sensor fault");
    }
}
