#ifndef PCS_FLIGHT_MANAGEMENT_FLIGHT_ALARM_MANAGEMENT_H
#define PCS_FLIGHT_MANAGEMENT_FLIGHT_ALARM_MANAGEMENT_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Flight Management
// Function : Flight Alarm Management
// Segment  : PCS
// Req ID   : R-FCSQC01-SFR-014
// Desc     : 비행 알람 관리 기능
void pcs_flight_management_flight_alarm_management_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
