#ifndef PCS_GUIDANCE_AND_NAVIGATION_MANAGEMENT_TAGET_POSTURE_GENERATOR_H
#define PCS_GUIDANCE_AND_NAVIGATION_MANAGEMENT_TAGET_POSTURE_GENERATOR_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Guidance & Navigation Management
// Function : Taget Posture Generator
// Segment  : PCS
// Req ID   : R-FCSQC01-SFR-017
// Desc     : RC, Pilot, Auto Flight별 목표점 및 자세 생성 기능
void pcs_guidance_and_navigation_management_taget_posture_generator_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
