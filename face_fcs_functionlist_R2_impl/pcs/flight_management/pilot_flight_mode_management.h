#ifndef PCS_FLIGHT_MANAGEMENT_PILOT_FLIGHT_MODE_MANAGEMENT_H
#define PCS_FLIGHT_MANAGEMENT_PILOT_FLIGHT_MODE_MANAGEMENT_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Flight Management
// Function : Pilot Flight Mode Management
// Segment  : PCS
// Req ID   : R-FCSQC01-SFR-003
// Desc     : 조종석 파일럿의 사이드스틱, 페달에 의한 비행제어 모드 수행 
void pcs_flight_management_pilot_flight_mode_management_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
