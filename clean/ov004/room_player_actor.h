/* What overlay 4's room objects (and a few other overlays) ask of this console's player's field
 * actor (SessionPlayers_FieldActor(4)): each call finds the actor and, when there is one, asks
 * it for one of its room states (field_actor_room_states.h, field_actor_room_states2.h,
 * field_actor_rooms.h, field_actor_place_states.h), nearly always with priority 6 and no
 * argument (-1). Without the actor each answers 0. Also here: where a session player stands
 * while in a given state, and two of this console's actor's flags. */
#ifndef CLEAN_OV004_ROOM_PLAYER_ACTOR_H
#define CLEAN_OV004_ROOM_PLAYER_ACTOR_H

#include "autoload_2/vector.h"
#include "types.h"

int RoomPlayerActor_PlayAnimation98(void);
int RoomPlayerActor_RequestSequence8A(void);
int RoomPlayerActor_RequestFixedPoint(void);
int RoomPlayerActor_RequestSpotStay(void);
int RoomPlayerActor_RequestHangUp(void);
int RoomPlayerActor_RequestPickUp(void);
int RoomPlayerActor_RequestHairOff(const u8 *kind, const u8 *hair_color);
int RoomPlayerActor_RequestItemBack(void);
void *RoomPlayerActor_RequestItemOut(const u16 *item, const int *look, const u8 *stage, const int *kind, int second);
int RoomPlayerActor_RequestExit(void);
int RoomPlayerActor_RequestChestClose(const int *index);
int RoomPlayerActor_RequestChestApproach(const int *index, const s32 *x, const s32 *z, const s16 *yaw);
int RoomPlayerActor_RequestSpotMove(int kind);
int RoomPlayerActor_RequestSpotApproach(const s32 *x, const s32 *z, const s16 *facing, const u8 *way);
int RoomPlayerActor_RequestPlaceOff(int side, int store_sun);
int RoomPlayerActor_RequestPlaceApproach(const fx32 *x, const fx32 *z, const s16 *yaw, s16 facing, int unused);
int RoomPlayerActor_SwitchHeadwear(int on);

int RoomPlayerActor_PointAtPlace(Vec3 *point, int player);
int RoomPlayerActor_PointAtSpot(Vec3 *point, int player);
int RoomPlayerActor_PointInState(Vec3 *point, int player, int state);

int RoomPlayerActor_TestFlag2(void);
int RoomPlayerActor_TestFlag15(void);

#endif
