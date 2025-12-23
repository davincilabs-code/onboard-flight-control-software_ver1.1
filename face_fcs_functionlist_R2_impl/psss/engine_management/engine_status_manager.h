#ifndef PSSS_ENGINE_MANAGEMENT_ENGINE_STATUS_MANAGER_H
#define PSSS_ENGINE_MANAGEMENT_ENGINE_STATUS_MANAGER_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Engine Management
// Function : Engine Status Manager
// Segment  : PSSS
// Req ID   : R-FCSQC01-SFR-028
// Desc     : Engine Status 관리
void psss_engine_management_engine_status_manager_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
