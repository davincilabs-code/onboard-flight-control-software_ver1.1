#include "face_context.h"
#include "face_log.h"
#include <stdbool.h>

static bool g_paused = false;

void oss_operarting_system_management_system_pause_step(FaceContext* ctx)
{
    (void)ctx;
    g_paused = true;
    face_log_warn("OSS: System paused (demo flag set)");
}

bool oss_is_paused(void) { return g_paused; }
