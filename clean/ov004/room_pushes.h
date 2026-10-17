/* The room's two pushes (data_ov004_02259784, func_ov004_0223cb10): what a room object's push box
 * (push_box.h) records when an actor pushes against a side of it, one record for the objects
 * on the floor and one for those on top of others (by RoomObject_Layer). The objects that can
 * be pushed read theirs back (func_ov004_0223ca9c, func_ov004_0223cadc). The array is a C++
 * array of two objects (constructed by the overlay's static initialisation) and is reset when
 * the room starts, every frame, and when it ends. */
#ifndef CLEAN_OV004_ROOM_PUSHES_H
#define CLEAN_OV004_ROOM_PUSHES_H

#include "types.h"

#include "autoload_2/vector.h"

#define ROOM_PUSHES_COUNT 2
#define ROOM_PUSH_NO_OBJECT (-1)
#define ROOM_PUSH_NO_SIDE 4

typedef struct RoomPush {
    s32 object;       /* 0x00: the index of the object pushed, ROOM_PUSH_NO_OBJECT for none */
    Vec3 from;        /* 0x04: the actor's point at 0x68 */
    Vec3 position;    /* 0x10: the actor's position */
    fx32 standoff;    /* 0x1c */
    Vec3 centre;      /* 0x20: the middle of the side pushed */
    Vec3 destination; /* 0x2c: where the actor is to stand */
    s16 facing;       /* 0x38 */
    u8 pad_3a[2];
    s32 side; /* 0x3c: the side pushed (Angle_Side), ROOM_PUSH_NO_SIDE for none */
} RoomPush;

int RoomPushes_Allowed(void);
int RoomPushes_Enabled(void);
int RoomPushes_Record(RoomPush *pushes, s32 object, Vec3 *from, Vec3 *position, s32 standoff, Vec3 *centre, Vec3 *destination,
                      short facing, s32 side);
void RoomPushes_Reset(RoomPush *pushes);
RoomPush *RoomPushes_Destruct(RoomPush *pushes);
RoomPush *RoomPushes_Construct(RoomPush *pushes);

#endif
