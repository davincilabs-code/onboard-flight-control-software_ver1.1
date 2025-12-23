#ifndef PSSS_BATTERY_MANAGEMENT_BATTERY_MANAGEMENT_H
#define PSSS_BATTERY_MANAGEMENT_BATTERY_MANAGEMENT_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Battery Management
// Function : Battery Management 
// Segment  : PSSS
// Req ID   : R-FCSQC01-SFR-024
// Desc     : Battery 종합 관리
void psss_battery_management_battery_management_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
