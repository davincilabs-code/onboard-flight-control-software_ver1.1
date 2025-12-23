#ifndef PCS_FLIGHT_MANAGEMENT_ROTATING_MODE_H
#define PCS_FLIGHT_MANAGEMENT_ROTATING_MODE_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Flight Management
// Function : Rotating Mode
// Segment  : PCS
// Req ID   : R-FCSQC01-SFR-008
// Desc     : Auto mode로 수행되는 Rotating에 대한 비행절차 수행 및 목점점 계산
void pcs_flight_management_rotating_mode_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
