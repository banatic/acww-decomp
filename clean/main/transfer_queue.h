/* Two queues of tasks that must run in the time the display leaves free (the game queues
 * texture copies on them): each task says how many scan lines it needs, and a queue is run, in
 * order, while the current line (VCOUNT) plus the next task's lines stays within the queue's
 * last line. One queue is run by the main loop (up to line 260), the other in the VBlank
 * interrupt (up to line 212). A task leaves its queue when its turn comes, whether it ran or not;
 * one that ran and reported success is marked done.
 *
 * The queues are kept in increasing `priority`: func_02065c2c inserts a task after those of the
 * same or a lower priority, but never before the first task. */
#ifndef CLEAN_MAIN_TRANSFER_QUEUE_H
#define CLEAN_MAIN_TRANSFER_QUEUE_H

#include "autoload_2/links.h"
#include "types.h"

/* A task's states. */
enum TransferTaskState {
    TRANSFER_TASK_QUEUED = 1, /* run when its turn comes */
    TRANSFER_TASK_DONE = 2,
};

/* A task (a C++ object): vtable slot 0 runs it (not 0 for success), slot 1 is called by its
 * owner when it could not be queued. */
typedef struct TransferTask {
    const u32 *vtable;
    ListNode link; /* 0x04 */
    u8 priority;   /* 0x0c */
    u8 state;      /* 0x0d: TransferTaskState */
    u8 kind;       /* 0x0e */
    u8 lines;      /* 0x0f: the scan lines it needs */
} TransferTask;

void TransferQueue_RunMain(void);
void TransferQueue_UnqueueMain(TransferTask *task);
int TransferQueue_QueueMain(TransferTask *task);
void TransferQueue_ClearMain(void);
void TransferQueue_RunVBlank(void);
int TransferQueue_UnqueueVBlank(TransferTask *task);
int TransferQueue_QueueVBlank(TransferTask *task);
void TransferQueue_ClearVBlank(void);

#endif
