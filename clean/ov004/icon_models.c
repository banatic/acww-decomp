/* The process of the items' icon models (icon_models.h). */
#include "icon_models.h"

#include "autoload_2/heap.h"
#include "clean.h"

static_assert(offsetof(IconModels, set) == 0x174, "icon models set");

/* The class and the process base's. */
extern const u32 data_ov004_02255bd4[];
extern const u32 data_020da13c[];

/* The model set taken down, then the base. */
static void IconModels_destruct_members(IconModels *self)
{
    self->base.vtable = data_ov004_02255bd4;
    ModelSet_Destruct(&self->set);
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
}

/* func_ov004_02233508 (the destructor, vtable slot 0x40) */
IconModels *IconModels_Destruct(IconModels *self)
{
    IconModels_destruct_members(self);
    return self;
}
CLEAN_AS(func_ov004_02233508, IconModels_Destruct)

/* func_ov004_02233538 (the deleting destructor, vtable slot 0x44) */
IconModels *IconModels_Delete(IconModels *self)
{
    IconModels_destruct_members(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_02233538, IconModels_Delete)
