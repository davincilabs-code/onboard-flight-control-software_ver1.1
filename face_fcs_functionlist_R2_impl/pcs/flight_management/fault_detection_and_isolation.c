#include "face_context.h"
#include <math.h>

void pcs_flight_management_fault_detection_and_isolation_step(FaceContext* ctx)
{
    // Basic FDI checks (demo thresholds)
    bool sensor_bad = (!ctx->air.ok) || (!ctx->gps.fix_ok && !ctx->ralt.ok);
    bool nav_bad = isnan(ctx->nav.z_m) || ctx->nav.z_m < -1.0 || ctx->nav.z_m > 10000.0;
    ctx->faults.sensor_fault = sensor_bad || nav_bad;
}
