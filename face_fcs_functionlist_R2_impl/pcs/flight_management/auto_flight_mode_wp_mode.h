#ifndef PCS_FLIGHT_MANAGEMENT_AUTO_FLIGHT_MODE_WP_MODE_H
#define PCS_FLIGHT_MANAGEMENT_AUTO_FLIGHT_MODE_WP_MODE_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Flight Management
// Function : Auto Flight Mode(WP Mode)
// Segment  : PCS
// Req ID   : R-FCSQC01-SFR-012
// Desc     : Auto mode로 수행되는 경로비행에 대한 비행절차 수행 및 목점점 계산
void pcs_flight_management_auto_flight_mode_wp_mode_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
