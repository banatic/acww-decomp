/* The queues of tasks run in the display's free time (transfer_queue.h). */
#include "transfer_queue.h"

#include "clean.h"

static_assert(offsetof(TransferTask, link) == 0x04, "TransferTask");
static_assert(offsetof(TransferTask, lines) == 0x0f, "TransferTask");

#define REG_VCOUNT (*(const volatile u16 *) 0x04000006)

/* The last line each queue may run to. */
#define TRANSFER_QUEUE_MAIN_LAST_LINE 260
#define TRANSFER_QUEUE_VBLANK_LAST_LINE 212
/* After the VBlank queue, VCOUNT is read once more while the line is this or less. */
#define TRANSFER_QUEUE_VBLANK_REREAD_LINE 213

#define TRANSFER_TASK_SLOT_RUN 0

extern List data_021f6c98; /* the main loop's queue */
extern List data_021f6ca0; /* the VBlank's */

/* `node` inserted in `list` after the nodes of its priority or less; always 1. */
extern int func_02065c2c(List *list, ListNode *node);
/* `list` emptied. */
extern void func_02065c68(List *list);

typedef int TransferTaskRun(TransferTask *task);

static TransferTask *task_of(ListNode *node)
{
    return node != NULL ? (TransferTask *) (void *) ((u8 *) node - offsetof(TransferTask, link)) : NULL;
}

static ListNode *node_of(TransferTask *task)
{
    return task != NULL ? &task->link : NULL;
}

/* The queue's tasks in order while the next one fits before `last_line`: a queued task is run
 * (and marked done when it succeeds), then taken off the queue.
 * HW: VCOUNT is read before each task. */
static void run_queue(List *queue, int last_line)
{
    TransferTask *task = task_of(queue->first);

    while (task != NULL) {
        if (REG_VCOUNT + task->lines > last_line) {
            break;
        }
        if (task->state == TRANSFER_TASK_QUEUED) {
            TransferTaskRun *run = (TransferTaskRun *) (uintptr_t) task->vtable[TRANSFER_TASK_SLOT_RUN];
            if (run(task) != 0) {
                task->state = TRANSFER_TASK_DONE;
            }
        }
        List_Remove(queue, node_of(task));
        task = task_of(queue->first);
    }
}

/* func_020b983c: the main loop's queue, up to line 260. */
void TransferQueue_RunMain(void)
{
    run_queue(&data_021f6c98, TRANSFER_QUEUE_MAIN_LAST_LINE);
}
CLEAN_AS(func_020b983c, TransferQueue_RunMain)

/* func_020b98ac */
void TransferQueue_UnqueueMain(TransferTask *task)
{
    List_Remove(&data_021f6c98, node_of(task));
}
CLEAN_AS(func_020b98ac, TransferQueue_UnqueueMain)

/* func_020b98c4: always 1. */
int TransferQueue_QueueMain(TransferTask *task)
{
    return func_02065c2c(&data_021f6c98, node_of(task));
}
CLEAN_AS(func_020b98c4, TransferQueue_QueueMain)

/* func_020b98dc */
void TransferQueue_ClearMain(void)
{
    func_02065c68(&data_021f6c98);
}
CLEAN_AS(func_020b98dc, TransferQueue_ClearMain)

/* func_020b98ec: the VBlank's queue, up to line 212.
 * HW: then VCOUNT is read, and read a second time (the value unused) when it is 213 or less. */
void TransferQueue_RunVBlank(void)
{
    run_queue(&data_021f6ca0, TRANSFER_QUEUE_VBLANK_LAST_LINE);
    if (REG_VCOUNT <= TRANSFER_QUEUE_VBLANK_REREAD_LINE) {
        (void) REG_VCOUNT;
    }
}
CLEAN_AS(func_020b98ec, TransferQueue_RunVBlank)

/* func_020b9960: List_Remove's result. */
int TransferQueue_UnqueueVBlank(TransferTask *task)
{
    return List_Remove(&data_021f6ca0, node_of(task));
}
CLEAN_AS(func_020b9960, TransferQueue_UnqueueVBlank)

/* func_020b9978: always 1. */
int TransferQueue_QueueVBlank(TransferTask *task)
{
    return func_02065c2c(&data_021f6ca0, node_of(task));
}
CLEAN_AS(func_020b9978, TransferQueue_QueueVBlank)

/* func_020b9990 */
void TransferQueue_ClearVBlank(void)
{
    func_02065c68(&data_021f6ca0);
}
CLEAN_AS(func_020b9990, TransferQueue_ClearVBlank)
