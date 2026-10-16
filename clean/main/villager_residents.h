/* Villagers moving into and out of the town (VillagerTown, villager_town.h).
 *
 * A villager about to leave has its record's object (at 0x734) in mode 9 (byte 0x10, given
 * by func_0207dc30 with the date of that day); a town of eight with none in mode 9 or 11 gets
 * one when a draw agrees (VillagerResidents_IsLeaveDue, VillagerResidents_PickLeaver). Two
 * days on (VillagerResidents_ReadyLeaver) it goes out of the town into the villager held for
 * the exchange with other towns (data_021ee418 at 0x14c, VillagerResidents_Exchange), and a
 * villager held there from another town takes its place. A town with a free place gets a new
 * villager, drawn from those of the personality fewest villagers have and not yet met, a day
 * or more after the last change (VillagerResidents_MoveInNew).
 *
 * The town's block keeps for this:
 *   0x4058  when a villager last left (all zero until one has)
 *   0x4060  a set of 150 bits, one for each villager number (NpcId.number), the villagers that
 *           have lived in the town; emptied again once all those that can come have
 *   0x4074  the number of the villager that last left, or -1
 *   0x4075  the place of the villager that last moved in, or -1
 *
 * The villagers' data (data_020cd884, 0x4e bytes each, func_02082500) gives each its
 * personality (byte 0x4a) and at byte 0x4b whether it can come: 0 always, 1 only after the
 * first villagers, 2 or more never. */
#ifndef CLEAN_MAIN_VILLAGER_RESIDENTS_H
#define CLEAN_MAIN_VILLAGER_RESIDENTS_H

#include "calendar.h"
#include "npc_id.h"
#include "types.h"
#include "villager_town.h"

#define VILLAGER_RESIDENTS_NUMBER_WORDS 5 /* the words of a set of villager numbers */
#define VILLAGER_RESIDENTS_FIRST_VILLAGERS 3

/* Byte 0x10 of a villager's record object. */
#define VILLAGER_RESIDENTS_MODE_ARRIVED 10 /* given to a villager that moves in */
#define VILLAGER_RESIDENTS_MODE_LEAVING 9
#define VILLAGER_RESIDENTS_MODE_11 11

/* Byte 0x7d6 of a villager: how it came to the town (3 for a villager reset). */
#define VILLAGER_RESIDENTS_CAME_NEW 1
#define VILLAGER_RESIDENTS_CAME_EXCHANGED 2

int VillagerResidents_PickLeaver(VillagerTown *town);
int VillagerResidents_IsLeaveDue(VillagerTown *town, const DateTime *now);
int VillagerResidents_FindMode11(VillagerTown *town);
int VillagerResidents_ReadyLeaver(VillagerTown *town, const DateTime *now);
int VillagerResidents_FindLeaving(VillagerTown *town);
void VillagerResidents_Exchange(VillagerTown *town, const DateTime *now);
void VillagerResidents_MoveOut(VillagerTown *town, u8 *hold, u8 *villager, int index, const DateTime *now);
void VillagerResidents_MoveIn(VillagerTown *town, u8 *place, int index, const u8 *newcomer, unsigned char came,
                              const DateTime *now);
void VillagerResidents_SetNewcomerNpc(VillagerTown *town, const NpcId *npc);
VillagerTown *VillagerResidents_SetNewcomer(VillagerTown *town, unsigned char index);
void VillagerResidents_MoveInNew(VillagerTown *town, const DateTime *now);
int VillagerResidents_PickNumber(VillagerTown *town);
int VillagerResidents_IsArrivalDue(VillagerTown *town, const DateTime *now);
void VillagerResidents_StartTown(VillagerTown *town);
int VillagerResidents_PickPersonality(VillagerTown *town, int excluded);
int VillagerResidents_PickOfPersonality(VillagerTown *town, int personality, int first_villagers);
void VillagerResidents_RefreshMet(u32 *met, VillagerTown *town);
int VillagerResidents_AllMet(const u32 *met);
void VillagerResidents_RemoveNumber(VillagerTown *town, u32 *set, int number);
void VillagerResidents_AddNumber(u32 *set, int number);
int VillagerResidents_HasNumber(int number, const u32 *set);

#endif
