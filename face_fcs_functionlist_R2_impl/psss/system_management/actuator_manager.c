#include "face_context.h"
#include "face_log.h"
#include <math.h>

static int g_sat_count = 0;

void psss_system_management_actuator_manager_step(FaceContext* ctx)
{
    // Detect sustained actuator saturation (demo)
    bool sat = (ctx->act.lift_thrust <= 0.001) || (ctx->act.lift_thrust >= 0.999);
    if (sat) g_sat_count++;
    else g_sat_count = 0;

    if (g_sat_count > 200){ // ~2s at 10ms
        face_log_warn("ACTMGR: sustained saturation -> comm/actuator fault (demo)");
        ctx->faults.comm_fault = true; // demo mapping
    }
}
