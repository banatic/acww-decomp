/* The objects picked with the pen on the field: a pick (func_020b7524) gives a kind (0-22)
 * and an index, and TouchPick_Object finds the object through the kind's function in the
 * table at data_020e57ac. Many kinds are only found in one mode: the overlay 3 ones outdoors
 * (mode 0), the overlay 4 ones in a room (mode 1); elsewhere they answer 0.
 *
 * The kinds:
 *   1 a session player's actor (func_02096190), 2 and 3 the actor tables E and D
 *   (actor_table.h), 6 and 7 overlay 3's table of 0x20 entries, 8 and 15 a room object of
 *   overlay 4 (room_object_body.c), 9 an "obj_etc_board" (etc_board.h), 11 the ATM (atm.h),
 *   12 and 13 two objects overlay 4 keeps, 14 and 16 overlay 4's tables of 0x20 and 0x40
 *   entries, 17 and 18 an overlay 3 object by its id; the others none (func_020b74ec). */
#ifndef CLEAN_MAIN_TOUCH_PICK_H
#define CLEAN_MAIN_TOUCH_PICK_H

#include "types.h"

#define TOUCH_PICK_KINDS 23

int TouchPick_Object(int kind, int index);
int TouchPick_OutdoorObjectById(int id);
int TouchPick_RoomEntry40(int index);
int TouchPick_RoomObject13(void);
int TouchPick_RoomObject12(void);
int TouchPick_RoomEntry20(int index);
int TouchPick_Atm(void);
int TouchPick_EtcBoard(int index);
int TouchPick_RoomObject(int index);
void TouchPick_OutdoorEntryKind6(int index);
int TouchPick_OutdoorEntry20(int index);
void TouchPick_ActorD(int index);
void TouchPick_ActorE(int index);
void TouchPick_PlayerActor(int player);

#endif
