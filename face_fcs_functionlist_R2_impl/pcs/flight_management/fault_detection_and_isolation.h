#ifndef PCS_FLIGHT_MANAGEMENT_FAULT_DETECTION_AND_ISOLATION_H
#define PCS_FLIGHT_MANAGEMENT_FAULT_DETECTION_AND_ISOLATION_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Flight Management
// Function : Fault Detection & Isolation
// Segment  : PCS
// Req ID   : R-FCSQC01-SFR-015
// Desc     : 고장 감지 및 분리 기능
void pcs_flight_management_fault_detection_and_isolation_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
