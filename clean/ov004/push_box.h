/* The box a room object pushes back with (its member at 0x62c): a collision box of the main
 * program (constructor CollisionBox_ConstructBase, vtable 0x020da1b4, set up by CollisionBox_Add and taken out
 * by CollisionBox_Remove) whose one virtual function, called when an actor runs into one of its four
 * sides, is overridden here: when the player walks into a side of an idle object, facing it,
 * the object starts to be pushed (RoomPushes_Record). */
#ifndef CLEAN_OV004_PUSH_BOX_H
#define CLEAN_OV004_PUSH_BOX_H

#include "types.h"

#include "autoload_2/vector.h" /* Vec3 */
#include "main/collision_box.h"
#include "main/field_collision.h"

struct RoomObject;

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
    CollisionBox base;        /* base.active clear: RoomObject_UpdateBoxAndShadow does not update it */
    struct RoomObject *owner; /* the object it belongs to while it is in the world */
} PushBox;

void PushBox_SettlePivot(PushBox *box, PushingActor *actor);
void PushBox_OnSideHit(PushBox *box, CollisionWall *side, PushingActor *actor, fx32 standoff);
void PushBox_ClearOwner(PushBox *box);
void PushBox_SetOwner(PushBox *box, struct RoomObject *owner);
PushBox *PushBox_Destruct(PushBox *box);
PushBox *PushBox_Construct(PushBox *box);

#endif
