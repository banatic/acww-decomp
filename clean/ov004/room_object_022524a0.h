/* A class of overlay 4's room objects (vtable 0x022524a0, receiver part 0x0225254c, 0x848 bytes)
 * whose state (RoomObject022524a0.state) runs through tables of member pointers
 * (member_pointer.h):
 *
 * - IDLE (0): entered with the value 0 of its node set and the animations of variant 0 played
 *   once; when its switch is asked to change it requests PLAYING for the object at its cell
 *   (func_02052738);
 * - PLAYING (1): entered with the value 1 of its node set, the animations of variant 0 played
 *   once and the sound at 2; once the model's joint animation has ended it requests IDLE.
 *
 * While PLAYING, the model's hook after the description of a node of the node set takes that
 * node's place in the world and asks the ground there (func_02034270); where the ground answers
 * above 0 it requests IDLE at once. Its start binds the animations of variant 0 and enters
 * IDLE. */
#ifndef CLEAN_OV004_ROOM_OBJECT_022524A0_H
#define CLEAN_OV004_ROOM_OBJECT_022524A0_H

#include "types.h"

#include "room_object.h"
#include "room_object_methods.h" /* NodeHookState */

typedef struct RoomObject022524a0 {
    RoomObject base;
    u8 state; /* RoomObject022524a0State */
    u8 unk_845[3];
} RoomObject022524a0;

enum RoomObject022524a0State {
    ROOM_OBJECT_022524A0_IDLE = 0,
    ROOM_OBJECT_022524A0_PLAYING = 1,
    ROOM_OBJECT_022524A0_STATE_COUNT = 2
};

int RoomObject022524a0_UpdatePlaying(RoomObject022524a0 *object);
int RoomObject022524a0_EnterPlaying(RoomObject022524a0 *object);
void RoomObject022524a0_UpdateIdle(RoomObject022524a0 *object);
int RoomObject022524a0_EnterIdle(RoomObject022524a0 *object);
void RoomObject022524a0_UpdateState(RoomObject022524a0 *object);
int RoomObject022524a0_EnterState(RoomObject022524a0 *object, unsigned int state, int value);
void RoomObject022524a0_NodeGroundHook(RoomObject022524a0 *object, int node, NodeHookState *state);
void RoomObject022524a0_OnVanish(RoomObject022524a0 *object);
int RoomObject022524a0_Vfunc0C(RoomObject022524a0 *object);
int RoomObject022524a0_Update(RoomObject022524a0 *object);
int RoomObject022524a0_Start(RoomObject022524a0 *object);
RoomObject022524a0 *RoomObject022524a0_Delete(RoomObject022524a0 *object);
RoomObject022524a0 *RoomObject022524a0_Destroy(RoomObject022524a0 *object);
RoomObject022524a0 *RoomObject022524a0_Construct(RoomObject022524a0 *object);
void RoomObject022524a0_Create(void);
RoomObject022524a0 *RoomObject022524a0Receiver_Delete(void *receiver);
RoomObject022524a0 *RoomObject022524a0Receiver_Destroy(void *receiver);

#endif
