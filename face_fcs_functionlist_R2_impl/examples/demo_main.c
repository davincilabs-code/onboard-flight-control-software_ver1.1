#include "face_context.h"
#include "face_bus.h"
#include "face_time.h"
#include "face_log.h"

// OSS functions
#include "oss/operarting_system_management/sytem_intializing.h"
#include "oss/operarting_system_management/task_allocation.h"
#include "oss/operarting_system_management/task_scheduling.h"
#include "oss/operarting_system_management/task_execution.h"

int main(void)
{
    FaceContext ctx;
    // Init system / bus / kernel
    oss_operarting_system_management_sytem_intializing_step(&ctx);

    // Register tasks and schedule them (demo)
    oss_operarting_system_management_task_allocation_step(&ctx);
    oss_operarting_system_management_task_scheduling_step(&ctx);

    face_log_info("Demo start: running 10 seconds");
    uint64_t start = face_time_now_us();
    while ((face_time_now_us() - start) < 10ull*1000000ull)
    {
        // Drive executor (runs due tasks)
        oss_operarting_system_management_task_execution_step(&ctx);

        // Fixed 10ms tick for demo timing
        face_time_sleep_us(10000);
    }
    face_log_info("Demo done");
    return 0;
}
