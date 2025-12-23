#ifndef PSSS_SYSTEM_MANAGEMENT_GCS_MANAGER_H
#define PSSS_SYSTEM_MANAGEMENT_GCS_MANAGER_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: System Management
// Function : GCS Manager
// Segment  : PSSS
// Req ID   : R-FCSQC01-SFR-039
// Desc     : GCS 상태정보 수신, 명령전달 관리자
void psss_system_management_gcs_manager_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
