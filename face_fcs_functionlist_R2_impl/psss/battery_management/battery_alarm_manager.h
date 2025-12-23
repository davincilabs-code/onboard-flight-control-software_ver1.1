#ifndef PSSS_BATTERY_MANAGEMENT_BATTERY_ALARM_MANAGER_H
#define PSSS_BATTERY_MANAGEMENT_BATTERY_ALARM_MANAGER_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Battery Management
// Function : Battery Alarm Manager
// Segment  : PSSS
// Req ID   : R-FCSQC01-SFR-026
// Desc     : Battery Alarm 관리
void psss_battery_management_battery_alarm_manager_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
