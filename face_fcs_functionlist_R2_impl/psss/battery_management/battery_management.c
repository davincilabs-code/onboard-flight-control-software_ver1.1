#include "face_context.h"

void psss_battery_management_battery_management_step(FaceContext* ctx)
{
    // Aggregate battery-related decisions (demo)
    if (ctx->faults.battery_fault && ctx->mode != FLIGHT_MODE_EMERGENCY){
        ctx->mode = FLIGHT_MODE_EMERGENCY;
    }
}
