#ifndef PSSS_SYSTEM_MANAGEMENT_HEALTH_FAULT_MANAGER_H
#define PSSS_SYSTEM_MANAGEMENT_HEALTH_FAULT_MANAGER_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: System Management
// Function : Health/Fault Manager
// Segment  : PSSS
// Req ID   : R-FCSQC01-SFR-036
// Desc     : Sytem health and fault 관리자
void psss_system_management_health_fault_manager_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
