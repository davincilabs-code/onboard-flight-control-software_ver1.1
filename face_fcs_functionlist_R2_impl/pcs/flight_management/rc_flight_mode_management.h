#ifndef PCS_FLIGHT_MANAGEMENT_RC_FLIGHT_MODE_MANAGEMENT_H
#define PCS_FLIGHT_MANAGEMENT_RC_FLIGHT_MODE_MANAGEMENT_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Flight Management
// Function : RC Flight Mode Management
// Segment  : PCS
// Req ID   : R-FCSQC01-SFR-002
// Desc     : 지상 조종자의 조종기에 의한 비행제어 모드 수행 
void pcs_flight_management_rc_flight_mode_management_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
