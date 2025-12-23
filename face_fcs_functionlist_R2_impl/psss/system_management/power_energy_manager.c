#include "face_context.h"
#include "face_log.h"

void psss_system_management_power_energy_manager_step(FaceContext* ctx)
{
    // Aggregate energy state: if battery low -> request RTL/land in auto.
    if (ctx->alarms.battery_low && ctx->mode == FLIGHT_MODE_AUTO){
        face_log_warn("POWER: battery low -> request LAND phase");
        ctx->phase = FLIGHT_PHASE_LAND;
    }
}
