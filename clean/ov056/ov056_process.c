/* The process class of overlay 56 that adds nothing (ov056_process.h). */
#include "ov056_process.h"

#include "autoload_2/heap.h"
#include "clean.h"

static_assert(sizeof(Process) == 0x50, "the size Ov056Process_Create allocates");

extern const u32 data_ov056_022604b0[]; /* this class's vtable */
extern const u32 data_020da13c[];       /* the game's process class's */

/* func_ov056_02260420 (the profile's create): a zeroed object from the auxiliary heap,
 * constructed as a process, then as the game's process class and as this one; NULL when the
 * heap is full. */
Process *Ov056Process_Create(void)
{
    Process *self = Heap_AllocAuxZeroed(sizeof(Process));

    if (self != NULL) {
        Process_Construct(self);
        self->vtable = data_020da13c;
        self->vtable = data_ov056_022604b0;
    }
    return self;
}
CLEAN_AS(func_ov056_02260420, Ov056Process_Create)

/* func_ov056_0226044c (vtable slot 16): the destructor, through the game's process class down
 * to the base's. */
Process *Ov056Process_Destroy(Process *self)
{
    self->vtable = data_ov056_022604b0;
    self->vtable = data_020da13c;
    Process_Destruct(self);
    return self;
}
CLEAN_AS(func_ov056_0226044c, Ov056Process_Destroy)

/* func_ov056_0226046c (vtable slot 17): destroyed and freed to the auxiliary heap. */
Process *Ov056Process_Delete(Process *self)
{
    self->vtable = data_ov056_022604b0;
    self->vtable = data_020da13c;
    Process_Destruct(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov056_0226046c, Ov056Process_Delete)
