#ifndef PCS_FLIGHT_MANAGEMENT_FLIGHT_STATUS_MANAGEMENT_H
#define PCS_FLIGHT_MANAGEMENT_FLIGHT_STATUS_MANAGEMENT_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Flight Management
// Function : Flight Status Management
// Segment  : PCS
// Req ID   : R-FCSQC01-SFR-013
// Desc     : 비행 상태 정보 관리 기능
void pcs_flight_management_flight_status_management_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
