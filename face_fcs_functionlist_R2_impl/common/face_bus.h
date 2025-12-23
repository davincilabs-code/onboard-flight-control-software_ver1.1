#ifndef FACE_BUS_H
#define FACE_BUS_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    TOPIC_PILOT_INPUT = 1,
    TOPIC_NAV_STATE   = 2,
    TOPIC_GUIDANCE_REF= 3,
    TOPIC_ACTUATOR_CMD= 4,
    TOPIC_FAULTS      = 5,
    TOPIC_ALARMS      = 6,
    TOPIC_TEXT_EVENT  = 7
} FaceTopic;

typedef struct {
    FaceTopic topic;
    uint64_t  t_us;
    uint16_t  len;
    uint8_t   payload[256];
} FaceMsg;

// Ring-buffer bus. Single-producer/single-consumer in demo.
void face_bus_init(void);
bool face_bus_publish(FaceTopic topic, uint64_t t_us, const void* data, size_t len);
bool face_bus_latest(FaceTopic topic, FaceMsg* out);

#ifdef __cplusplus
}
#endif
#endif
