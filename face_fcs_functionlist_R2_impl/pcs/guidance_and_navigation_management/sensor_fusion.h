#ifndef PCS_GUIDANCE_AND_NAVIGATION_MANAGEMENT_SENSOR_FUSION_H
#define PCS_GUIDANCE_AND_NAVIGATION_MANAGEMENT_SENSOR_FUSION_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Guidance & Navigation Management
// Function : Sensor Fusion
// Segment  : PCS
// Req ID   : R-FCSQC01-SFR-018
// Desc     : 센서 융합 알고리즘 통한 자기 위치 및 자세 추정
void pcs_guidance_and_navigation_management_sensor_fusion_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
