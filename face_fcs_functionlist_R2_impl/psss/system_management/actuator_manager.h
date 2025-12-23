#ifndef PSSS_SYSTEM_MANAGEMENT_ACTUATOR_MANAGER_H
#define PSSS_SYSTEM_MANAGEMENT_ACTUATOR_MANAGER_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: System Management
// Function : Actuator Manager
// Segment  : PSSS
// Req ID   : R-FCSQC01-SFR-035
// Desc     : Actuator 상태 및 이상 대응 관리자, 캘리브레이션
void psss_system_management_actuator_manager_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
