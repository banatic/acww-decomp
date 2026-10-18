/* A class of overlay 4's room objects (vtable 0x02252824, receiver part 0x022528d0, 0x848 bytes)
 * that shows its switch through its material colour animation (RoomObject.anims, ROOM_ANIM_MATERIAL,
 * of variant 0). Its state (RoomObject02252824.state) runs through tables of member pointers
 * (member_pointer.h):
 *
 * - OFF (0): the switch off; the material animation at its first frame in mode 3; when the
 *   switch is asked to change it requests TURNING_ON for the object at its cell
 *   (RoomSync_RequestState);
 * - TURNING_ON (1): the switch on; the material animation once from the start, with the sound
 *   at 2; each frame the sound at 0, and once the animation has ended (or when it is not bound)
 *   ON;
 * - ON (2): the switch on; the material animation held at its last frame; each frame
 *   FurnitureInfo_IndoorBit6 of its number and the sound at 0; when the switch is asked to change it
 *   requests TURNING_OFF;
 * - TURNING_OFF (3): the switch off; the material animation in mode 3 from its last frame,
 *   with the sound at 4; once it has ended (or when it is not bound) OFF.
 *
 * Each frame its other animations (joints, texture coordinates, patterns, visibility) advance
 * on their own. Its start binds all five of variant 0 and enters ON when its switch is on
 * (unless RoomObjects_InNookOrScene0AOr0F says so), else OFF. */
#ifndef CLEAN_OV004_ROOM_OBJECT_02252824_H
#define CLEAN_OV004_ROOM_OBJECT_02252824_H

#include "types.h"

#include "room_object.h"

typedef struct RoomObject02252824 {
    RoomObject base;
    u8 state; /* RoomObject02252824State */
    u8 unk_845[3];
} RoomObject02252824;

enum RoomObject02252824State {
    ROOM_OBJECT_02252824_OFF = 0,
    ROOM_OBJECT_02252824_TURNING_ON = 1,
    ROOM_OBJECT_02252824_ON = 2,
    ROOM_OBJECT_02252824_TURNING_OFF = 3,
    ROOM_OBJECT_02252824_STATE_COUNT = 4
};

void RoomObject02252824_UpdateTurningOff(RoomObject02252824 *object);
int RoomObject02252824_EnterTurningOff(RoomObject02252824 *object);
int RoomObject02252824_UpdateOn(RoomObject02252824 *object);
int RoomObject02252824_EnterOn(RoomObject02252824 *object);
void RoomObject02252824_UpdateTurningOn(RoomObject02252824 *object);
int RoomObject02252824_EnterTurningOn(RoomObject02252824 *object);
void RoomObject02252824_UpdateOff(RoomObject02252824 *object);
int RoomObject02252824_EnterOff(RoomObject02252824 *object);
void RoomObject02252824_UpdateState(RoomObject02252824 *object);
int RoomObject02252824_EnterState(RoomObject02252824 *object, unsigned int state, int value);
u8 RoomObject02252824_StateIsOn(RoomObject02252824 *object, unsigned int state);
int RoomObject02252824_Vfunc0C(void);
int RoomObject02252824_Update(RoomObject02252824 *object);
int RoomObject02252824_Start(RoomObject02252824 *object);
RoomObject02252824 *RoomObject02252824_Delete(RoomObject02252824 *object);
RoomObject02252824 *RoomObject02252824_Destroy(RoomObject02252824 *object);
RoomObject02252824 *RoomObject02252824_Construct(RoomObject02252824 *object);
void RoomObject02252824_Create(void);
RoomObject02252824 *RoomObject02252824Receiver_Delete(void *receiver);
RoomObject02252824 *RoomObject02252824Receiver_Destroy(void *receiver);

#endif
