#ifndef FACE_CONTEXT_H
#define FACE_CONTEXT_H

#include "face_types.h"
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    // Time
    uint64_t now_us;
    double   dt_s;

    // Inputs / samples
    PilotInput pilot_in;
    AhrsSample ahrs;
    GpsSample  gps;
    AirDataSample air;
    RaltSample ralt;

    // Estimated state + targets + outputs
    NavState nav;
    GuidanceRef ref;
    ActuatorCmd act;

    // Mode & phase
    FlightMode mode;
    FlightPhase phase;

    // Managers
    FaultFlags faults;
    uint8_t active_fcc; // 0/1 for dual FCC demo
    Alarms alarms;

    // Kinematics helpers
    bool wow; // weight-on-wheels (demo)

    // Config / parameters (demo)
    double takeoff_alt_m;
    double hover_alt_m;
    double cruise_speed_m_s;
} FaceContext;

void face_context_init(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
