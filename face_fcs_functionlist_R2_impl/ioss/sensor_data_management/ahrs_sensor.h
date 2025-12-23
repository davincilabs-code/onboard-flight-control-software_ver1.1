#ifndef IOSS_SENSOR_DATA_MANAGEMENT_AHRS_SENSOR_H
#define IOSS_SENSOR_DATA_MANAGEMENT_AHRS_SENSOR_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Sensor Data Management
// Function : AHRS Sensor
// Segment  : IOSS
// Req ID   : R-FCSQC01-IDR-009
// Desc     : AHRS Sensor data 입력
void ioss_sensor_data_management_ahrs_sensor_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
