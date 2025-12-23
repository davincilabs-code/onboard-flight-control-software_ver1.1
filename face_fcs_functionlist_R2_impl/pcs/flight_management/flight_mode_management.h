#ifndef PCS_FLIGHT_MANAGEMENT_FLIGHT_MODE_MANAGEMENT_H
#define PCS_FLIGHT_MANAGEMENT_FLIGHT_MODE_MANAGEMENT_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Flight Management
// Function : Flight Mode Management
// Segment  : PCS
// Req ID   : R-FCSQC01-SFR-001
// Desc     : 수동, 자동, 비상 모드에 대한 상태 모니터링 및 비행 모드별 함수 실행
void pcs_flight_management_flight_mode_management_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
