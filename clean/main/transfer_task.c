/* The base of the transfer queues' tasks (transfer_task.h). */
#include "transfer_task.h"

#include "clean.h"

extern const u32 data_020e5954[]; /* the base class's vtable: both slots empty */

/* func_020ba1bc: back to no kind, not queued, one line. */
void TransferTask_Reset(TransferTask *task)
{
    task->state = TRANSFER_TASK_IDLE;
    task->kind = TRANSFER_KIND_NONE;
    task->lines = 1;
}
CLEAN_AS(func_020ba1bc, TransferTask_Reset)

/* func_020ba1cc: the constructor: unlinked, the lowest priority, then as TransferTask_Reset
 * leaves it. */
void TransferTask_Construct(TransferTask *task)
{
    task->link.prev = NULL;
    task->link.next = NULL;
    task->priority = TRANSFER_TASK_PRIORITY_LAST;
    task->vtable = data_020e5954;
    task->state = TRANSFER_TASK_IDLE;
    task->kind = TRANSFER_KIND_NONE;
    task->lines = 1;
}
CLEAN_AS(func_020ba1cc, TransferTask_Construct)
