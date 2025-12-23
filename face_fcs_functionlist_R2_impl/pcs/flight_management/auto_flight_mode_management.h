#ifndef PCS_FLIGHT_MANAGEMENT_AUTO_FLIGHT_MODE_MANAGEMENT_H
#define PCS_FLIGHT_MANAGEMENT_AUTO_FLIGHT_MODE_MANAGEMENT_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Flight Management
// Function : Auto Flight Mode Management
// Segment  : PCS
// Req ID   : R-FCSQC01-SFR-004
// Desc     : 수집센서 및 자동비행모드 에 의한 자동 비행제어 모드 수행 
void pcs_flight_management_auto_flight_mode_management_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
