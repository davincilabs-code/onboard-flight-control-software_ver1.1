#ifndef IOSS_SENSOR_DATA_MANAGEMENT_RALT_SENSOR_H
#define IOSS_SENSOR_DATA_MANAGEMENT_RALT_SENSOR_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Sensor Data Management
// Function : RALT Sensor
// Segment  : IOSS
// Req ID   : R-FCSQC01-IDR-008
// Desc     : RALT Sensor data 입력
void ioss_sensor_data_management_ralt_sensor_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
