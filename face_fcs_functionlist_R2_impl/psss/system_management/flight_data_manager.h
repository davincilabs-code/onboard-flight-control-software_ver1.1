#ifndef PSSS_SYSTEM_MANAGEMENT_FLIGHT_DATA_MANAGER_H
#define PSSS_SYSTEM_MANAGEMENT_FLIGHT_DATA_MANAGER_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: System Management
// Function : Flight Data Manager
// Segment  : PSSS
// Req ID   : R-FCSQC01-SFR-030
// Desc     : 비행로그, 비행데이터 관리자
void psss_system_management_flight_data_manager_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
