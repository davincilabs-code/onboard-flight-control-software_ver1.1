#ifndef IOSS_SENSOR_DATA_MANAGEMENT_GPS_SENSOR_H
#define IOSS_SENSOR_DATA_MANAGEMENT_GPS_SENSOR_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Sensor Data Management
// Function : GPS Sensor
// Segment  : IOSS
// Req ID   : R-FCSQC01-IDR-007
// Desc     : GPS Sensor data 입력
void ioss_sensor_data_management_gps_sensor_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
