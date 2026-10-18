/* A room object (room_object.h) on the town's map: the cells it covers, putting it on the map
 * and taking it off (the map's record of its item code, RoomSync_PutFurniture and RoomSync_TakeFurniture, and
 * the grid of the room's objects, RoomObjects_Grid), moving it with the objects standing
 * on it, and whether a move or a turn is free: no player, item or other object in the way. */
#ifndef CLEAN_OV004_ROOM_OBJECT_MAP_H
#define CLEAN_OV004_ROOM_OBJECT_MAP_H

#include "types.h"

#include "main/lookups.h" /* ItemCode */
#include "room_object.h"

/* An actor of the main program (SessionPlayers_ActorOf, Actors_Slot): its position and facing. */
typedef struct MapActor {
    u8 unk_00[0x5c];
    Vec3 position;
    u8 unk_68[0x26];
    u16 angle;
} MapActor;

int RoomObject_CanMoveOrTurn(RoomObject *object, Vec3 *offset, int turn);
int RoomObject_CanMove(RoomObject *object, Vec3 *offset);
int RoomObject_CanTurn(RoomObject *object, int turn);
int RoomObject_HasItemsOnTop(RoomObject *object);
void RoomObject_MoveOnMap(RoomObject *object, Vec3 *offset, int turn);
void RoomObject_PutOnMap(RoomObject *object, int unused, Vec3 *offset, int turn, u8 update_reference);
void RoomObject_TakeOffMap(RoomObject *object, u8 flag, int with_top);
int RoomObject_FacingItemCode(ItemCode *code, RoomObject *object, int angle);
int Angle_Side(int angle);
void RoomObject_ListCells(RoomObject *object, CellList *cells, Vec3 *offset, int turn);
int RoomObject_MountParent(RoomObject *object);
int Actors_NoneNear(Vec3 *point, fx32 player_reach, fx32 npc_reach, fx32 player_radius, fx32 npc_radius);
int Actors_AreNear(Vec3 *point, fx32 reach, Vec3 *other, fx32 radius);
int Room_Check0220fed0(void);

#endif
