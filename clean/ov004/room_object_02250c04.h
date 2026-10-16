/* A class of overlay 4's room objects (vtable 0x02250c04, receiver part 0x02250cb0) without
 * states of its own: its start binds the animations of variant 0 held at frame 0 (speed 0),
 * each frame advances them, and when a move starts it plays them forwards or backwards by the
 * state of its entry among the two of func_ov004_0223cb10 (func_ov004_0223ca9c), with the
 * sound at 2, or else the sound of the move. It is 0x844 bytes: the base class's alone. */
#ifndef CLEAN_OV004_ROOM_OBJECT_02250C04_H
#define CLEAN_OV004_ROOM_OBJECT_02250C04_H

#include "types.h"

#include "room_object.h"

typedef struct RoomObject02250c04 {
    RoomObject base;
} RoomObject02250c04;

void RoomObject02250c04_OnMoveStart(RoomObject02250c04 *object, int ahead);
int RoomObject02250c04_Vfunc0C(void);
int RoomObject02250c04_Update(RoomObject02250c04 *object);
int RoomObject02250c04_Start(RoomObject02250c04 *object);
RoomObject02250c04 *RoomObject02250c04_Delete(RoomObject02250c04 *object);
RoomObject02250c04 *RoomObject02250c04_Destroy(RoomObject02250c04 *object);
RoomObject02250c04 *RoomObject02250c04_Construct(RoomObject02250c04 *object);
void RoomObject02250c04_Create(void);

#endif
