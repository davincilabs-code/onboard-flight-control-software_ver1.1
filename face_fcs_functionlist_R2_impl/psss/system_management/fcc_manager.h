#ifndef PSSS_SYSTEM_MANAGEMENT_FCC_MANAGER_H
#define PSSS_SYSTEM_MANAGEMENT_FCC_MANAGER_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: System Management
// Function : FCC Manager
// Segment  : PSSS
// Req ID   : R-FCSQC01-SFR-033
// Desc     : 비행제어컴퓨터 상태 및 스위칭 관리자
void psss_system_management_fcc_manager_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
