#include "oss_kernel.h"
#include "face_time.h"
#include "face_log.h"
#include <stddef.h>

#define MAX_TASKS 96
static OssTask g_tasks[MAX_TASKS];
static int g_task_count = 0;

void oss_kernel_init(FaceContext* ctx)
{
    (void)ctx;
    g_task_count = 0;
    for (int i=0;i<MAX_TASKS;i++){
        g_tasks[i].enabled = false;
        g_tasks[i].name = NULL;
        g_tasks[i].fn = NULL;
        g_tasks[i].period_us = 0;
        g_tasks[i].next_release_us = 0;
        g_tasks[i].priority = 255;
    }
}

bool oss_kernel_add_task(const char* name, FaceTaskFn fn, uint32_t period_us, uint8_t priority)
{
    if (g_task_count >= MAX_TASKS) return false;
    OssTask* t = &g_tasks[g_task_count++];
    t->name = name;
    t->fn = fn;
    t->period_us = period_us;
    t->priority = priority;
    t->next_release_us = face_time_now_us();
    t->enabled = true;
    return true;
}

static void sort_by_priority(void)
{
    // simple insertion sort
    for (int i=1;i<g_task_count;i++){
        OssTask key = g_tasks[i];
        int j = i-1;
        while (j>=0 && g_tasks[j].priority > key.priority){
            g_tasks[j+1] = g_tasks[j];
            j--;
        }
        g_tasks[j+1] = key;
    }
}

void oss_kernel_step(FaceContext* ctx)
{
    sort_by_priority();
    uint64_t now = face_time_now_us();
    ctx->now_us = now;

    for (int i=0;i<g_task_count;i++){
        OssTask* t = &g_tasks[i];
        if (!t->enabled || !t->fn) continue;
        if (now >= t->next_release_us){
            t->fn(ctx);
            t->next_release_us = now + (uint64_t)t->period_us;
        }
    }
}
