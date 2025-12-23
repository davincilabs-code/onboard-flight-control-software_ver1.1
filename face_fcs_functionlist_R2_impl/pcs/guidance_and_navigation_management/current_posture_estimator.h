#ifndef PCS_GUIDANCE_AND_NAVIGATION_MANAGEMENT_CURRENT_POSTURE_ESTIMATOR_H
#define PCS_GUIDANCE_AND_NAVIGATION_MANAGEMENT_CURRENT_POSTURE_ESTIMATOR_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Guidance & Navigation Management
// Function : Current Posture Estimator
// Segment  : PCS
// Req ID   : R-FCSQC01-SFR-019
// Desc     : 자기 위치 추정 기능(위치,자세, 속도, 각속도, 가속도, 각가속도)
void pcs_guidance_and_navigation_management_current_posture_estimator_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
