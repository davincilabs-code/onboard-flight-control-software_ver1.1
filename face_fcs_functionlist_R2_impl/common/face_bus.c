#include "face_bus.h"
#include <string.h>

typedef struct {
    bool valid;
    FaceMsg msg;
} TopicSlot;

static TopicSlot g_slots[16];

void face_bus_init(void)
{
    memset(g_slots, 0, sizeof(g_slots));
}

static TopicSlot* slot_for(FaceTopic topic)
{
    for (size_t i=0;i<16;i++){
        if (!g_slots[i].valid || g_slots[i].msg.topic==topic) return &g_slots[i];
    }
    return NULL;
}

bool face_bus_publish(FaceTopic topic, uint64_t t_us, const void* data, size_t len)
{
    if (len > sizeof(((FaceMsg*)0)->payload)) return false;
    TopicSlot* s = slot_for(topic);
    if (!s) return false;
    s->valid = true;
    s->msg.topic = topic;
    s->msg.t_us = t_us;
    s->msg.len = (uint16_t)len;
    if (len>0 && data) memcpy(s->msg.payload, data, len);
    return true;
}

bool face_bus_latest(FaceTopic topic, FaceMsg* out)
{
    for (size_t i=0;i<16;i++){
        if (g_slots[i].valid && g_slots[i].msg.topic==topic){
            if (out) *out = g_slots[i].msg;
            return true;
        }
    }
    return false;
}
