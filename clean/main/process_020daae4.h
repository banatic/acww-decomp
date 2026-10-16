/* A process of main (class data_020daae4, 0x50 bytes; func_0203ed2c allocates and builds it):
 * a process (autoload_2/process.h) with fields of its own. Here are its destructors. */
#ifndef CLEAN_MAIN_PROCESS_020DAAE4_H
#define CLEAN_MAIN_PROCESS_020DAAE4_H

#include "autoload_2/process.h"

Process *Process020daae4_Destruct(Process *process);
Process *Process020daae4_DestructFree(Process *process);

/* Its vtable's own execute (slot 6), after-execute (slot 8) and draw (slot 9): it runs main's
 * queue of events (event_queue.h). */
int Process020daae4_Execute(Process *process);
void Process020daae4_AfterExecute(Process *process, int outcome);
int Process020daae4_Draw(void);

/* Its creation (slot 0), deletion (slot 3), and the profile's function that makes one. */
int Process020daae4_Create(void);
int Process020daae4_Delete(void);
Process *Process020daae4_New(void);

#endif
