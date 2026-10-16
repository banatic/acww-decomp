/* One villager's plan to move away: the record at 0x3f90 of the town's villagers
 * (villager_town.h).
 *
 * The record names a villager by its NpcId (at 0x0c) when its object (at 0x00, func_0209bd44)
 * holds something. While it does, the villager stays out of the ones drawn to walk outside
 * (villager_outdoors.h). It is read here as a plan to move away from what sets it up: only in
 * a town of seven or more villagers, a villager picked by a monthly chance
 * (VillagerMove_PickVillager), with an object of type 9 and item 0x155e (func_0209a710).
 *
 * The plan goes through stages 0-4 (byte 0xba), one step each day (VillagerMove_Step); each
 * stage has a player id of 30 bytes (at 0x1c), which a step empties. Stage 5 is no plan, or the
 * plan carried out: func_0209a77c clears the record to it. The record keeps the date the plan
 * started (0xb2) and the day of its last step (0xb6). */
#ifndef CLEAN_MAIN_VILLAGER_MOVE_H
#define CLEAN_MAIN_VILLAGER_MOVE_H

#include "calendar.h"
#include "npc_id.h"
#include "types.h"

#define VILLAGER_MOVE_STAGES 5
#define VILLAGER_MOVE_STAGE_NONE 5
#define VILLAGER_MOVE_PLAYER_ID_SIZE 30
/* A town needs this many villagers before one plans to move. */
#define VILLAGER_MOVE_MIN_VILLAGERS 7

typedef struct VillagerMove {
    u8 object[12];                                                  /* 0x00 */
    NpcId npc;                                                      /* 0x0c */
    u8 players[VILLAGER_MOVE_STAGES][VILLAGER_MOVE_PLAYER_ID_SIZE]; /* 0x1c */
    Date started;   /* 0xb2: its last byte (0xb5) set once the first steps are taken */
    Date last_step; /* 0xb6 */
    u8 stage;       /* 0xba */
} VillagerMove;

typedef struct VillagerTown VillagerTown;

void VillagerMove_Update(VillagerTown *town);
void VillagerMove_Step(VillagerTown *town);
int VillagerMove_TownIsFull(VillagerTown *town);
int VillagerMove_PickVillager(VillagerTown *town, unsigned int month);
int VillagerMove_VillagerIndex(VillagerTown *town);
VillagerMove *VillagerMove_Record(VillagerTown *town);

#endif
