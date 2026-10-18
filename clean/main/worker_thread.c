/* A job run on a thread of its own (worker_thread.h). */
#include "worker_thread.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "town_day.h"

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

static_assert(offsetof(WorkerThread, unk_c0) == 0xc0, "WorkerThread.unk_c0");
static_assert(sizeof(WorkerThreadContext) == sizeof(((WorkerThread *) NULL)->unk_c0), "WorkerThreadContext");
static_assert(offsetof(WorkerThreadContext, days) == 0xc8 - 0xc0, "WorkerThreadContext.days");
static_assert(offsetof(WorkerThreadContext, stack_top) == 0x10e4 - 0xc0, "WorkerThreadContext.stack_top");
static_assert(offsetof(WorkerThreadDays, mode) == 0x14, "WorkerThreadDays.mode");

/* NitroSDK's thread calls and its record of the threads (current: the running one). */
typedef struct WorkerThreadOsInfo {
    u16 is_need_rescheduling;
    u16 irq_depth;
    struct OSThread *current;
} WorkerThreadOsInfo;

extern WorkerThreadOsInfo OSi_ThreadInfo;
extern void OS_CreateThread(struct OSThread *thread, void (*function)(void *), void *argument, void *stack, u32 size,
                            u32 priority);
extern void OS_WakeupThreadDirect(struct OSThread *thread);
extern void OS_ExitThread(void);
extern void DC_FlushAll(void);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* The job thread's function, handed to OS_CreateThread (WorkerThread_Run). */
extern void func_020424b4(void *argument);

/* NitroSDK's OSThread keeps its state at 0x64; 2 is "terminated". */
#define WORKER_THREAD_OS_STATE 0x64
#define WORKER_THREAD_OS_TERMINATED 2

static WorkerThreadContext *WorkerThread_Context(WorkerThread *job)
{
    return (WorkerThreadContext *) job->unk_c0;
}

/* func_020422f8: whether the job is over; when it is, it is released (1). 0 while it runs or
 * when there is none. */
int WorkerThread_TakeDone(void)
{
    WorkerThread *job = data_021c779c.job;
    if (job != NULL && job->done) {
        WorkerThread_Release();
        return 1;
    }
    return 0;
}
CLEAN_AS(func_020422f8, WorkerThread_TakeDone)

/* func_02042324: the job's thread started; a job that cannot start (no arguments were set) is
 * released. 1 when it started, 0 otherwise or when there is no job. */
int WorkerThread_StartJob(void)
{
    WorkerThread *job = data_021c779c.job;
    if (job == NULL) {
        return 0;
    }
    int started = WorkerThread_Start(job);
    if (!started) {
        WorkerThread_Release();
    }
    return started;
}
CLEAN_AS(func_02042324, WorkerThread_StartJob)

/* func_0204234c: once its arguments are set (`ready`), the job's thread created on its own
 * stack with func_020424b4 and woken. The starting thread gives its heap (data_021fbe94) to the
 * job's thread for the time it runs; WorkerThread_Run gives it back. 0 when not ready. */
int WorkerThread_Start(WorkerThread *job)
{
    WorkerThreadContext *context = WorkerThread_Context(job);
    if (!job->ready) {
        return 0;
    }
    context->guard = WORKER_THREAD_GUARD;
    context->stack_top = WORKER_THREAD_GUARD;
    job->done = 0;
    job->started = 1;
    OS_CreateThread((struct OSThread *) job->thread, func_020424b4, &context->days, &context->stack_top,
                    WORKER_THREAD_STACK_SIZE, WORKER_THREAD_PRIORITY);
    context->caller = OSi_ThreadInfo.current;
    context->heap = data_021fbe94;
    Heap_SetThreadHeap(context->caller, NULL);
    Heap_SetThreadHeap((struct OSThread *) job->thread, context->heap);
    OS_WakeupThreadDirect((struct OSThread *) job->thread);
    return 1;
}
CLEAN_AS(func_0204234c, WorkerThread_Start)

/* func_020423ec: the job's arguments set, when there is a job. */
void WorkerThread_SetDays(const DateTime *from, const DateTime *to, u32 days, u32 mode)
{
    WorkerThread *job = data_021c779c.job;
    if (job != NULL) {
        WorkerThread_SetJobDays(job, from, to, (int) days, (u8) mode);
    }
}
CLEAN_AS(func_020423ec, WorkerThread_SetDays)

/* func_02042418: the dates, the number of days and the mode copied into the job, which may then
 * start. */
void WorkerThread_SetJobDays(WorkerThread *job, const DateTime *from, const DateTime *to, int days, u8 mode)
{
    WorkerThreadContext *context = WorkerThread_Context(job);
    MI_CpuCopy8(from, &context->days.from, sizeof(DateTime));
    MI_CpuCopy8(to, &context->days.to, sizeof(DateTime));
    context->days.days = days;
    context->days.mode = mode;
    job->ready = 1;
}
CLEAN_AS(func_02042418, WorkerThread_SetJobDays)

/* func_02042458: a job allocated (0x10ec bytes from the heap data_021fbe94) and set up. */
void WorkerThread_Create(void)
{
    WorkerThread *job = Heap_Alloc(data_021fbe94, sizeof(WorkerThread));
    data_021c779c.job = job;
    if (job != NULL) {
        WorkerThread_Init(job);
    }
}
CLEAN_AS(func_02042458, WorkerThread_Create)

/* func_02042484: the flags cleared and the thread record zeroed, marked terminated so that
 * WorkerThread_Stop leaves it alone. Gives that state, 2. */
int WorkerThread_Init(WorkerThread *job)
{
    job->ready = 0;
    job->done = 0;
    job->started = 0;
    MI_CpuFill8(job->thread, 0, sizeof(job->thread));
    *(u32 *) (job->thread + WORKER_THREAD_OS_STATE) = WORKER_THREAD_OS_TERMINATED;
    return WORKER_THREAD_OS_TERMINATED;
}
CLEAN_AS(func_02042484, WorkerThread_Init)

/* func_020424b4: the job's thread: the town's change between the two dates made, the heap given
 * back to the thread that started the job, the job marked done, and the thread ended. */
void WorkerThread_Run(void *argument)
{
    WorkerThreadDays *days = argument;
    DC_FlushAll();
    WorkerThread *job = data_021c779c.job;
    TownDay_Pass((TownDay *) &data_021c779c, &days->from, &days->to, (u32) days->days, days->mode, 1);
    WorkerThreadContext *context = WorkerThread_Context(job);
    Heap_SetThreadHeap(context->caller, context->heap);
    job->done = 1;
    OS_ExitThread();
}
CLEAN_AS(func_020424b4, WorkerThread_Run)
