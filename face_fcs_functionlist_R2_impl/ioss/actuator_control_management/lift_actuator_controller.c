#include "face_context.h"
#include "face_bus.h"
#include "face_log.h"
#include <stdio.h>

void ioss_actuator_control_management_lift_actuator_controller_step(FaceContext* ctx)
{
    // In real system this would send to ESC/servo drivers.
    face_bus_publish(TOPIC_ACTUATOR_CMD, ctx->now_us, &ctx->act, sizeof(ctx->act));
    face_log_info("ACT: lift=%.2f roll=%.2f pitch=%.2f yaw=%.2f",
                  ctx->act.lift_thrust, ctx->act.roll_cmd, ctx->act.pitch_cmd, ctx->act.yaw_cmd);
}
