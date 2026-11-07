/* The objects picked with the pen on the field: a pick (func_020b7524) gives a kind (0-22)
 * and an index, and TouchPick_Object finds the object through the kind's function in the
 * table at data_020e57ac. Many kinds are only found in one mode: the overlay 3 ones outdoors
 * (mode 0), the overlay 4 ones in a room (mode 1); elsewhere they answer 0.
 *
 * The kinds:
 *   1 a session player's actor (func_02096190), 2 and 3 the actor tables E and D
 *   (actor_table.h), 6 and 7 overlay 3's object actors (0x20 entries), 8 and 15 a room object
 *   of overlay 4 (room_object_body.c), 9 a villager's nameplate (villager_nameplate.h), 11 the
 *   ATM (atm.h), 12 overlay 4's recycle bin, 13 its telephone, 14 its museum spots (0x20
 *   entries), 16 its board objects (0x40 entries), 17 and 18 an overlay 3 snowman by its id;
 *   the others none (func_020b74ec). */
#ifndef CLEAN_MAIN_TOUCH_PICK_H
#define CLEAN_MAIN_TOUCH_PICK_H

#include "types.h"

#define TOUCH_PICK_KINDS 23

int TouchPick_Object(int kind, int index);
int TouchPick_Snowman(int id);
int TouchPick_RoomBoard(int index);
int TouchPick_Telephone(void);
int TouchPick_RecycleBin(void);
int TouchPick_MuseumSpot(int index);
int TouchPick_Atm(void);
int TouchPick_VillagerNameplate(int index);
int TouchPick_RoomObject(int index);
void TouchPick_ObjectActorKind6(int index);
int TouchPick_ObjectActor(int index);
void TouchPick_ActorD(int index);
void TouchPick_ActorE(int index);
void TouchPick_PlayerActor(int player);

#endif
