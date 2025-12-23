#include "face_context.h"

extern void pcs_fcl_management_lift_mode_controller_step(FaceContext* ctx);

void pcs_fcl_management_flight_control_law_management_step(FaceContext* ctx)
{
    // For this reference implementation, use Lift Mode Controller in all phases.
    pcs_fcl_management_lift_mode_controller_step(ctx);
}
