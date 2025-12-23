#ifndef PSSS_SYSTEM_MANAGEMENT_SIDE_STICK_MANAGER_H
#define PSSS_SYSTEM_MANAGEMENT_SIDE_STICK_MANAGER_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: System Management
// Function : Side Stick Manager
// Segment  : PSSS
// Req ID   : R-FCSQC01-SFR-040
// Desc     : 사이드 스틱 조종 관리자
void psss_system_management_side_stick_manager_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
