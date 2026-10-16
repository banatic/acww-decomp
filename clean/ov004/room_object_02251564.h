/* A class of overlay 4's room objects (vtable 0x02251564, receiver part 0x02251610, 0x848
 * bytes) that takes one bell from the player who uses it. It has two states, entered through
 * vtable slot 0x70 and dispatched through tables of member pointers (member_pointer.h):
 *
 * - idle: touching it (a change of the switch pending) requests the used state with this
 *   system's player number as the value vtable slot 0x70 keeps (RoomObject.unk_77C);
 * - used: on entry, the sound at 2 and, when the player who used it is this system's, one bell
 *   less in the player's wallet (at 0xa68 of the pockets, func_02098cf8 and func_02098aa0) if
 *   any is left. Its update is idle's, so it can be used again.
 *
 * With unk_76C at 2 it enters the used state by itself, each frame, with no player (0xff). Once
 * its model is bound it is idle. */
#ifndef CLEAN_OV004_ROOM_OBJECT_02251564_H
#define CLEAN_OV004_ROOM_OBJECT_02251564_H

#include "types.h"

#include "room_object.h"

typedef struct RoomObject02251564 {
    RoomObject base;
    u8 state; /* RoomObject02251564State */
    u8 unk_845[3];
} RoomObject02251564;

enum RoomObject02251564State {
    ROOM_OBJECT_02251564_IDLE = 0,
    ROOM_OBJECT_02251564_USED = 1,
    ROOM_OBJECT_02251564_STATE_COUNT = 2
};

void RoomObject02251564_UpdateUsed(RoomObject02251564 *object);
int RoomObject02251564_EnterUsed(RoomObject02251564 *object);
void RoomObject02251564_UpdateIdle(RoomObject02251564 *object);
int RoomObject02251564_EnterIdle(RoomObject02251564 *object);
void RoomObject02251564_UpdateState(RoomObject02251564 *object);
int RoomObject02251564_EnterState(RoomObject02251564 *object, unsigned int state, int value);
int RoomObject02251564_Vfunc0C(void);
int RoomObject02251564_Update(RoomObject02251564 *object);
int RoomObject02251564_Start(RoomObject02251564 *object);
RoomObject02251564 *RoomObject02251564_Delete(RoomObject02251564 *object);
RoomObject02251564 *RoomObject02251564_Destroy(RoomObject02251564 *object);
RoomObject02251564 *RoomObject02251564_Construct(RoomObject02251564 *object);
void RoomObject02251564_Create(void);

#endif
