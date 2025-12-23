#ifndef PCS_FCL_MANAGEMENT_LIFT_MODE_CONTROLLER_H
#define PCS_FCL_MANAGEMENT_LIFT_MODE_CONTROLLER_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: FCL Management
// Function : Lift Mode Controller
// Segment  : PCS
// Req ID   : R-FCSQC01-SFR-022
// Desc     : 이륙 단계 제어기
void pcs_fcl_management_lift_mode_controller_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
