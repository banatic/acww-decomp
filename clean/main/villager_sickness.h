/* One villager sick in bed: the record at 0x3f90 of the town's villagers (villager_town.h).
 *
 * The record names a villager by its NpcId (at 0x0c) when its object (at 0x00, func_0209bd44)
 * holds something: an object of type 9 with item 0x155e, the medicine (func_0209a710). While it
 * does, the villager stays out of the ones drawn to walk outside (villager_outdoors.h) and is
 * found at home, where ov004's sick_villager.h talks with the message files "q12_sick1_2" and
 * "q12_sick3_5" and asks the player for the medicine. A villager falls sick only in a town of
 * seven or more villagers, picked by a monthly chance (VillagerSickness_PickVillager).
 *
 * How sick it is goes through stages 0-4 (byte 0xba), one step each day (VillagerSickness_Step):
 * it gets better when a player handed it the medicine at the current stage (the player id of 30
 * bytes the stage keeps, at 0x1c), or once its first ten days are past, and worse otherwise.
 * Stage 5 is well again, or no one sick: func_0209a77c clears the record to it. The record keeps
 * the date it fell sick (0xb2) and the day of its last step (0xb6); for three days after it got
 * well the villager thanks the player who handed it the medicine most
 * (VillagerTalkOffer_AfterSickness). */
#ifndef CLEAN_MAIN_VILLAGER_SICKNESS_H
#define CLEAN_MAIN_VILLAGER_SICKNESS_H

#include "calendar.h"
#include "npc_id.h"
#include "types.h"

#define VILLAGER_SICKNESS_STAGES 5
/* The stage of a villager well again, or of no one sick. */
#define VILLAGER_SICKNESS_WELL 5
#define VILLAGER_SICKNESS_PLAYER_ID_SIZE 30
/* A town needs this many villagers before one falls sick. */
#define VILLAGER_SICKNESS_MIN_VILLAGERS 7

typedef struct VillagerSickness {
    u8 object[12];                                                          /* 0x00 */
    NpcId npc;                                                              /* 0x0c */
    u8 players[VILLAGER_SICKNESS_STAGES][VILLAGER_SICKNESS_PLAYER_ID_SIZE]; /* 0x1c */
    Date started;   /* 0xb2: its last byte (0xb5) set once the first steps are taken */
    Date last_step; /* 0xb6 */
    u8 stage;       /* 0xba */
} VillagerSickness;

typedef struct VillagerTown VillagerTown;

void VillagerSickness_Update(VillagerTown *town);
void VillagerSickness_Step(VillagerTown *town);
int VillagerSickness_HasEnoughVillagers(VillagerTown *town);
int VillagerSickness_PickVillager(VillagerTown *town, unsigned int month);
int VillagerSickness_VillagerIndex(VillagerTown *town);
VillagerSickness *VillagerSickness_Record(VillagerTown *town);

#endif
