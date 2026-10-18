/* The room objects of vtable 0x02251690 (room_object_02251690.h). */
#include "room_object_02251690.h"

#include <stdint.h>

#include "clean.h"
#include "main/sound.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "room_object_parts.h"
#include "autoload_2/sound_melody.h"
#include "furniture_sounds.h"
#include "main/room_sync.h"

static_assert(offsetof(RoomObject02251690, seq) == 0x844, "seq");
static_assert(sizeof(RoomObject02251690) == 0x850, "the size RoomObject02251690_Create allocates");

#define ROOM_OBJECT_02251690_SIZE 0x850
#define SLOT_70_VALUE 0xff /* the second argument given with a state (vtable slot 0x70) */

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02251690[];
extern const u8 data_ov004_0225173c[];

/* The sound number that means none. */
extern u16 data_ov004_0224fd38;

/* func_ov004_02213270 (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given `state`
 * and `value`), then starts the furniture's sound at 2 when it has one; 1. */
int RoomObject02251690_Play(RoomObject02251690 *object, int state, int value)
{
    RoomObject_SetUnk77C(&object->base, state, value);
    int sound = FurnitureSounds_Sound1(RoomObject_Number(&object->base));
    if (sound != data_ov004_0224fd38) {
        SoundSeq_Start(&object->seq, (u16) sound);
    }
    return 1;
}
CLEAN_AS(func_ov004_02213270, RoomObject02251690_Play)

/* func_ov004_022132a4 (vtable slot 0x0c): stops the sequence. */
int RoomObject02251690_Stop(RoomObject02251690 *object)
{
    SoundSeq_Stop(&object->seq);
    return 1;
}
CLEAN_AS(func_ov004_022132a4, RoomObject02251690_Stop)

/* func_ov004_022132bc (vtable slot 0x84, each frame while appearing or vanishing, and called by
 * the update): the sequence follows a copy of the object's centre. */
int RoomObject02251690_Follow(RoomObject02251690 *object)
{
    Vec3 position = object->base.sound.position;
    SoundSeq_UpdateAt(&object->seq, &position);
    return 1;
}
CLEAN_AS(func_ov004_022132bc, RoomObject02251690_Follow)

/* func_ov004_022132f4 (vtable slot 0x80, each frame while neither appearing nor vanishing):
 * touched, it requests state 0 for the object at its cell; then vtable slot 0x84. */
int RoomObject02251690_Update(RoomObject02251690 *object)
{
    if (Switch_IsPending(&object->base.light_switch)) {
        RoomSync_RequestState(&object->base, 0, SLOT_70_VALUE, 1);
    }
    object->base.vtable->update_unsettled(&object->base);
    return 1;
}
CLEAN_AS(func_ov004_022132f4, RoomObject02251690_Update)

/* func_ov004_02213328 (vtable slot 0x7c, once the model is bound): readies the sequence; done
 * at once. */
int RoomObject02251690_Start(RoomObject02251690 *object)
{
    SoundSeq_Init(&object->seq);
    return 1;
}
CLEAN_AS(func_ov004_02213328, RoomObject02251690_Start)

static void RoomObject02251690_set_vtables(RoomObject02251690 *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_02251690;
    object->base.receiver_vtable = data_ov004_0225173c;
}

/* func_ov004_02213340 (the deleting destructor, vtable slot 0x44) */
RoomObject02251690 *RoomObject02251690_Delete(RoomObject02251690 *object)
{
    RoomObject02251690_set_vtables(object);
    MelodySeq_Destruct(&object->seq);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_02213340, RoomObject02251690_Delete)

/* func_ov004_02213378 (the destructor, vtable slot 0x40) */
RoomObject02251690 *RoomObject02251690_Destroy(RoomObject02251690 *object)
{
    RoomObject02251690_set_vtables(object);
    MelodySeq_Destruct(&object->seq);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_02213378, RoomObject02251690_Destroy)

/* func_ov004_022133ac (the constructor) */
RoomObject02251690 *RoomObject02251690_Construct(RoomObject02251690 *object)
{
    RoomObject_ConstructBase(&object->base);
    RoomObject02251690_set_vtables(object);
    MelodySeq_Construct(&object->seq);
    return object;
}
CLEAN_AS(func_ov004_022133ac, RoomObject02251690_Construct)

/* func_ov004_022133dc: a new one from the room's heap; nothing when it has no room. */
void RoomObject02251690_Create(void)
{
    RoomObject02251690 *object = RoomObject_Alloc(ROOM_OBJECT_02251690_SIZE);
    if (object != NULL) {
        RoomObject02251690_Construct(object);
    }
}
CLEAN_AS(func_ov004_022133dc, RoomObject02251690_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters RoomObject02251690's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static RoomObject02251690 *RoomObject02251690_from_receiver(void *receiver)
{
    return (RoomObject02251690 *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221aaa4: the deleting destructor, entered from the receiver part. */
RoomObject02251690 *RoomObject02251690Receiver_Delete(void *receiver)
{
    return RoomObject02251690_Delete(RoomObject02251690_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02251690D0Ev, RoomObject02251690Receiver_Delete)

/* func_ov004_0221aac0: the destructor, entered from the receiver part. */
RoomObject02251690 *RoomObject02251690Receiver_Destroy(void *receiver)
{
    return RoomObject02251690_Destroy(RoomObject02251690_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02251690D1Ev, RoomObject02251690Receiver_Destroy)
