/* The process of vtable data_020dabc0: a bare process (0x50 bytes, made by func_0204087c) of
 * main whose execute (func_0203fb18) runs date checks (func_02040bfc). */
#ifndef CLEAN_MAIN_PROCESS_020DABC0_H
#define CLEAN_MAIN_PROCESS_020DABC0_H

#include "autoload_2/process.h"
#include "types.h"

Process *Process020dabc0_Destruct(Process *process);
Process *Process020dabc0_DestructFree(Process *process);
int Process020dabc0_IsHeldBack(void);

int Process020dabc0_Create(void);
int Process020dabc0_Delete(void);
int Process020dabc0_Execute(Process *process);
int Process020dabc0_Draw(void);
Process *Process020dabc0_New(void);

#endif
