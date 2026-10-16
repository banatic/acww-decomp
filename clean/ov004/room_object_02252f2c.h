/* A class of overlay 4's room objects (vtable 0x02252f2c, 0x8a0 bytes) that is on or off by its
 * switch, with three glowing materials (a GlowSet, room_object_parts.h) kept lit. Its state
 * (RoomObject02252f2c.state) runs through tables of member pointers (member_pointer.h):
 *
 * - OFF (0): entered with the switch off and the sound at 4;
 * - ON (1): entered with the switch on and the sound at 2;
 *
 * in either, while the switch has a change pending it requests the other state for the object
 * at its cell (func_0205265c). ON shows it on (vtable slot 0x74).
 *
 * With RoomObject.unk_780 at 1 its animations of variant 0 run in a loop from a random frame
 * (from the start when RoomObject.unk_76C is 1) and the glows are bound lit. Furniture 0x123,
 * 0x1fb and 0x1fc play their own sound at a point (0x429, 0x42b and 0x42c) and set its variable
 * at some frames of the joint animation; the others play the sound at 0 each frame. */
#ifndef CLEAN_OV004_ROOM_OBJECT_02252F2C_H
#define CLEAN_OV004_ROOM_OBJECT_02252F2C_H

#include "types.h"

#include "room_object.h"
#include "room_object_parts.h"

typedef struct RoomObject02252f2c {
    RoomObject base;
    u8 state; /* RoomObject02252f2cState */
    u8 unk_845[3];
    GlowSet glows;
} RoomObject02252f2c;

enum RoomObject02252f2cState {
    ROOM_OBJECT_02252F2C_OFF = 0,
    ROOM_OBJECT_02252F2C_ON = 1,
    ROOM_OBJECT_02252F2C_STATE_COUNT = 2
};

void RoomObject02252f2c_UpdateOn(RoomObject02252f2c *object);
int RoomObject02252f2c_EnterOn(RoomObject02252f2c *object);
void RoomObject02252f2c_UpdateOff(RoomObject02252f2c *object);
int RoomObject02252f2c_EnterOff(RoomObject02252f2c *object);
void RoomObject02252f2c_UpdateState(RoomObject02252f2c *object);
int RoomObject02252f2c_EnterState(RoomObject02252f2c *object, unsigned int state, int value);
u8 RoomObject02252f2c_StateIsOn(RoomObject02252f2c *object, unsigned int state);
int RoomObject02252f2c_Vfunc0C(void);
int RoomObject02252f2c_Update(RoomObject02252f2c *object);
int RoomObject02252f2c_Start(RoomObject02252f2c *object);

#endif
