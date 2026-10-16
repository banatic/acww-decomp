/* A job run on a thread of its own (0x10ec bytes from the heap data_021fbe94, kept in the word
 * 0x20 of data_021c779c): the NitroSDK thread first, its stack after it, and three flags at the
 * end. func_02042458 makes it, func_02042324 starts the thread (func_0204234c) and
 * func_020422f8 asks whether it is done; WorkerThread_Release ends it. */
#ifndef CLEAN_MAIN_WORKER_THREAD_H
#define CLEAN_MAIN_WORKER_THREAD_H

#include "autoload_2/heap.h"
#include "calendar.h"
#include "types.h"

typedef struct WorkerThread {
    u8 thread[0xc0]; /* the OSThread */
    u8 unk_c0[0x1028];
    u8 ready;   /* 0x10e8: the thread may be started */
    u8 done;    /* 0x10e9: the job is over */
    u8 started; /* 0x10ea: the thread was created */
    u8 unk_10eb;
} WorkerThread;

/* data_021c779c */
typedef struct WorkerThreadOwner {
    u8 unk_00[0x20];
    WorkerThread *job; /* 0x20: NULL when there is none */
} WorkerThreadOwner;

void WorkerThread_Release(void);
void WorkerThread_Stop(WorkerThread *job);

/* The words after the thread (WorkerThread.unk_c0, WorkerThread_Context): who started it and the
 * job's arguments, then its stack between two guard words. */
#define WORKER_THREAD_STACK_SIZE 0x1000
#define WORKER_THREAD_PRIORITY 0x1e
#define WORKER_THREAD_GUARD 0x3039

/* What the thread hands to func_0204714c: the town's change from one date to another. */
typedef struct WorkerThreadDays {
    DateTime from; /* 0x00 */
    DateTime to;   /* 0x08 */
    int days;      /* 0x10 */
    u8 mode;       /* 0x14 */
    u8 unk_15[3];
} WorkerThreadDays;

typedef struct WorkerThreadContext {
    struct OSThread *caller; /* 0xc0: the thread that started the job */
    Heap *heap;              /* 0xc4: the heap data_021fbe94 was when it started */
    WorkerThreadDays days;   /* 0xc8: the thread's argument */
    u32 guard;               /* 0xe0: WORKER_THREAD_GUARD */
    u8 stack[WORKER_THREAD_STACK_SIZE];
    u32 stack_top; /* 0x10e4: WORKER_THREAD_GUARD, where the stack starts */
} WorkerThreadContext;

int WorkerThread_TakeDone(void);
int WorkerThread_StartJob(void);
int WorkerThread_Start(WorkerThread *job);
void WorkerThread_SetDays(const DateTime *from, const DateTime *to, u32 days, u32 mode);
void WorkerThread_SetJobDays(WorkerThread *job, const DateTime *from, const DateTime *to, int days, u8 mode);
void WorkerThread_Create(void);
int WorkerThread_Init(WorkerThread *job);
void WorkerThread_Run(void *argument);

#endif
