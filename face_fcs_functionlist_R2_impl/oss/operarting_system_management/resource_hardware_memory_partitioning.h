#ifndef OSS_OPERARTING_SYSTEM_MANAGEMENT_RESOURCE_HARDWARE_MEMORY_PARTITIONING_H
#define OSS_OPERARTING_SYSTEM_MANAGEMENT_RESOURCE_HARDWARE_MEMORY_PARTITIONING_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: Operarting System Management
// Function : Resource(Hardware/Memory) Partitioning
// Segment  : OSS
// Req ID   : R-FCSQC01-ECRR-011
// Desc     : 태스크별 프로세서 / 메모리 할당
void oss_operarting_system_management_resource_hardware_memory_partitioning_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
