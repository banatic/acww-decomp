/* The destructors of main's process of class data_020daae4 (process_020daae4.h). */
#include "process_020daae4.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "event_entries.h"
#include "link_scene.h"
#include "object_claim.h"
#include "scene_process_base.h"

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

/* ---- Its execute and draw (vtable slots 6, 8 and 9) ---- */

#include "event_queue.h"
#include "itcm/process_phases.h"

/* The events waiting (event_queue.h). */
extern List data_021c72c4;
/* The scene's process, or NULL. */
extern Process *data_021f42f4;

/* func_0203e514 (slot 6): the current event stepped (running, then ending); without one, the
 * next queued one taken; a current one stepped while starting; then every event still queued
 * is dropped. Done at once (1).
 * QUIRK: an event asked for and not taken in the frame it was asked for is freed. */
int Process020daae4_Execute(Process *process)
{
    if (EventQueue_HasCurrent()) {
        EventQueue_StepRunning(process);
        EventQueue_StepEnding(process);
    }
    if (!EventQueue_HasCurrent()) {
        EventQueue_TakeNext(process);
    }
    if (EventQueue_HasCurrent()) {
        EventQueue_StepStarting(process);
    }
    EventEntries_FreeList(&data_021c72c4);
    return 1;
}
CLEAN_AS(func_0203e514, Process020daae4_Execute)

/* func_0203e4e0 (slot 8): func_020a6d24, func_020a6ce4, the scene's process given to
 * func_020a529c when there is one, then the base class's after-execute. */
void Process020daae4_AfterExecute(Process *process, int outcome)
{
    (void) outcome;
    LinkScene_SendLeftState();
    LinkScene_SendAskedState();
    if (data_021f42f4 != NULL) {
        SceneProcessBase_CheckChange(data_021f42f4);
    }
    Process_AfterExecute(process);
}
CLEAN_AS(func_0203e4e0, Process020daae4_AfterExecute)

/* func_0203e510 (slot 9): nothing to draw; done at once. */
int Process020daae4_Draw(void)
{
    return 1;
}
CLEAN_AS(func_0203e510, Process020daae4_Draw)

/* ---- Its creation and deletion (slots 0 and 3) ---- */

/* The flags of main's queue of events (event_queue.h). */
extern u32 data_021c72c0;

/* func_0203ec78 (slot 0): the queue of events started over, the session's slots cleared and
 * every flag cleared; done at once. */
int Process020daae4_Create(void)
{
    EventQueue_Reset();
    ObjectClaim_Reset();
    data_021c72c0 = 0;
    return 1;
}
CLEAN_AS(func_0203ec78, Process020daae4_Create)

/* func_0203ec74 (slot 3): deleted at once. */
int Process020daae4_Delete(void)
{
    return 1;
}
CLEAN_AS(func_0203ec74, Process020daae4_Delete)

/* func_0203ed2c (its profile's creation function): a new process of 0x50 bytes from the
 * auxiliary heap, constructed with the root class's vtable and then its own; NULL when the
 * allocation fails. */
Process *Process020daae4_New(void)
{
    Process *process = Heap_AllocAuxZeroed(0x50);

    if (process != NULL) {
        Process_Construct(process);
        process->vtable = data_020da13c;
        process->vtable = data_020daae4;
    }
    return process;
}
CLEAN_AS(func_0203ed2c, Process020daae4_New)
