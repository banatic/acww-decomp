/* The RMO family's base class: its body's loading, its shared value and its vtable slots
 * (rmo_object_slots.h). */
#include "rmo_object_slots.h"

#include <stdint.h>

#include "autoload_2/vector.h"
#include "clean.h"
#include "main/actor.h"
#include "main/animated_model.h"
#include "main/c_library.h"
#include "main/room_object_state.h"
#include "main/scene_object_base.h"
#include "main/sound_emitter.h"
#include "ov004/rmo_model.h"
#include "ov004/rmo_object.h"

static_assert(offsetof(RmoObject, body) == 0xec, "body");
static_assert(offsetof(RmoObject, body_model) == 0x1a4, "body model");
static_assert(offsetof(RmoObject, body_texture) == 0x248, "body texture");
static_assert(offsetof(RmoObject, unk_24c) == 0x24c, "the state shown");
static_assert(offsetof(RoomObject, state_number) == 0xea, "shared value's number");
static_assert(offsetof(Actor, position) == 0x5c, "position");

/* The class's vtable. */
extern const u8 data_ov004_02254b28[];

/* The vtable slots called through the vtable. */
#define RMO_SLOTS_SHOW_STATE 0x60
#define RMO_SLOTS_SOUND_POINT 0x64

/* The paths are built in buffers of this size. */
#define RMO_SLOTS_PATH_SIZE 0x28

/* The archive's and texture file's paths from a name. */
extern const char data_ov004_02254bd4[]; /* "/roomObj/%s.arc" */
extern const char data_ov004_02254be4[]; /* "/roomObj/%s.nsbtx" */

/* The state the object shows (byte 0x24c) and its sound emitter (0x250). */
static u8 *rmo_slots_shown(RmoObject *object)
{
    return &object->unk_24c[0];
}

static void *rmo_slots_sound(RmoObject *object)
{
    return &object->unk_24c[4];
}

static u8 rmo_slots_number(RmoObject *object)
{
    return ((RoomObject *) (void *) object)->state_number;
}

static SceneObjectBase *rmo_slots_scene_object(RmoObject *object)
{
    return (SceneObjectBase *) (void *) object;
}

static uintptr_t rmo_slots_slot(RmoObject *object, u32 offset)
{
    const u32 *vtable = object->actor.vtable;
    return vtable[offset / 4];
}

/* func_ov004_0222c558: the object's shared value set to `value` (RoomObjectState_Set's
 * answer); 0 without a number. */
int RmoObjectSlots_SetSharedValue(RmoObject *object, unsigned int value)
{
    if (rmo_slots_number(object) == ROOM_OBJECT_STATE_NONE) {
        return 0;
    }
    return RoomObjectState_Set(rmo_slots_number(object), value);
}
CLEAN_AS(func_ov004_0222c558, RmoObjectSlots_SetSharedValue)

/* func_ov004_0222c574: the object's shared value; 0 without a number. */
int RmoObjectSlots_SharedValue(RmoObject *object)
{
    if (rmo_slots_number(object) == ROOM_OBJECT_STATE_NONE) {
        return 0;
    }
    return (int) RoomObjectState_Get(rmo_slots_number(object));
}
CLEAN_AS(func_ov004_0222c574, RmoObjectSlots_SharedValue)

/* func_ov004_0222c590: the number of the object's shared value (0xff for none). */
void RmoObjectSlots_SetValueNumber(RmoObject *object, u8 number)
{
    ((RoomObject *) (void *) object)->state_number = number;
}
CLEAN_AS(func_ov004_0222c590, RmoObjectSlots_SetValueNumber)

/* func_ov004_0222c598: the body's archive freed and its texture let go of. */
void RmoObjectSlots_ReleaseBody(RmoObject *object)
{
    RmoModel_ReleaseWithTexture(&object->body_model, &object->body_texture);
}
CLEAN_AS(func_ov004_0222c598, RmoObjectSlots_ReleaseBody)

/* func_ov004_0222c5c8: the body loaded from "/roomObj/<name>.arc" and "/roomObj/<name>.nsbtx"
 * (RmoObjectSlots_Load). */
int RmoObjectSlots_LoadNamed(RmoObject *object, const char *name)
{
    char archive[RMO_SLOTS_PATH_SIZE];
    char texture[RMO_SLOTS_PATH_SIZE];
    CLib_SPrintf(archive, data_ov004_02254bd4, name);
    CLib_SPrintf(texture, data_ov004_02254be4, name);
    return RmoObjectSlots_Load(object, archive, texture);
}
CLEAN_AS(func_ov004_0222c5c8, RmoObjectSlots_LoadNamed)

/* func_ov004_0222c600: the body's archive and textures loaded from the paths and its model
 * bound to them (RmoModel_LoadWithTexture). */
int RmoObjectSlots_Load(RmoObject *object, const char *archive, const char *texture)
{
    return RmoModel_LoadWithTexture(archive, texture, &object->body.object, &object->body_model, &object->body_texture);
}
CLEAN_AS(func_ov004_0222c600, RmoObjectSlots_Load)

/* func_ov004_0222c6cc (vtable slot 0x60): told a state to show; the base class shows nothing
 * and answers 1. */
int RmoObjectSlots_ShowState(RmoObject *object, unsigned int state)
{
    (void) object;
    (void) state;
    return 1;
}
CLEAN_AS(func_ov004_0222c6cc, RmoObjectSlots_ShowState)

/* func_ov004_0222c6d0 (vtable slot 0x64): the point the object's sound is at, its position. */
void RmoObjectSlots_SoundPoint(RmoObject *object, Vec3 *point)
{
    point->x = object->actor.position.x;
    point->y = object->actor.position.y;
    point->z = object->actor.position.z;
}
CLEAN_AS(func_ov004_0222c6d0, RmoObjectSlots_SoundPoint)

/* func_ov004_0222c6e0 (vtable slot 0x10): whether the object can be deleted, as the scene
 * object says; when it can, its sound's slot 0x10 is called. */
int RmoObjectSlots_CanDelete(RmoObject *object)
{
    if (SceneObjectBase_CanDelete(rmo_slots_scene_object(object)) == 0) {
        return 0;
    }
    RmoSound_Vfunc10(rmo_slots_sound(object));
    return 1;
}
CLEAN_AS(func_ov004_0222c6e0, RmoObjectSlots_CanDelete)

/* func_ov004_0222c704 (vtable slot 0x20): the object's sound follows the point of its slot
 * 0x64; then the actor runs. */
void RmoObjectSlots_Run(RmoObject *object, int status)
{
    Vec3 point;
    ((void (*)(RmoObject *, Vec3 *))(uintptr_t) rmo_slots_slot(object, RMO_SLOTS_SOUND_POINT))(object, &point);
    RmoSound_UpdateAt(rmo_slots_sound(object), &point);
    Actor_Run(&object->actor, status);
}
CLEAN_AS(func_ov004_0222c704, RmoObjectSlots_Run)

/* func_ov004_0222c734 (vtable slot 0x1c): whether the object may run, as the scene object says;
 * when it may and has a shared value that differs from the state it shows, it is told to show
 * the value (slot 0x60). */
int RmoObjectSlots_CanRun(RmoObject *object)
{
    if (SceneObjectBase_CanRun(rmo_slots_scene_object(object)) == 0) {
        return 0;
    }
    if (rmo_slots_number(object) != ROOM_OBJECT_STATE_NONE) {
        int value = RmoObjectSlots_SharedValue(object);
        if (*rmo_slots_shown(object) != value) {
            ((int (*)(RmoObject *, int))(uintptr_t) rmo_slots_slot(object, RMO_SLOTS_SHOW_STATE))(object, value);
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_0222c734, RmoObjectSlots_CanRun)

/* func_ov004_0222c774 (vtable slot 0x04): asked before the object's creation: when the scene
 * object is set up, its id is cleared and its sound stopped. */
int RmoObjectSlots_CanCreate(RmoObject *object)
{
    if (SceneObjectBase_CanCreate(rmo_slots_scene_object(object)) == 0) {
        return 0;
    }
    SceneObjectBase_SetId(rmo_slots_scene_object(object), 0);
    RmoSound_Stop(rmo_slots_sound(object));
    return 1;
}
CLEAN_AS(func_ov004_0222c774, RmoObjectSlots_CanCreate)

/* func_ov004_0222c7a0: the destructor the derived classes end theirs with (a copy of the
 * class's own, func_ov004_0222c834): the class's vtable, then the sound, the texture's and the
 * archive's holders, the body and the scene object taken down in turn. Returns the object. */
RmoObject *RmoObjectSlots_Destruct(RmoObject *object)
{
    object->actor.vtable = data_ov004_02254b28;
    RmoSound_Destruct(rmo_slots_sound(object));
    RmoTexture_Destruct(&object->body_texture);
    RmoModel_Destruct(&object->body_model);
    AnimatedModel_DestructComplete((AnimatedModel *) (void *) &object->body);
    SceneObjectBase_DestructBase(rmo_slots_scene_object(object));
    return object;
}
CLEAN_AS(func_ov004_0222c7a0, RmoObjectSlots_Destruct)
