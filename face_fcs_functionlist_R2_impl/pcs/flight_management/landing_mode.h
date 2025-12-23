#ifndef PCS_FLIGHT_MANAGEMENT_LANDING_MODE_H
#define PCS_FLIGHT_MANAGEMENT_LANDING_MODE_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Flight Management
// Function : Landing Mode
// Segment  : PCS
// Req ID   : R-FCSQC01-SFR-006
// Desc     : Auto mode로 수행되는 Landing에 대한 비행절차 수행 및 목점점 계산
void pcs_flight_management_landing_mode_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
