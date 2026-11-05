/* Tests of one of the town's villagers (villager_checks.h). */
#include "villager_checks.h"

#include <string.h>

#include "clean.h"
#include "npc_id.h"
#include "player_records.h"
#include "villager_sickness.h"
#include "villager_roster.h"
#include "villager_state.h"
#include "villager_town.h"
#include "player_id.h"
#include "player_record.h"
#include "town_villager.h"
#include "villager_sickness_record.h"
#include "villager_status.h"

/* What func_0207f150 gives a villager that lives in the town as usual. */
#define VILLAGER_CHECK_RESIDENT 3

extern u8 data_021e5a2c[]; /* the town's villagers (VillagerTown) */
extern u8 data_021dc7bc[]; /* the four players' records */

static VillagerTown *town(void)
{
    return (VillagerTown *) (void *) data_021e5a2c;
}

static int same_npc(const NpcId *a, const NpcId *b)
{
    return a->town.number == b->town.number && memcmp(a->town.name, b->town.name, sizeof(a->town.name)) == 0 &&
           a->number == b->number;
}

/* func_0207d6c4: whether the villager lives in the town as usual and is not the one the town's
 * sickness record names (the personality is not compared). */
int VillagerCheck_IsWellResident(u8 *villager)
{
    NpcId *npc = TownVillager_NpcId(villager);
    if (!NpcId_IsValid(npc) || VillagerStatus_Stay(villager) != VILLAGER_CHECK_RESIDENT) {
        return 0;
    }
    NpcId *sick = VillagerSicknessRecord_Npc(VillagerSickness_Record(town()));
    return !same_npc(npc, sick);
}
CLEAN_AS(func_0207d6c4, VillagerCheck_IsWellResident)

/* func_0207dca8: 1 unless the record of one of the town's four players (one whose id is set)
 * holds an object for the villager. */
int VillagerCheck_NoPlayerHolds(u8 *villager)
{
    for (int i = 0; i < PLAYER_RECORDS_TOWN; i++) {
        u8 *record = PlayerRecords_TownRecord(data_021dc7bc, i);
        if (PlayerId_IsSet(PlayerRecord_Player(record)) == 0) {
            continue;
        }
        if (VillagerStatus_PlayerHolds(villager, PlayerRecord_VillagerPart(record)) != 0) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_0207dca8, VillagerCheck_NoPlayerHolds)

/* func_0207dd1c: whether the villager is the one that tells today's fox password (the state
 * table's 0x161). */
int VillagerCheck_TellsFoxPassword(u8 *villager)
{
    int named = (s8) VillagerState_Table()->fox_password_villager;
    int index = VillagerRoster_IndexOf(town(), TownVillager_NpcId(villager));
    return NpcId_IsValid(TownVillager_NpcId(villager)) && index == named;
}
CLEAN_AS(func_0207dd1c, VillagerCheck_TellsFoxPassword)

/* func_0207dd60: the villager with fleas (the state table's index 0x160) cleared (-1) when it
 * is this villager. */
void VillagerCheck_ClearFleasIfSelf(u8 *villager)
{
    if (VillagerCheck_HasFleas(villager)) {
        VillagerState_Table()->flea_villager = VILLAGER_STATE_NONE;
    }
}
CLEAN_AS(func_0207dd60, VillagerCheck_ClearFleasIfSelf)

/* func_0207dd84: whether the villager is the one with fleas, as the state table names it at
 * 0x160 (-1 names none). */
int VillagerCheck_HasFleas(u8 *villager)
{
    int named = VillagerState_Table()->flea_villager;
    int index = VillagerRoster_IndexOf(town(), TownVillager_NpcId(villager));
    return NpcId_IsValid(TownVillager_NpcId(villager)) && named != VILLAGER_STATE_NONE && index == named;
}
CLEAN_AS(func_0207dd84, VillagerCheck_HasFleas)
