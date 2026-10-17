/* The room's objects as a whole (room_object.h for one of them): the table of the room's
 * objects (RoomObjects_Table, as many entries as RoomObjects_Capacity gives for the scene), the
 * grid of the cells they stand on (RoomObjects_Grid, two layers of 16 x 16 cells, the floor and
 * on top of other furniture) and the heap they are made in (RoomObjects_Heap). Here are the
 * queries over them: the one in front of the
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

/* The grid of the cells (RoomObjects_Grid): ROOM_OBJECTS_LAYERS layers of ROOM_OBJECTS_CELLS
 * rows of ROOM_OBJECTS_CELLS cells, a byte each. */
#define ROOM_OBJECTS_LAYERS 2
#define ROOM_OBJECTS_CELLS 16
#define ROOM_OBJECTS_NO_INDEX 0xff /* a cell without an object */

RoomObject *RoomObjects_GridObjectAtPoint(u8 *grid, const Vec3 *point, int layer);
RoomObject *RoomObjects_GridObjectAt(u8 *grid, int x, int z, int layer);
int RoomObjects_GridIndexAt(u8 *grid, int x, int z, int layer);
int RoomObjects_GridClearCell(u8 *grid, RoomObject *object, int x, int z, u8 layer);
int RoomObjects_GridSetCell(u8 *grid, RoomObject *object, int x, int z, u8 layer);
void RoomObjects_GridClear(u8 *grid);
void RoomObjects_GridDestruct(void *grid);
u8 *RoomObjects_GridConstruct(u8 *grid);
u8 *RoomObjects_Grid(void);

/* The table of the room's objects (RoomObjects_Table). Its size is fixed; the scene uses the
 * first RoomObjects_Capacity entries. */
#define ROOM_OBJECTS_TABLE_SIZE 0x1c

RoomObject *RoomObjects_At(RoomObject **table, unsigned int index);
int RoomObjects_IndexOf(RoomObject **table, RoomObject *object);
int RoomObjects_FreeCount(RoomObject **table);
int RoomObjects_UsedCount(RoomObject **table);
int RoomObjects_Remove(RoomObject **table, RoomObject *object);
int RoomObjects_Add(RoomObject **table, RoomObject *object);
void RoomObjects_TableClear(RoomObject **table);
void RoomObjects_TableDestruct(void *table);
RoomObject **RoomObjects_TableConstruct(RoomObject **table);
RoomObject **RoomObjects_Table(void);

/* The room's heap (RoomObjects_Heap), where the room's objects are made. */
struct Heap;
void RoomObjects_HeapFree(struct Heap **heap, void *block);
void *RoomObjects_HeapAlloc(struct Heap **heap, int size);
void RoomObjects_HeapDelete(struct Heap **heap);
int RoomObjects_HeapCreate(struct Heap **heap, int count);
void RoomObjects_HeapForget(struct Heap **heap);
void RoomObjects_HeapDestruct(void *heap);
struct Heap **RoomObjects_HeapConstruct(struct Heap **heap);
struct Heap **RoomObjects_Heap(void);

#endif
