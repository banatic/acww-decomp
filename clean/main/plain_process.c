/* The process class that adds nothing (plain_process.h). */
#include "plain_process.h"

#include "autoload_2/heap.h"
#include "clean.h"

extern const u32 data_020e587c[]; /* this class's vtable */
extern const u32 data_020da13c[]; /* the game's process class's */

/* func_020b920c (the profile's create): a zeroed object from the auxiliary heap, constructed
 * as a process, then as the game's process class and as this one; NULL when the heap is full. */
Process *PlainProcess_Create(void)
{
    Process *self = Heap_AllocAuxZeroed(sizeof(Process));

    if (self != NULL) {
        Process_Construct(self);
        self->vtable = data_020da13c;
        self->vtable = data_020e587c;
    }
    return self;
}
CLEAN_AS(func_020b920c, PlainProcess_Create)

/* func_020b9238 (vtable slot 16): the destructor, through the game's process class down to the
 * base's. */
Process *PlainProcess_Destroy(Process *self)
{
    self->vtable = data_020e587c;
    self->vtable = data_020da13c;
    Process_Destruct(self);
    return self;
}
CLEAN_AS(func_020b9238, PlainProcess_Destroy)

/* func_020b9258 (vtable slot 17): destroyed and freed to the auxiliary heap. */
Process *PlainProcess_Delete(Process *self)
{
    self->vtable = data_020e587c;
    self->vtable = data_020da13c;
    Process_Destruct(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_020b9258, PlainProcess_Delete)
