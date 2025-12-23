#ifndef PSSS_SYSTEM_MANAGEMENT_SENSOR_MANAGER_H
#define PSSS_SYSTEM_MANAGEMENT_SENSOR_MANAGER_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: System Management
// Function : Sensor Manager
// Segment  : PSSS
// Req ID   : R-FCSQC01-SFR-034
// Desc     : 센서 상태 및 이중화 대응 관리자, 캘리브레이션
void psss_system_management_sensor_manager_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
