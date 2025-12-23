#ifndef IOSS_ACTUATOR_CONTROL_MANAGEMENT_LIFT_ACTUATOR_CONTROLLER_H
#define IOSS_ACTUATOR_CONTROL_MANAGEMENT_LIFT_ACTUATOR_CONTROLLER_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Actuator Control Management
// Function : Lift Actuator Controller
// Segment  : IOSS
// Req ID   : R-FCSQC01-SFR-023
// Desc     : Lift Actuator에 명령값 전달
void ioss_actuator_control_management_lift_actuator_controller_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
