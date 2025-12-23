#include "face_context.h"

void psss_engine_management_engine_mode_management_step(FaceContext* ctx)
{
    // If engine fault, force emergency.
    if (ctx->faults.engine_fault) ctx->mode = FLIGHT_MODE_EMERGENCY;
}
