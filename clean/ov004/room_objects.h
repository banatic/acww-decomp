/* The room's objects as a whole (room_object.h for one of them): the table of the room's
 * objects (func_ov004_0223ce84, as many entries as RoomObjects_Capacity gives for the scene) and
 * the grid of the cells they stand on (func_ov004_0223cd50, two layers of 16 x 16 cells, the
 * floor and on top of other furniture). Here are the queries over them: the one in front of the
 * player, the ones switched on, the height at a cell, whether a point ahead of an actor is free,
 * switching or taking one away, and spawning the actor of a newly placed object.
 *
 * A cell is 0x2000 units of position wide (data_020ca0e8, the room being one acre of 16 x 16
 * cells). */
#ifndef CLEAN_OV004_ROOM_OBJECTS_H
#define CLEAN_OV004_ROOM_OBJECTS_H

#include "types.h"

#include "autoload_2/vector.h"
#include "main/lookups.h" /* ItemCode */
#include "room_object.h"

#define ROOM_OBJECTS_LAYER_FLOOR 0
#define ROOM_OBJECTS_LAYER_ON_TOP 1

/* What RoomObjects_FindAhead gives besides an object's index. */
#define ROOM_OBJECTS_AHEAD_NONE (-1)
#define ROOM_OBJECTS_AHEAD_FLOOR_ITEM (-2) /* an item of kind 1 lying on the cell ahead */

/* What RoomObjects_PointAheadState gives. */
enum RoomObjectsPointState {
    ROOM_OBJECTS_POINT_BLOCKED = 0, /* not at floor height, or something is on the cell */
    ROOM_OBJECTS_POINT_CROWDED = 1, /* someone stands near it */
    ROOM_OBJECTS_POINT_FREE = 2
};

/* A test of a room object the game hands to the queries below (a function of the game's). */
typedef int (*RoomObjectsTest)(RoomObject *object);

int RoomObjects_Stub0223b334(Vec3 *position, s16 angle);
int RoomObjects_Stub0223b338(Vec3 *position, s16 angle);
int RoomObjects_Stub0223b33c(Vec3 *position, s16 angle);
int RoomObjects_RequestOnAt(int x, int z);
int RoomObjects_RequestOn(RoomObject *object);
int RoomObjects_RequestOffAt(int x, int z);
int RoomObjects_RequestOff(RoomObject *object);
int RoomObjects_CellAhead(int *x, int *z, const Vec3 *position, int angle, int pass);
int RoomObjects_IsIdleAt(int index);
int RoomObjects_IsIdleAndBare(RoomObject *object);
void RoomObjects_SetVanishPoint(const Vec3 *point);
const Vec3 *RoomObjects_VanishPoint(int index);
int RoomObjects_Take(int index);
int RoomObjects_TakeWithItem(unsigned int index, ItemCode *item, ItemCode *item_copy);
int RoomObjects_Unk288Of(unsigned int index);
int RoomObjects_FindAheadOfPlayer(int *x, int *z, ItemCode *item, ItemCode *item_copy);
int RoomObjects_FindAhead(int *x, int *z, const Vec3 *position, int angle, ItemCode *item, ItemCode *item_copy);
int RoomObjects_InNookOrScene0AOr0F(void);
int RoomObjects_Capacity(void);
int RoomObjects_PickUnk778(int key);
RoomObject *RoomObjects_PickOn(RoomObjectsTest test, int pending);
int RoomObjects_CountOn(RoomObjectsTest test);
void RoomObjects_SetSwitches(int value, RoomObjectsTest test, int pending);
int RoomObjects_SyncKind3AOn(void);
int RoomObjects_IsFreeAt270(Vec3 *position, int angle);
int RoomObjects_IsFreeAt90(Vec3 *position, int angle);
int RoomObjects_IsFreeAhead(Vec3 *position, int angle);
int RoomObjects_PointAheadState(Vec3 *position, int angle, fx32 reach);
int RoomObjects_CheckStepXMinus(Vec3 *point, int angle);
int RoomObjects_CheckStepXPlus(Vec3 *point, int angle);
int RoomObjects_CheckStep(Vec3 *point, int angle, Vec3 *offset);
fx32 RoomObjects_HeightAtPoint(const Vec3 *point);
fx32 RoomObjects_HeightAtCell(int x, int z);
void RoomObjects_Place(int x, int z, int number, int side, u8 layer, int mode);
int RoomObjects_Spawn(u32 placement);

#endif
