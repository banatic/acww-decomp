/* A job run on a thread of its own (worker_thread.h). */
#include "worker_thread.h"

#include "autoload_2/heap.h"
#include "clean.h"

static_assert(offsetof(WorkerThread, ready) == 0x10e8, "WorkerThread.ready");
static_assert(sizeof(WorkerThread) == 0x10ec, "WorkerThread");
static_assert(offsetof(WorkerThreadOwner, job) == 0x20, "WorkerThreadOwner.job");

extern int OS_IsThreadTerminated(void *thread);
extern void OS_KillThread(void *thread, void *argument);

extern WorkerThreadOwner data_021c779c;
extern Heap *data_021fbe94;

/* func_020422a0: the job, if any, ended: its thread stopped, its memory freed to the heap
 * data_021fbe94 (whichever heap that is now) and forgotten. */
void WorkerThread_Release(void)
{
    WorkerThread *job = data_021c779c.job;
    if (job == NULL) {
        return;
    }
    WorkerThread_Stop(job);
    Heap_Free(data_021fbe94, job);
    data_021c779c.job = NULL;
}
CLEAN_AS(func_020422a0, WorkerThread_Release)

/* func_020422d0: a started job's thread killed unless it has ended. */
void WorkerThread_Stop(WorkerThread *job)
{
    if (job->started && !OS_IsThreadTerminated(job)) {
        OS_KillThread(job, NULL);
    }
}
CLEAN_AS(func_020422d0, WorkerThread_Stop)
