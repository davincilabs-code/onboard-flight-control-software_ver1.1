#include "face_context.h"
#include "face_log.h"

void psss_system_management_flight_data_manager_step(FaceContext* ctx)
{
    // Minimal flight log line (console). Real system: file/flash.
    face_log_info("LOG: mode=%d phase=%d z=%.1f air=%.1f",
                  (int)ctx->mode, (int)ctx->phase, ctx->nav.z_m, ctx->air.airspeed_m_s);
}
