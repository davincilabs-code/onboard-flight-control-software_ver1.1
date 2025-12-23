#ifndef IOSS_SENSOR_DATA_MANAGEMENT_AIR_DATA_SENSOR_H
#define IOSS_SENSOR_DATA_MANAGEMENT_AIR_DATA_SENSOR_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Sensor Data Management
// Function : Air Data Sensor 
// Segment  : IOSS
// Req ID   : R-FCSQC01-IDR-006
// Desc     : Air speed Sensor data 입력
void ioss_sensor_data_management_air_data_sensor_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
