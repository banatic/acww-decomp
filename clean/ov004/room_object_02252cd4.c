/* The room objects of vtable 0x02252cd4 (room_object_02252cd4.h). */
#include "room_object_02252cd4.h"

#include <stdint.h>

#include "cells.h"
#include "clean.h"
#include "room_object_anims.h"
#include "room_object_life.h"
#include "room_object_map.h"

static_assert(offsetof(RoomObject, position) == 0x5c, "position");
static_assert(offsetof(RoomObject, angle) == 0x8e, "angle");
static_assert(offsetof(RoomObject, node_set) == 0x764, "node set");
static_assert(offsetof(RoomObject, unk_780) == 0x780, "kind");
static_assert(offsetof(RoomObject, unk_784) == 0x784, "shape");
static_assert(offsetof(RoomObject02252cd4, push_frames) == 0x844, "push frames");
static_assert(sizeof(RoomObject02252cd4) == 0x848, "the size RoomObject02252cd4_Create allocates");

#define ROOM_OBJECT_02252CD4_SIZE 0x848
#define ONE 0x1000         /* normal speed, 20.12 fixed point */
#define ANIM_MODE_LOOP 0   /* RoomObject_LoadAnims: start again at the end */
#define KIND_9 9           /* RoomObject.unk_780 of the kind animated every frame */
#define KIND_26 0x26       /* RoomObject.unk_780 of the kind with three entry states */
#define KIND_2C 0x2c       /* RoomObject.unk_780 of the kind stood on */
#define PLAYER_COUNT 4     /* the actors func_ov004_0222c268 is asked for */
#define PUSH_FRAMES 7      /* frames counted before the player is sent */
#define MOVED_ENOUGH 0x200 /* how far the entry must have moved (func_ov004_0223cb30) */
#define AHEAD 0x1000       /* added to the entry's distance for the point in front of it */
#define PLAYER_REACH 0x800 /* what Actors_NoneNear is given */
#define NPC_REACH 0x2000
#define PLAYER_RADIUS 0x800

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02252cd4[];
extern const u8 data_ov004_02252d80[];

/* Its entry among two (func_ov004_0223ca9c of func_ov004_0223cb10) and the parts of one: an
 * angle, a state, a point, a distance and how far it has moved. */
extern void *func_ov004_0223cb10(void);
extern void *func_ov004_0223ca9c(void *entries, RoomObject02252cd4 *object);
extern int func_ov004_0223cb18(void *entry);
extern u32 func_ov004_0223cb20(void *entry);
extern Vec3 *func_ov004_0223cb24(void *entry);
extern u32 func_ov004_0223cb2c(void *entry);
extern int func_ov004_0223cb30(void *entry);
/* Whether the entry's push may start. */
extern int func_ov004_0223c700(void);

/* Where player `actor` stands when it is in state 0x28; whether it is. */
extern int func_ov004_0222c268(Vec3 *point, int actor);
/* The player (actor 4) sent to (`*x`, `*z`) facing away from `*angle`, with `*action`, unless it
 * is already in move 6 or later; whether it was. */
extern int func_ov004_0222c0b8(s32 *x, s32 *z, s16 *angle, u8 *action);
/* The cell of a point of the town's map. */
extern void func_0204f818(s32 *x, s32 *y, const Vec3 *point);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);

/* func_ov004_02218848: the point checked for people in front of the entry: the object's own
 * position for a shape of one cell (RoomObject.unk_784 0), else the entry's point moved by its
 * distance plus 0x1000 along its angle. */
void RoomObject02252cd4_ProbePoint(RoomObject02252cd4 *object, Vec3 *out, void *entry)
{
    if (object->base.unk_784 == 0) {
        *out = object->base.position;
        return;
    }
    *out = *func_ov004_0223cb24(entry);
    Vec3 ahead = {0, 0, (s32) (func_ov004_0223cb2c(entry) + AHEAD)};
    Vec_RotateY(&ahead, func_ov004_0223cb18(entry));
    VEC_Add(out, &ahead, out);
}
CLEAN_AS(func_ov004_02218848, RoomObject02252cd4_ProbePoint)

/* func_ov004_022188b4 (vtable slot 0x0c) */
int RoomObject02252cd4_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022188b4, RoomObject02252cd4_Vfunc0C)

/* Kind 0x2c: the node set's value 0, or 1 while a player stands on one of its cells (each such
 * player also advancing the animations and playing sound 0). */
static void RoomObject02252cd4_update_stood_on(RoomObject02252cd4 *object)
{
    RoomObject *base = &object->base;
    ByteSet_SetValue(&base->node_set, 0);
    for (int i = 0; i < PLAYER_COUNT; i++) {
        Vec3 point;
        if (func_ov004_0222c268(&point, i) == 0) {
            continue;
        }
        s32 x;
        s32 y;
        func_0204f818(&x, &y, &point);
        CellList cells;
        CellList_Construct(&cells);
        RoomObject_ListCells(base, &cells, NULL, 0);
        for (unsigned long j = 0; j < CellList_Count(&cells); j++) {
            if (x == CellList_At(&cells, (int) j)->x && y == CellList_At(&cells, (int) j)->y) {
                ByteSet_SetValue(&base->node_set, 1);
                RoomObject_AdvanceAnims(base);
                RoomObject_PlaySound0(base);
                break;
            }
        }
        CellList_Destruct(&cells);
    }
}

/* Whether the entry's state lets the player be sent, and the action it is sent with: state 0
 * (action 0); for kind 0x26 also state 3 (action 1) and state 1 (action 2). The entry's state
 * is read again for each comparison. */
static int RoomObject02252cd4_entry_ready(RoomObject02252cd4 *object, void *entry, u8 *action)
{
    *action = 0;
    if (object->base.unk_780 != KIND_26) {
        return func_ov004_0223cb20(entry) == 0;
    }
    if (func_ov004_0223cb20(entry) == 0) {
        return 1;
    }
    if (func_ov004_0223cb20(entry) == 3) {
        *action = 1;
        return 1;
    }
    if (func_ov004_0223cb20(entry) == 1) {
        *action = 2;
        return 1;
    }
    return 0;
}

/* func_ov004_022188b8 (vtable slot 0x80, each frame while neither appearing nor vanishing):
 * kinds 0x2c and 9 as the class says (room_object_02252cd4.h); then, with its entry ready and
 * nobody near the point in front of it, the count of frames rises to 7, and once the entry has
 * moved more than 0x200 with the count at 7 the player is sent there and the count cleared. A
 * frame that did not raise the count clears it.
 * QUIRK: so the count, once at 7, is cleared the next frame whether or not the player was sent;
 * the player is sent on the frame the count reaches 7 or on the one after. */
int RoomObject02252cd4_Update(RoomObject02252cd4 *object)
{
    RoomObject *base = &object->base;
    if (base->unk_780 == KIND_2C) {
        RoomObject02252cd4_update_stood_on(object);
    } else if (base->unk_780 == KIND_9) {
        RoomObject_AdvanceAnims(base);
        RoomObject_PlaySound0(base);
    }
    int counted = 0;
    void *entry = func_ov004_0223ca9c(func_ov004_0223cb10(), object);
    if (entry != NULL && func_ov004_0223c700() != 0) {
        u8 action;
        if (RoomObject02252cd4_entry_ready(object, entry, &action)) {
            Vec3 point;
            RoomObject02252cd4_ProbePoint(object, &point, entry);
            if (Actors_NoneNear(&point, PLAYER_REACH, NPC_REACH, PLAYER_RADIUS, 0)) {
                if (object->push_frames < PUSH_FRAMES) {
                    counted = 1;
                    object->push_frames++;
                }
                if (func_ov004_0223cb30(entry) > MOVED_ENOUGH && object->push_frames >= PUSH_FRAMES) {
                    func_ov004_0222c0b8(&point.x, &point.z, &base->angle, &action);
                    object->push_frames = 0;
                }
            }
        }
    }
    if (!counted) {
        object->push_frames = 0;
    }
    return 1;
}
CLEAN_AS(func_ov004_022188b8, RoomObject02252cd4_Update)

/* func_ov004_02218a5c (vtable slot 0x7c, once the model is bound): the node set's value 0; kinds
 * 9 and 0x2c bind the animations of variant 0 in a loop from the start. Done at once. */
int RoomObject02252cd4_Start(RoomObject02252cd4 *object)
{
    RoomObject *base = &object->base;
    ByteSet_SetValue(&base->node_set, 0);
    if (base->unk_780 == KIND_9 || base->unk_780 == KIND_2C) {
        RoomObject_LoadAnims(base, 0, ANIM_MODE_LOOP, ONE, 0);
    }
    return 1;
}
CLEAN_AS(func_ov004_02218a5c, RoomObject02252cd4_Start)

static void RoomObject02252cd4_set_vtables(RoomObject02252cd4 *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_02252cd4;
    object->base.receiver_vtable = data_ov004_02252d80;
}

/* func_ov004_02218a9c (the deleting destructor, vtable slot 0x44) */
RoomObject02252cd4 *RoomObject02252cd4_Delete(RoomObject02252cd4 *object)
{
    RoomObject02252cd4_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_02218a9c, RoomObject02252cd4_Delete)

/* func_ov004_02218ac8 (the destructor, vtable slot 0x40) */
RoomObject02252cd4 *RoomObject02252cd4_Destroy(RoomObject02252cd4 *object)
{
    RoomObject02252cd4_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_02218ac8, RoomObject02252cd4_Destroy)

/* func_ov004_02218aec (the constructor). Its own fields are left as the allocation zeroed
 * them. */
RoomObject02252cd4 *RoomObject02252cd4_Construct(RoomObject02252cd4 *object)
{
    RoomObject_ConstructBase(&object->base);
    RoomObject02252cd4_set_vtables(object);
    return object;
}
CLEAN_AS(func_ov004_02218aec, RoomObject02252cd4_Construct)

/* func_ov004_02218b10: a new one from the room's heap; nothing when it has no room. */
void RoomObject02252cd4_Create(void)
{
    RoomObject02252cd4 *object = RoomObject_Alloc(ROOM_OBJECT_02252CD4_SIZE);
    if (object != NULL) {
        RoomObject02252cd4_Construct(object);
    }
}
CLEAN_AS(func_ov004_02218b10, RoomObject02252cd4_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters RoomObject02252cd4's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static RoomObject02252cd4 *RoomObject02252cd4_from_receiver(void *receiver)
{
    return (RoomObject02252cd4 *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221a6ec: the deleting destructor, entered from the receiver part. */
RoomObject02252cd4 *RoomObject02252cd4Receiver_Delete(void *receiver)
{
    return RoomObject02252cd4_Delete(RoomObject02252cd4_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02252cd4D0Ev, RoomObject02252cd4Receiver_Delete)

/* func_ov004_0221a708: the destructor, entered from the receiver part. */
RoomObject02252cd4 *RoomObject02252cd4Receiver_Destroy(void *receiver)
{
    return RoomObject02252cd4_Destroy(RoomObject02252cd4_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02252cd4D1Ev, RoomObject02252cd4Receiver_Destroy)
