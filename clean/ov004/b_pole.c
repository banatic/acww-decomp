/* The room object of /roomObj/obj_b_pole (b_pole.h). */
#include "b_pole.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/animated_model.h"
#include "ov004/rmo_model.h"
#include "ov004/rmo_object_slots.h"
#include "rmo_object_base.h"

static_assert(sizeof(BPole) == 0x290, "the size BPole_Create allocates");

#define B_POLE_ONE 0x1000 /* normal speed, 20.12 fixed point */
#define B_POLE_LOOP 0     /* FrameCtrlFlags: the animation starts over at its end */

/* The class's vtable. */
extern const u8 data_ov004_02255290[];

/* "obj_b_pole", the archive's name. */
extern const char data_ov004_022552f8[];

extern Heap *data_021c9b24;

/* The RMO family's base class (rmo_object.h). */

static AnimatedModel *BPole_body(BPole *self)
{
    return (AnimatedModel *) (void *) &self->base.body;
}

/* func_ov004_0222f368 (vtable slot 0x0c): the archive released. */
int BPole_Release(BPole *self)
{
    RmoObjectSlots_ReleaseBody(&self->base);
    return 1;
}
CLEAN_AS(func_ov004_0222f368, BPole_Release)

/* func_ov004_0222f378 (vtable slot 0x24) */
int BPole_Draw(BPole *self)
{
    AnimatedModel_Draw(BPole_body(self), NULL);
    return 1;
}
CLEAN_AS(func_ov004_0222f378, BPole_Draw)

/* func_ov004_0222f38c (vtable slot 0x18): the animation steps. */
int BPole_Update(BPole *self)
{
    AnimatedModel_StepFrames(BPole_body(self));
    return 1;
}
CLEAN_AS(func_ov004_0222f38c, BPole_Update)

/* func_ov004_0222f3a0 (vtable slot 0x00): the archive loaded and, when it has a first joint
 * animation that the model can take, that animation looped from its start. */
int BPole_Start(BPole *self)
{
    RmoObjectSlots_LoadNamed(&self->base, data_ov004_022552f8);
    if (RmoModel_JointAnim(&self->base.body_model, 0) != NULL &&
        AnimatedModel_LoadAnim(BPole_body(self), data_021c9b24) != 0) {
        AnimatedModel_Start(BPole_body(self), RmoModel_JointAnim(&self->base.body_model, 0), B_POLE_LOOP, B_POLE_ONE, 0, 0);
        AnimatedModel_Attach(BPole_body(self));
    }
    return 1;
}
CLEAN_AS(func_ov004_0222f3a0, BPole_Start)

/* func_ov004_0222f408 (vtable slot 0x44): taken down and freed. */
BPole *BPole_Delete(BPole *self)
{
    self->base.actor.vtable = data_ov004_02255290;
    RmoObjectSlots_Destruct(&self->base);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_0222f408, BPole_Delete)

/* func_ov004_0222f428 (vtable slot 0x40) */
BPole *BPole_Destruct(BPole *self)
{
    self->base.actor.vtable = data_ov004_02255290;
    RmoObjectSlots_Destruct(&self->base);
    return self;
}
CLEAN_AS(func_ov004_0222f428, BPole_Destruct)

/* func_ov004_0222f440 */
BPole *BPole_Construct(BPole *self)
{
    RmoObjectBase_Construct(&self->base);
    self->base.actor.vtable = data_ov004_02255290;
    return self;
}
CLEAN_AS(func_ov004_0222f440, BPole_Construct)

/* func_ov004_0222f458: a new one from the room's heap; nothing when it has no room. */
void BPole_Create(void)
{
    BPole *self = Heap_AllocAuxZeroed(sizeof(BPole));
    if (self != NULL) {
        BPole_Construct(self);
    }
}
CLEAN_AS(func_ov004_0222f458, BPole_Create)
