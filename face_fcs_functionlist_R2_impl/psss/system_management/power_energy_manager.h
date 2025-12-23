#ifndef PSSS_SYSTEM_MANAGEMENT_POWER_ENERGY_MANAGER_H
#define PSSS_SYSTEM_MANAGEMENT_POWER_ENERGY_MANAGER_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: System Management
// Function : Power(Energy) Manager
// Segment  : PSSS
// Req ID   : R-FCSQC01-SFR-032
// Desc     : 동력원 상태 및 이상 대응 관리자
void psss_system_management_power_energy_manager_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
