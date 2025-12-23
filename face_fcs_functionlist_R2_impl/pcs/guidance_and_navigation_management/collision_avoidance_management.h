#ifndef PCS_GUIDANCE_AND_NAVIGATION_MANAGEMENT_COLLISION_AVOIDANCE_MANAGEMENT_H
#define PCS_GUIDANCE_AND_NAVIGATION_MANAGEMENT_COLLISION_AVOIDANCE_MANAGEMENT_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Guidance & Navigation Management
// Function : Collision Avoidance Management
// Segment  : PCS
// Req ID   : R-FCSQC01-SFR-020
// Desc     : 장애물 감지 및 회피 절차 수행
void pcs_guidance_and_navigation_management_collision_avoidance_management_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
