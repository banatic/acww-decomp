/* The box a room object pushes back with (its member at 0x62c): a collision box of the main
 * program (constructor func_02032564, vtable 0x020da1b4, set up by func_020321bc and taken out
 * by func_02032180) whose one virtual function, called when an actor runs into one of its four
 * sides, is overridden here: when the player walks into a side of an idle object, facing it,
 * the object starts to be pushed (func_ov004_0223c758). */
#ifndef CLEAN_OV004_PUSH_BOX_H
#define CLEAN_OV004_PUSH_BOX_H

#include "types.h"

#include "autoload_2/vector.h" /* Vec3 */

struct RoomObject;

/* A point or direction on the ground, in 20.12 fixed point. */
typedef struct Point2 {
    fx32 x;
    fx32 z;
} Point2;

/* A side of a box: from `start` to `end`, with the outward normal; the line through it is
 * normal.x * x + normal.z * z + offset = 0 (func_0202f59c). */
typedef struct BoxSide {
    u32 unk_00;
    Point2 start;
    Point2 end;
    Point2 normal;
    fx32 offset;
} BoxSide;

/* The actor running into a side: only its position, the point the test starts from and its
 * facing angle are read. */
typedef struct PushingActor {
    u8 unk_00[0x5c];
    Vec3 position;
    Vec3 unk_68; /* the point projected onto the side */
    u8 unk_74[0x1a];
    s16 angle;
} PushingActor;

typedef struct PushBox {
    const void *vtable;
    u8 unk_04[0x94];
    u8 unk_98; /* clear: func_ov004_0220f8c0 does not update it */
    u8 unk_99[3];
    struct RoomObject *owner; /* the object it belongs to while it is in the world */
} PushBox;

void PushBox_SettlePivot(PushBox *box, PushingActor *actor);
void PushBox_OnSideHit(PushBox *box, BoxSide *side, PushingActor *actor, fx32 standoff);
void PushBox_ClearOwner(PushBox *box);
void PushBox_SetOwner(PushBox *box, struct RoomObject *owner);
PushBox *PushBox_Destruct(PushBox *box);
PushBox *PushBox_Construct(PushBox *box);

#endif
