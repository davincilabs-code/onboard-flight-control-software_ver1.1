#ifndef PSSS_COMMUNICATION_MANAGEMENT_RF_VHF_COMMUNICATION_MANAGER_H
#define PSSS_COMMUNICATION_MANAGEMENT_RF_VHF_COMMUNICATION_MANAGER_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Communication Management
// Function : RF(VHF) Communication Manager
// Segment  : PSSS
// Req ID   : R-FCSQC01-IEIR-005
// Desc     : RF(VHF) 포트 및 연결 관리
void psss_communication_management_rf_vhf_communication_manager_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
