#include "face_context.h"
#include "face_log.h"
#include "oss_kernel.h"

// Task functions are declared in generated registry
void oss_register_all_tasks(void);

void oss_operarting_system_management_task_allocation_step(FaceContext* ctx)
{
    (void)ctx;
    face_log_info("OSS: Task allocation (register tasks)");
    oss_register_all_tasks();
}
