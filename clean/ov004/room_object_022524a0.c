/* The room objects of vtable 0x022524a0 (room_object_022524a0.h). */
#include "room_object_022524a0.h"

#include <stdint.h>

#include "clean.h"
#include "room_object_anims.h"
#include "room_object_parts.h"

static_assert(offsetof(RoomObject022524a0, state) == 0x844, "state");
static_assert(sizeof(RoomObject022524a0) == 0x848, "the size of one");

#define ONE 0x1000         /* normal speed, 20.12 fixed point */
#define ANIM_MODE_ONCE 1   /* RoomObject_PlayAnimsFrom: stop at the end */
#define SLOT_70_VALUE 0xff /* the second argument given with a state (vtable slot 0x70) */

/* Advances the model's joint animation (the main program's model object at 0x538), and whether
 * that animation is at its end. */
extern void func_02054cdc(void *model);
extern int func_02056f94(void *anim);
/* Request a state for the object at the object's cell (only when data_020e54a8 is 1), straight
 * to func_020526b8. */
extern int func_02052738(unsigned int object, int state, int a2, int a3);

static unsigned int RoomObject022524a0_address(RoomObject022524a0 *object)
{
    return (unsigned int) (uintptr_t) object;
}

/* func_ov004_0221412c (update of PLAYING): advances the joint animation; once it has ended,
 * requests IDLE and gives the answer, else 0. */
int RoomObject022524a0_UpdatePlaying(RoomObject022524a0 *object)
{
    func_02054cdc(object->base.unk_538);
    if (func_02056f94(object->base.joint_anim) == 0) {
        return 0;
    }
    return func_02052738(RoomObject022524a0_address(object), ROOM_OBJECT_022524A0_IDLE, SLOT_70_VALUE, 1);
}
CLEAN_AS(func_ov004_0221412c, RoomObject022524a0_UpdatePlaying)

/* func_ov004_02214160 (entry of PLAYING): the node set's value 1, the animations of variant 0
 * once from the start, and the sound at 2. */
int RoomObject022524a0_EnterPlaying(RoomObject022524a0 *object)
{
    ByteSet_SetValue(&object->base.node_set, 1);
    RoomObject_PlayAnimsFrom(&object->base, 0, ANIM_MODE_ONCE, ONE, 0);
    RoomObject_PlaySound1(&object->base);
    return 1;
}
CLEAN_AS(func_ov004_02214160, RoomObject022524a0_EnterPlaying)

/* func_ov004_02214198 (update of IDLE): when the switch was asked to change, requests
 * PLAYING. */
void RoomObject022524a0_UpdateIdle(RoomObject022524a0 *object)
{
    if (Switch_IsPending(&object->base.light_switch)) {
        func_02052738(RoomObject022524a0_address(object), ROOM_OBJECT_022524A0_PLAYING, SLOT_70_VALUE, 1);
    }
}
CLEAN_AS(func_ov004_02214198, RoomObject022524a0_UpdateIdle)
