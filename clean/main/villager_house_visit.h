/* The record at 0xa4 of the villagers' part of a player's record (VillagerPart,
 * villager_part.h): a villager's visit to the player's house, agreed in a talk
 * (VillagerTalkSteps_SetHouseVisit sets it with the villager's NpcId and the time agreed, and
 * empties the villager's own errand). Overlay 68's house visitor runs the visit from it
 * (ov068 house_visitor.h, the "q10_*" texts).
 *
 *   0x00  the villager's NpcId
 *   0x10  an errand (villager_errand.h): type 21, no item, its date set when the visit was
 *         agreed; its progress says how far the visit went (HOUSE_VISITOR_VISIT_* of ov068)
 *   0x1c  the time agreed
 *   0x24  a byte whose low three bits are the rating the villager gave the room, by which
 *         VillagerTown_ExpireHouseVisits sends its "re_q10" letter
 *
 * It is emptied when it expires (villager_town.c). */
#ifndef CLEAN_MAIN_VILLAGER_HOUSE_VISIT_H
#define CLEAN_MAIN_VILLAGER_HOUSE_VISIT_H

#include "calendar.h"
#include "npc_id.h"
#include "types.h"

/* The errand's type: the visit to the player's house. */
#define VILLAGER_HOUSE_VISIT_TYPE 21

typedef struct VillagerHouseVisit {
    NpcId npc;     /* 0x00 */
    u8 object[12]; /* 0x10 */
    DateTime date; /* 0x1c */
    u8 rating;     /* 0x24: bits 0-2 the room's rating */
    u8 unused_25[3];
} VillagerHouseVisit;

void VillagerHouseVisit_Set(VillagerHouseVisit *visit, const NpcId *npc, const DateTime *date);
int VillagerHouseVisit_IsFrom(VillagerHouseVisit *visit, const NpcId *npc);
void VillagerHouseVisit_Clear(VillagerHouseVisit *visit);
VillagerHouseVisit *VillagerHouseVisit_Destruct(VillagerHouseVisit *visit);
VillagerHouseVisit *VillagerHouseVisit_Construct(VillagerHouseVisit *visit);

#endif
