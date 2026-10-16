/* The destructors of main's process of class data_020daae4 (process_020daae4.h). */
#include "process_020daae4.h"

#include "autoload_2/heap.h"
#include "clean.h"

extern const u32 data_020daae4[]; /* its class */
extern const u32 data_020da13c[]; /* the processes' root class */

/* func_0203de7c: the destructor: its vtable, the root class's, then the process destructor. */
Process *Process020daae4_Destruct(Process *process)
{
    process->vtable = data_020daae4;
    process->vtable = data_020da13c;
    Process_Destruct(process);
    return process;
}
CLEAN_AS(func_0203de7c, Process020daae4_Destruct)

/* func_0203de9c: the destructor, then the process freed. */
Process *Process020daae4_DestructFree(Process *process)
{
    process->vtable = data_020daae4;
    process->vtable = data_020da13c;
    Process_Destruct(process);
    Heap_FreeAux(process);
    return process;
}
CLEAN_AS(func_0203de9c, Process020daae4_DestructFree)
