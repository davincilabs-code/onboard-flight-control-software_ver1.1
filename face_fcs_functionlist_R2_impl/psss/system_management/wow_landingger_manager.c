#include "face_context.h"

void psss_system_management_wow_landingger_manager_step(FaceContext* ctx)
{
    // Simple weight-on-wheels based on altitude
    ctx->wow = (ctx->nav.z_m < 0.2);
}
