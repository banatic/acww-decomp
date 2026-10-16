/* A job run on a thread of its own (0x10ec bytes from the heap data_021fbe94, kept in the word
 * 0x20 of data_021c779c): the NitroSDK thread first, its stack after it, and three flags at the
 * end. func_02042458 makes it, func_02042324 starts the thread (func_0204234c) and
 * func_020422f8 asks whether it is done; WorkerThread_Release ends it. */
#ifndef CLEAN_MAIN_WORKER_THREAD_H
#define CLEAN_MAIN_WORKER_THREAD_H

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

#endif
