/* The town's villagers as one block (data_021e5a2c): the eight villagers, then what the town
 * keeps about them as a group.
 *
 *   0x0000  eight villagers of 0x7ec bytes, each with its NpcId at 0x7a0 (func_0208150c); a
 *           villager whose NpcId is not valid (NpcId_IsValid) is an empty place
 *   0x3f60  how each pair of villagers gets on (villager_bonds.h)
 *   0x3f7c  who is out walking (villager_outdoors.h)
 *   0x3f90  one villager sick in bed (villager_sickness.h)
 *   0x404c  a date and whether it is set (VillagerTown_SetDate404C)
 *   0x4050  when a villager last moved in (or the town started); kept from being after the
 *           clock (VillagerTown_Update); a villager is due to leave a set number of days after
 *   0x4058  when a villager last left, unset until one has; moved with the time above while set;
 *           the next villager is due to move in a set number of days after
 *   0x4060  the numbers of the villagers that have lived in the town (a bit each), then at
 *           0x4074 the number of the villager that last left
 *   0x4075  the villager that moved in last (VillagerResidents_SetNewcomer), or -1; it is never
 *           the next to leave
 *   0x4076  the villager index last picked to fall sick (VillagerSickness_PickVillager)
 *   0x4078  a marked villager: bit 1 set, its index in bits 2-4 (VillagerTown_Mark)
 *   0x407a  the day the per-day update last ran (VillagerTown_StartDay)
 *
 * Each villager also has an entry of the running state table (villager_state.h), found by
 * func_0207f270, and a memory of each player it knows (func_020807a8: 0x80 bytes, its signed
 * byte 0x6c how fond the villager is of the player, its halfword 0x7c flags). */
#ifndef CLEAN_MAIN_VILLAGER_TOWN_H
#define CLEAN_MAIN_VILLAGER_TOWN_H

#include "calendar.h"
#include "mail.h"
#include "npc_id.h"
#include "types.h"
#include "villager_sickness.h"
#include "villager_outdoors.h"
#include "villager_state.h"

#define VILLAGER_TOWN_VILLAGERS 8
#define VILLAGER_TOWN_VILLAGER_SIZE 0x7ec
#define VILLAGER_TOWN_PAIRS 28
#define VILLAGER_TOWN_NONE (-1)

/* The marked villager's halfword at 0x4078. */
#define VILLAGER_TOWN_MARKED 0x0002
#define VILLAGER_TOWN_MARK_SHIFT 2
#define VILLAGER_TOWN_MARK_INDEX 0x001c

/* The events of the calendar this block looks for (data_020cd524). */
#define VILLAGER_TOWN_EVENTS 11

typedef struct VillagerTown {
    u8 villagers[VILLAGER_TOWN_VILLAGERS][VILLAGER_TOWN_VILLAGER_SIZE]; /* 0x0000 */
    s8 bonds[VILLAGER_TOWN_PAIRS];                                      /* 0x3f60 */
    VillagerOutdoors outdoors;                                          /* 0x3f7c */
    VillagerSickness sickness;                                          /* 0x3f90 */
    Date date_404c;          /* 0x404c: its last byte (0x404f) set once the date is */
    DateTime last_arrival;   /* 0x4050 */
    DateTime last_departure; /* 0x4058 */
    u8 numbers_met[0x15];    /* 0x4060: a bit for each NpcId number met (five words), then the number gone */
    s8 newcomer_index;       /* 0x4075 */
    s8 last_sick;            /* 0x4076 */
    u8 unknown_4077;
    u16 mark;      /* 0x4078: VILLAGER_TOWN_MARK* */
    Date last_day; /* 0x407a */
} VillagerTown;

/* An event of the calendar on a date, as func_0203fea0 lists them (at most seven). */
typedef struct VillagerTownEvent {
    u16 id; /* 0x00: an event, or for some events a villager index */
    u16 half_02;
    u32 word_04;
    u32 word_08;
} VillagerTownEvent;

#define VILLAGER_TOWN_DAY_EVENTS 7

void VillagerTown_ClearMemoryFlags(VillagerTown *town);
int VillagerTown_IsMarked(VillagerTown *town, const NpcId *npc);
void VillagerTown_Mark(VillagerTown *town, const NpcId *npc);
void VillagerTown_ClearMark(VillagerTown *town);
int VillagerTown_GiveLetter(VillagerTown *town, Letter *letter);
int VillagerTown_AllRemember(VillagerTown *town, const void *player);
void VillagerTown_SetDate404C(VillagerTown *town, const Date *date);
int VillagerTown_IsFarFromDate404C(VillagerTown *town, const Date *date);
void VillagerTown_PickBirthdayVisitor(VillagerTown *town, void *record);
int VillagerTown_FondestOf(VillagerTown *town, const void *player);
void VillagerTown_PickFleaMarketVisitor(VillagerTown *town);
int VillagerTown_PickOutsideAcquaintance(VillagerTown *town);
void VillagerTown_ApplyBirthdayStates(VillagerTown *town);
void VillagerTown_UpdateBirthdayVillager(VillagerTown *town);
int VillagerTown_FindBirthdayVillager(const VillagerTown *town, const DateTime *when);
int VillagerTown_ClosestCompanion(VillagerTown *town, int villager);
void VillagerTown_SendBirthdayNotices(VillagerTown *town);
void VillagerTown_ClearMoods(VillagerTown *town);
void VillagerTown_ScoreAllRooms(VillagerTown *town);
void VillagerTown_ScoreRoom(VillagerTown *town, int villager);
void VillagerTown_UpdateAlone(VillagerTown *town, const void *player);
void VillagerTown_PickFortuneGiver(VillagerTown *town, const void *player);
void VillagerTown_HalveByte1E(VillagerTown *town);
void VillagerTown_DoubleByte1E(VillagerTown *town);
void VillagerTown_SetByte1E(VillagerTown *town, void *record);
int VillagerTown_NextEvent(unsigned int days, const DateTime *from);
int VillagerTown_CurrentEvent(void);
void VillagerTown_PickFoxPasswordVillager(VillagerTown *town);
void VillagerTown_UpdateVillagers(VillagerTown *town, int skip_designs);
void VillagerTown_ExpirePlayerObjects(VillagerTown *town, const DateTime *now);
VillagerState *VillagerTown_StateAt(int index);
void VillagerTown_StartDay(VillagerTown *town);
void VillagerTown_Update(VillagerTown *town, int skip_designs);
void VillagerTown_UpdateWithClock(VillagerTown *town);
void VillagerTown_CheckObjects(VillagerTown *town);
void VillagerTown_UpdateObjects(VillagerTown *town, const DateTime *now);
void VillagerTown_StartLeaving(VillagerTown *town, const DateTime *now);

#endif
