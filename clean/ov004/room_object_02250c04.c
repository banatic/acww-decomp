/* The room objects of vtable 0x02250c04 (room_object_02250c04.h). */
#include "room_object_02250c04.h"

#include <stdint.h>

#include "clean.h"
#include "furniture_model.h"
#include "room_object_anims.h"
#include "room_object_life.h"
#include "room_object_parts.h"

static_assert(sizeof(RoomObject02250c04) == 0x844, "the size RoomObject02250c04_Create allocates");

#define ROOM_OBJECT_02250C04_SIZE 0x844
#define ONE 0x1000       /* normal speed, 20.12 fixed point */
#define ANIM_MODE_LOOP 0 /* start again at the end */
#define ANIM_MODE_ONCE 1 /* stop at the end */
#define ANIM_MODE_3 3    /* the animations' mode 3 */
#define NO_SOUND 0xffff  /* from RoomObject_MoveSound: none */
#define KIND_16 0x16     /* RoomObject.unk_780 of the kind whose entry states are 0 and 2 */

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02250c04[];
extern const u8 data_ov004_02250cb0[];

/* The two entries at data_ov004_02259784 (0x40 bytes each), the one of `object` among them
 * (NULL for none), and an entry's state (its word at 0x3c). */
extern void *func_ov004_0223cb10(void);
extern void *func_ov004_0223ca9c(void *entries, RoomObject02250c04 *object);
extern int func_ov004_0223cb20(void *entry);
/* Plays a sound (through func_02096718(4) and func_0200f328). */
extern int func_02095380(int sound);

/* Plays the animations of variant 0 once from the start (`forward`), else in mode 3 from the
 * last frame of `joints`; the sound at 2 first, whether it played added to `played`.
 * QUIRK: for a file without frames mode 3 starts from 0xffff. */
static void RoomObject02250c04_play(RoomObject02250c04 *object, int forward, const AnimFile *joints, int *played)
{
    if (RoomObject_PlaySound1(&object->base) != 0) {
        *played = 1;
    }
    if (forward) {
        RoomObject_PlayAnimsFrom(&object->base, 0, ANIM_MODE_ONCE, ONE, 0);
    } else {
        RoomObject_PlayAnimsFrom(&object->base, 0, ANIM_MODE_3, ONE, (u16) (joints->frames - 1));
    }
}

/* func_ov004_02215504 (vtable slot 0x94, when a move starts: `ahead` 1 in state 3, 0 in 4):
 * with an entry among func_ov004_0223cb10's, the animations of variant 0 are played by its
 * state: for kind 0x16 state 2 plays forwards ahead and backwards otherwise, state 0 the other
 * way round; for the other kinds states 3 and 1 do the same. Unless the sound at 2 played,
 * the sound of the move (RoomObject_MoveSound) is played when there is one.
 * REQUIRES: the archive has a joint animation of variant 0 where one is played backwards (its
 * frame count is read). */
void RoomObject02250c04_OnMoveStart(RoomObject02250c04 *object, int ahead)
{
    void *entry = func_ov004_0223ca9c(func_ov004_0223cb10(), object);
    int played = 0;
    if (entry != NULL) {
        const AnimFile *joints =
            (const AnimFile *) (uintptr_t) (u32) AnimSet_Anim00(FurnitureModel_Anims(&object->base.model_files), 0);
        int forward_state = 3;
        int backward_state = 1;
        if (object->base.unk_780 == KIND_16) {
            forward_state = 2;
            backward_state = 0;
        }
        if (func_ov004_0223cb20(entry) == forward_state) {
            RoomObject02250c04_play(object, ahead != 0, joints, &played);
        } else if (func_ov004_0223cb20(entry) == backward_state) {
            RoomObject02250c04_play(object, ahead == 0, joints, &played);
        }
    }
    if (played == 0) {
        int sound = RoomObject_MoveSound(&object->base);
        if (sound != NO_SOUND) {
            func_02095380(sound);
        }
    }
}
CLEAN_AS(func_ov004_02215504, RoomObject02250c04_OnMoveStart)

/* func_ov004_0221569c (vtable slot 0x0c) */
int RoomObject02250c04_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_0221569c, RoomObject02250c04_Vfunc0C)

/* func_ov004_022156a0 (vtable slot 0x80, each frame while neither appearing nor vanishing):
 * advances its animations. */
int RoomObject02250c04_Update(RoomObject02250c04 *object)
{
    RoomObject_AdvanceAnims(&object->base);
    return 1;
}
CLEAN_AS(func_ov004_022156a0, RoomObject02250c04_Update)

/* func_ov004_022156b0 (vtable slot 0x7c, once the model is bound): binds the animations of
 * variant 0, looping at speed 0 from frame 0; done at once. */
int RoomObject02250c04_Start(RoomObject02250c04 *object)
{
    RoomObject_LoadAnims(&object->base, 0, ANIM_MODE_LOOP, 0, 0);
    return 1;
}
CLEAN_AS(func_ov004_022156b0, RoomObject02250c04_Start)

static void RoomObject02250c04_set_vtables(RoomObject02250c04 *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_02250c04;
    object->base.receiver_vtable = data_ov004_02250cb0;
}

/* func_ov004_022156c8 (the deleting destructor, vtable slot 0x44) */
RoomObject02250c04 *RoomObject02250c04_Delete(RoomObject02250c04 *object)
{
    RoomObject02250c04_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_022156c8, RoomObject02250c04_Delete)

/* func_ov004_022156f4 (the destructor, vtable slot 0x40) */
RoomObject02250c04 *RoomObject02250c04_Destroy(RoomObject02250c04 *object)
{
    RoomObject02250c04_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_022156f4, RoomObject02250c04_Destroy)

/* func_ov004_02215718 (the constructor): the base, then this class's vtables. */
RoomObject02250c04 *RoomObject02250c04_Construct(RoomObject02250c04 *object)
{
    RoomObject_ConstructBase(&object->base);
    RoomObject02250c04_set_vtables(object);
    return object;
}
CLEAN_AS(func_ov004_02215718, RoomObject02250c04_Construct)

/* func_ov004_0221573c: a new one from the room's heap; nothing when it has no room. */
void RoomObject02250c04_Create(void)
{
    RoomObject02250c04 *object = RoomObject_Alloc(ROOM_OBJECT_02250C04_SIZE);
    if (object != NULL) {
        RoomObject02250c04_Construct(object);
    }
}
CLEAN_AS(func_ov004_0221573c, RoomObject02250c04_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters RoomObject02250c04's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static RoomObject02250c04 *RoomObject02250c04_from_receiver(void *receiver)
{
    return (RoomObject02250c04 *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221a8ac: the deleting destructor, entered from the receiver part. */
RoomObject02250c04 *RoomObject02250c04Receiver_Delete(void *receiver)
{
    return RoomObject02250c04_Delete(RoomObject02250c04_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02250c04D0Ev, RoomObject02250c04Receiver_Delete)

/* func_ov004_0221a8c8: the destructor, entered from the receiver part. */
RoomObject02250c04 *RoomObject02250c04Receiver_Destroy(void *receiver)
{
    return RoomObject02250c04_Destroy(RoomObject02250c04_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02250c04D1Ev, RoomObject02250c04Receiver_Destroy)
