/* The record of a villager's plan to move away (VillagerMove, villager_move.h): set up, cleared,
 * and the player ids of its stages (DesignCreator, 30 bytes: a town and a player).
 *
 * A plan starts (VillagerMoveRecord_Start) at stage 1 or 2 for a villager, with an object of
 * type 9 and item 0x155e; stage 5 is no plan. Each stage may name a player
 * (VillagerMoveRecord_SetStagePlayer); the player named most often is found by
 * VillagerMoveRecord_MostNamedPlayer. */
#ifndef CLEAN_MAIN_VILLAGER_MOVE_RECORD_H
#define CLEAN_MAIN_VILLAGER_MOVE_RECORD_H

#include "calendar.h"
#include "design.h"
#include "npc_id.h"
#include "types.h"
#include "villager_move.h"

/* The object a plan starts with. */
#define VILLAGER_MOVE_RECORD_TYPE 9
#define VILLAGER_MOVE_RECORD_ITEM 0x155e
/* How many days after the last step a finished plan counts as recent. */
#define VILLAGER_MOVE_RECORD_RECENT_DAYS 3

DesignCreator *VillagerMoveRecord_MostNamedPlayer(VillagerMove *move);
int VillagerMoveRecord_IsRecentlyDone(VillagerMove *move, const Date *today);
int VillagerMoveRecord_IsIdle(const VillagerMove *move);
void VillagerMoveRecord_SetStagePlayer(VillagerMove *move, const DesignCreator *player);
int VillagerMoveRecord_HasStagePlayer(VillagerMove *move);
int VillagerMoveRecord_NamesPlayer(VillagerMove *move, const DesignCreator *player);
DesignCreator *VillagerMoveRecord_StagePlayer(VillagerMove *move);
DesignCreator *VillagerMoveRecord_Player(VillagerMove *move, u32 stage);
void VillagerMoveRecord_Start(VillagerMove *move, const NpcId *npc, const Date *today);
NpcId *VillagerMoveRecord_Npc(VillagerMove *move);
u8 *VillagerMoveRecord_Object(VillagerMove *move);
void VillagerMoveRecord_Clear(VillagerMove *move);
VillagerMove *VillagerMoveRecord_Destruct(VillagerMove *move);
VillagerMove *VillagerMoveRecord_Construct(VillagerMove *move);

#endif
