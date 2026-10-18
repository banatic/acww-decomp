/* The RMO family's base class: its constructor and destructors (rmo_object_base.h). */
#include "rmo_object_base.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/animated_model.h"
#include "main/room_object_state.h"
#include "main/scene_object_base.h"
#include "rmo_model.h"

static_assert(sizeof(RmoObject) == 0x290, "RmoObject size");
static_assert(offsetof(RmoObject, body) == 0xec, "body");
static_assert(offsetof(RmoObject, body_model) == 0x1a4, "body model");
static_assert(offsetof(RmoObject, body_texture) == 0x248, "body texture");
static_assert(offsetof(RoomObject, state_number) == 0xea, "state number");

/* The sound source the objects play their sounds at (RmoSound_Play). */
#define RMO_OBJECT_BASE_SOUND_SOURCE 0x250

/* The class's vtable. */
extern const u8 data_ov004_02254b28[];

static void *RmoObjectBase_sound_source(RmoObject *self)
{
    return (u8 *) self + RMO_OBJECT_BASE_SOUND_SOURCE;
}

static SceneObjectBase *RmoObjectBase_scene_object(RmoObject *self)
{
    return (SceneObjectBase *) (void *) self;
}

static AnimatedModel *RmoObjectBase_body(RmoObject *self)
{
    return (AnimatedModel *) (void *) &self->body;
}

/* The parts taken down in the reverse of their construction, the scene object last. */
static void RmoObjectBase_take_down(RmoObject *self)
{
    self->actor.vtable = data_ov004_02254b28;
    RmoSound_Destruct(RmoObjectBase_sound_source(self));
    RmoTexture_Destruct(&self->body_texture);
    RmoModel_Destruct(&self->body_model);
    AnimatedModel_DestructComplete(RmoObjectBase_body(self));
    SceneObjectBase_DestructBase(RmoObjectBase_scene_object(self));
}

/* func_ov004_0222c7e8 (the deleting destructor, vtable slot 0x44): taken down and freed. */
RmoObject *RmoObjectBase_Delete(RmoObject *self)
{
    RmoObjectBase_take_down(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_0222c7e8, RmoObjectBase_Delete)

/* func_ov004_0222c834 (the destructor, vtable slot 0x40) */
RmoObject *RmoObjectBase_Destruct(RmoObject *self)
{
    RmoObjectBase_take_down(self);
    return self;
}
CLEAN_AS(func_ov004_0222c834, RmoObjectBase_Destruct)

/* func_ov004_0222c87c (the constructor): the scene object, the class's vtable, then the parts;
 * the object starts without a number among the room objects' shared values. */
RmoObject *RmoObjectBase_Construct(RmoObject *self)
{
    SceneObjectBase_Construct(RmoObjectBase_scene_object(self));
    self->actor.vtable = data_ov004_02254b28;
    AnimatedModel_Construct(RmoObjectBase_body(self));
    RmoModel_Construct(&self->body_model);
    RmoTexture_Construct(&self->body_texture);
    RmoSound_Construct(RmoObjectBase_sound_source(self));
    ((RoomObject *) (void *) self)->state_number = ROOM_OBJECT_STATE_NONE;
    return self;
}
CLEAN_AS(func_ov004_0222c87c, RmoObjectBase_Construct)
