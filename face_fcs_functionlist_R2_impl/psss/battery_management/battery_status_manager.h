#ifndef PSSS_BATTERY_MANAGEMENT_BATTERY_STATUS_MANAGER_H
#define PSSS_BATTERY_MANAGEMENT_BATTERY_STATUS_MANAGER_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Battery Management
// Function : Battery Status Manager
// Segment  : PSSS
// Req ID   : R-FCSQC01-SFR-025
// Desc     : Battery 상태 관리
void psss_battery_management_battery_status_manager_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
