#include "face_context.h"
#include "face_log.h"

static int g_bad_count = 0;

void psss_system_management_sensor_manager_step(FaceContext* ctx)
{
    // Monitor sensor health and trigger sensor_fault if persistent bad samples
    bool any_bad = (!ctx->air.ok) || (!ctx->ralt.ok) || (!ctx->gps.fix_ok);
    if (any_bad) g_bad_count++;
    else g_bad_count = 0;

    if (g_bad_count > 50){ // ~0.5s at 10ms
        ctx->faults.sensor_fault = true;
        face_log_warn("SENSOR: persistent invalid samples -> fault");
    }
}
