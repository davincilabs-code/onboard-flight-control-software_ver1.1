#ifndef PSSS_I_O_PROCESSING_MANAGEMENT_IO_MANAGEMENT_H
#define PSSS_I_O_PROCESSING_MANAGEMENT_IO_MANAGEMENT_H

#include "face_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component: I/O Processing Management
// Function : IO Management
// Segment  : PSSS
// Req ID   : R-FCSQC01-IDR-001
// Desc     : 아날로그, 디지털 IO 관리자
void psss_i_o_processing_management_io_management_step(FaceContext* ctx);

#ifdef __cplusplus
}
#endif

#endif
