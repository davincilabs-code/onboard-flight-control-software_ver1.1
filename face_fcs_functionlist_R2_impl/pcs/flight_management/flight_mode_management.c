#include "face_context.h"
#include "face_log.h"

void pcs_flight_management_flight_mode_management_step(FaceContext* ctx)
{
    // Decide mode based on faults and pilot switch
    if (ctx->faults.sensor_fault || ctx->faults.engine_fault || ctx->faults.battery_fault){
        ctx->mode = FLIGHT_MODE_EMERGENCY;
    } else {
        if (ctx->pilot_in.mode_switch == 1) ctx->mode = FLIGHT_MODE_AUTO;
        else if (ctx->pilot_in.mode_switch == 2) ctx->mode = FLIGHT_MODE_EMERGENCY;
        else ctx->mode = FLIGHT_MODE_MANUAL;
    }

    // Phase management (very simple demo)
    if (ctx->mode != FLIGHT_MODE_AUTO){
        if (ctx->nav.z_m < 1.0) ctx->phase = FLIGHT_PHASE_GROUND;
        else ctx->phase = FLIGHT_PHASE_HOVER;
        return;
    }

    // Auto phase transitions
    if (ctx->phase == FLIGHT_PHASE_GROUND) ctx->phase = FLIGHT_PHASE_TAKEOFF;

    if (ctx->phase == FLIGHT_PHASE_TAKEOFF && ctx->nav.z_m >= ctx->takeoff_alt_m - 1.0){
        ctx->phase = FLIGHT_PHASE_HOVER;
        face_log_info("PHASE: TAKEOFF -> HOVER");
    }
    if (ctx->phase == FLIGHT_PHASE_HOVER && ctx->air.airspeed_m_s >= 5.0){
        ctx->phase = FLIGHT_PHASE_TRANSITION;
        face_log_info("PHASE: HOVER -> TRANSITION");
    }
    if (ctx->phase == FLIGHT_PHASE_TRANSITION && ctx->air.airspeed_m_s >= ctx->cruise_speed_m_s - 1.0){
        ctx->phase = FLIGHT_PHASE_CRUISE;
        face_log_info("PHASE: TRANSITION -> CRUISE");
    }
}
