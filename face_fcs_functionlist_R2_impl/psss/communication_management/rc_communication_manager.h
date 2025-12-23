#ifndef PSSS_COMMUNICATION_MANAGEMENT_RC_COMMUNICATION_MANAGER_H
#define PSSS_COMMUNICATION_MANAGEMENT_RC_COMMUNICATION_MANAGER_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Communication Management
// Function : RC Communication Manager
// Segment  : PSSS
// Req ID   : R-FCSQC01-IEIR-006
// Desc     : RC 포트 및 연결 관리
void psss_communication_management_rc_communication_manager_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
