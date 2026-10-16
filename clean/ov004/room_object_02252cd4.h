/* A class of overlay 4's room objects (vtable 0x02252cd4, receiver part 0x02252d80, 0x848 bytes)
 * without states of its own (vtable slot 0x70 is the base class's). Each frame:
 *
 * - kind 0x2c (RoomObject.unk_780): the node set's value 0, or 1 while a player (actors 0 to 3,
 *   in state 0x28, func_ov004_0222c268) stands on one of its cells, which also advances the
 *   animations and plays sound 0 for each such player; kind 9 advances the animations and plays
 *   sound 0 every frame;
 * - with its entry among two (func_ov004_0223ca9c of func_ov004_0223cb10) in state 0 (or, for
 *   kind 0x26, in state 0, 3 or 1, giving the player's action 0, 1 or 2) and func_ov004_0223c700
 *   allowing it, nobody near the point in front of the entry (RoomObject02252cd4_ProbePoint)
 *   counts up to 7 frames; once the entry has moved more than 0x200 with the count at 7, the
 *   player is sent to that point (func_ov004_0222c0b8) and the count starts again.
 *
 * Its start binds the animations of variant 0 in a loop for kinds 9 and 0x2c. */
#ifndef CLEAN_OV004_ROOM_OBJECT_02252CD4_H
#define CLEAN_OV004_ROOM_OBJECT_02252CD4_H

#include "types.h"

#include "autoload_2/vector.h"
#include "room_object.h"

typedef struct RoomObject02252cd4 {
    RoomObject base;
    u16 push_frames; /* frames with nobody near the entry's point, up to 7 */
    u8 unk_846[2];
} RoomObject02252cd4;

void RoomObject02252cd4_ProbePoint(RoomObject02252cd4 *object, Vec3 *out, void *entry);
int RoomObject02252cd4_Vfunc0C(void);
int RoomObject02252cd4_Update(RoomObject02252cd4 *object);
int RoomObject02252cd4_Start(RoomObject02252cd4 *object);
RoomObject02252cd4 *RoomObject02252cd4_Delete(RoomObject02252cd4 *object);
RoomObject02252cd4 *RoomObject02252cd4_Destroy(RoomObject02252cd4 *object);
RoomObject02252cd4 *RoomObject02252cd4_Construct(RoomObject02252cd4 *object);
void RoomObject02252cd4_Create(void);
RoomObject02252cd4 *RoomObject02252cd4Receiver_Delete(void *receiver);
RoomObject02252cd4 *RoomObject02252cd4Receiver_Destroy(void *receiver);

#endif
