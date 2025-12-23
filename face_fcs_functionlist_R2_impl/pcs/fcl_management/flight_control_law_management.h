#ifndef PCS_FCL_MANAGEMENT_FLIGHT_CONTROL_LAW_MANAGEMENT_H
#define PCS_FCL_MANAGEMENT_FLIGHT_CONTROL_LAW_MANAGEMENT_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: FCL Management
// Function : Flight Control Law Management
// Segment  : PCS
// Req ID   : R-FCSQC01-SFR-021
// Desc     : 비행제어 법칙 관리자
void pcs_fcl_management_flight_control_law_management_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
