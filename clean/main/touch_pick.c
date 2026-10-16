/* The objects picked with the pen on the field (touch_pick.h). */
#include "touch_pick.h"

#include "clean.h"
#include "main/actor_table.h"
#include "ov003/etc_board.h"
#include "ov004/atm.h"

/* The modes of data_020e54a8: 0 outdoors, 1 in a room. */
#define TOUCH_PICK_MODE_OUTDOORS 0
#define TOUCH_PICK_MODE_ROOM 1

extern u8 data_020e54a8;
/* Each kind's function: the object for an index, or 0. */
extern int (*const data_020e57ac[TOUCH_PICK_KINDS])(int index);

/* Overlay 3's object of an id (of its eight), and its table of 0x20 entries. */
extern int func_ov003_02236204(int id);
extern int func_ov003_022201e4(int index);
/* Overlay 4's tables of 0x40 and 0x20 entries, and two objects it keeps. */
extern int func_ov004_0221ad40(int index);
extern int func_ov004_0221b27c(int index);
extern unsigned int func_ov004_022318f8(void);
extern unsigned int func_ov004_0222fc84(void);
/* Overlay 4's room objects, and the one of an index among them. */
extern void *func_ov004_0223ce84(void);
extern int func_ov004_0223cd58(int objects, int index);
/* The actor of a session player (4 for this system's). */
extern int func_02096190(int player);

/* func_020b7338: the object of kind `kind` with `index`; 0 for a kind of 23 or more.
 * REQUIRES: `kind` is not negative (the table is read at it as the ROM does). */
int TouchPick_Object(int kind, int index)
{
    if (kind < TOUCH_PICK_KINDS) {
        return data_020e57ac[kind](index);
    }
    return 0;
}
CLEAN_AS(func_020b7338, TouchPick_Object)

/* func_020b735c (kinds 17 and 18): outdoors, overlay 3's object with id `id`. */
int TouchPick_OutdoorObjectById(int id)
{
    if (data_020e54a8 == TOUCH_PICK_MODE_OUTDOORS) {
        return func_ov003_02236204(id);
    }
    return 0;
}
CLEAN_AS(func_020b735c, TouchPick_OutdoorObjectById)

/* func_020b7384 (kind 16): in a room, entry `index` of overlay 4's table of 0x40. */
int TouchPick_RoomEntry40(int index)
{
    if (data_020e54a8 == TOUCH_PICK_MODE_ROOM) {
        return func_ov004_0221ad40(index);
    }
    return 0;
}
CLEAN_AS(func_020b7384, TouchPick_RoomEntry40)

/* func_020b73ac (kind 13): in a room, the object overlay 4 keeps at 0x022588c8. */
int TouchPick_RoomObject13(void)
{
    if (data_020e54a8 == TOUCH_PICK_MODE_ROOM) {
        return (int) func_ov004_022318f8();
    }
    return 0;
}
CLEAN_AS(func_020b73ac, TouchPick_RoomObject13)

/* func_020b73d4 (kind 12): in a room, the object overlay 4 keeps at 0x02258490. */
int TouchPick_RoomObject12(void)
{
    if (data_020e54a8 == TOUCH_PICK_MODE_ROOM) {
        return (int) func_ov004_0222fc84();
    }
    return 0;
}
CLEAN_AS(func_020b73d4, TouchPick_RoomObject12)

/* func_020b73fc (kind 14): in a room, entry `index` of overlay 4's table of 0x20. */
int TouchPick_RoomEntry20(int index)
{
    if (data_020e54a8 == TOUCH_PICK_MODE_ROOM) {
        return func_ov004_0221b27c(index);
    }
    return 0;
}
CLEAN_AS(func_020b73fc, TouchPick_RoomEntry20)

/* func_020b7424 (kind 11): in a room, the ATM. */
int TouchPick_Atm(void)
{
    if (data_020e54a8 == TOUCH_PICK_MODE_ROOM) {
        return (int) (uintptr_t) Atm_Current();
    }
    return 0;
}
CLEAN_AS(func_020b7424, TouchPick_Atm)

/* func_020b744c (kind 9): outdoors, the board of index `index`. */
int TouchPick_EtcBoard(int index)
{
    if (data_020e54a8 == TOUCH_PICK_MODE_OUTDOORS) {
        return (int) (uintptr_t) EtcBoard_Get(index);
    }
    return 0;
}
CLEAN_AS(func_020b744c, TouchPick_EtcBoard)

/* func_020b7474 (kinds 8 and 15): in a room, overlay 4's room object of index `index`. */
int TouchPick_RoomObject(int index)
{
    if (data_020e54a8 == TOUCH_PICK_MODE_ROOM) {
        return func_ov004_0223cd58((int) (uintptr_t) func_ov004_0223ce84(), index);
    }
    return 0;
}
CLEAN_AS(func_020b7474, TouchPick_RoomObject)

/* func_020b74a4 (kind 6): TouchPick_OutdoorEntry20.
 * QUIRK: declared without a result, like the kinds 1-3 below; in the ROM the answer of the
 * call it ends with is still in r0 when it returns, and TouchPick_Object hands it on. */
void TouchPick_OutdoorEntryKind6(int index)
{
    (void) TouchPick_OutdoorEntry20(index);
}
CLEAN_AS(func_020b74a4, TouchPick_OutdoorEntryKind6)

/* func_020b74ac (kind 7): outdoors, entry `index` of overlay 3's table of 0x20. */
int TouchPick_OutdoorEntry20(int index)
{
    if (data_020e54a8 == TOUCH_PICK_MODE_OUTDOORS) {
        return func_ov003_022201e4(index);
    }
    return 0;
}
CLEAN_AS(func_020b74ac, TouchPick_OutdoorEntry20)

/* func_020b74d4 (kind 3): Actors_GetDByIndex; its answer left in r0 (see kind 6). */
void TouchPick_ActorD(int index)
{
    (void) Actors_GetDByIndex(index);
}
CLEAN_AS(func_020b74d4, TouchPick_ActorD)

/* func_020b74dc (kind 2): Actors_GetEByIndex; its answer left in r0 (see kind 6). */
void TouchPick_ActorE(int index)
{
    (void) Actors_GetEByIndex(index);
}
CLEAN_AS(func_020b74dc, TouchPick_ActorE)

/* func_020b74e4 (kind 1): the actor of session player `player`; its answer left in r0 (see
 * kind 6). */
void TouchPick_PlayerActor(int player)
{
    (void) func_02096190(player);
}
CLEAN_AS(func_020b74e4, TouchPick_PlayerActor)
