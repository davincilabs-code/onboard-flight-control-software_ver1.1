#include "face_context.h"
#include "face_log.h"

void psss_i_o_processing_management_analog_input_data_processing_step(FaceContext* ctx)
{
    // Demo: inputs are already in ctx->pilot_in
    (void)ctx;
    face_log_info("PSSS: Analog Input Data Processing ok");
}
