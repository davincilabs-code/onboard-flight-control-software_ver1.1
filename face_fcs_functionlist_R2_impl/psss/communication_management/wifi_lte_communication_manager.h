#ifndef PSSS_COMMUNICATION_MANAGEMENT_WIFI_LTE_COMMUNICATION_MANAGER_H
#define PSSS_COMMUNICATION_MANAGEMENT_WIFI_LTE_COMMUNICATION_MANAGER_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Communication Management
// Function : Wifi(LTE) Communication Manager
// Segment  : PSSS
// Req ID   : R-FCSQC01-IEIR-004
// Desc     : Wifi(LTE) 포트 및 연결 관리
void psss_communication_management_wifi_lte_communication_manager_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
