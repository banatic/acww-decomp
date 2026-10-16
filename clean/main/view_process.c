/* The process with a view matrix (view_process.h). */
#include "view_process.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "display_3d.h"

static_assert(sizeof(Process) == 0x50, "Process");
static_assert(offsetof(ViewProcess, view) == 0x50, "ViewProcess");

extern const u32 data_020e58cc[]; /* this class's vtable */
extern const u32 data_020da13c[]; /* the game's process class's */

/* func_020b941c (vtable slot 16): the destructor, through the game's process class down to the
 * base's. */
ViewProcess *ViewProcess_Destroy(ViewProcess *self)
{
    self->base.vtable = data_020e58cc;
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
    return self;
}
CLEAN_AS(func_020b941c, ViewProcess_Destroy)

/* func_020b943c (vtable slot 17): destroyed and freed to the auxiliary heap. */
ViewProcess *ViewProcess_Delete(ViewProcess *self)
{
    self->base.vtable = data_020e58cc;
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_020b943c, ViewProcess_Delete)

/* func_020b9464 (vtable slot 9, the DRAW phase's work): the view matrix made the 3D view; done
 * at once (1). */
int ViewProcess_Draw(ViewProcess *self)
{
    Display3D_SetViewMatrix(&self->view);
    return 1;
}
CLEAN_AS(func_020b9464, ViewProcess_Draw)
