#include "face_context.h"
#include "face_log.h"

void psss_system_management_fcc_manager_step(FaceContext* ctx)
{
    // Simple dual-FCC switching logic (demo)
    // If any critical fault, switch active FCC once.
    static bool switched = false;
    bool critical = ctx->faults.sensor_fault || ctx->faults.engine_fault || ctx->faults.comm_fault;

    if (critical && !switched){
        ctx->active_fcc = (ctx->active_fcc==0) ? 1 : 0;
        switched = true;
        face_log_warn("FCC: switch to backup FCC=%u (demo)", (unsigned)ctx->active_fcc);
    }
    if (!critical) switched = false;
}
