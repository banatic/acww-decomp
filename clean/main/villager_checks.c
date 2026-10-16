/* Tests of one of the town's villagers (villager_checks.h). */
#include "villager_checks.h"

#include <string.h>

#include "clean.h"
#include "npc_id.h"
#include "player_records.h"
#include "villager_move.h"
#include "villager_roster.h"
#include "villager_state.h"
#include "villager_town.h"

/* What func_0207f150 gives a villager that lives in the town as usual. */
#define VILLAGER_CHECK_RESIDENT 3

extern u8 data_021e5a2c[]; /* the town's villagers (VillagerTown) */
extern u8 data_021dc7bc[]; /* the four players' records */

static VillagerTown *town(void)
{
    return (VillagerTown *) (void *) data_021e5a2c;
}

extern NpcId *func_0208150c(const void *villager); /* the villager's NpcId, at 0x7a0 */
extern int func_0207f150(const void *villager);    /* 0-3, from three tests of the villager */
extern NpcId *func_0209a774(VillagerMove *move);   /* the plan's NpcId */
extern u8 *func_02099870(u8 *record);              /* the player's id (town and name), at 0x247e */
extern int func_020951bc(const u8 *player);        /* whether the player id is set */
extern u8 *func_02099640(u8 *record);              /* the record's part at 0x1e40 */
/* Whether the part (of a player's record) holds an object for the villager. */
extern int func_0207ef54(const void *villager, u8 *part);

static int same_npc(const NpcId *a, const NpcId *b)
{
    return a->head.id == b->head.id && memcmp(a->head.data, b->head.data, sizeof(a->head.data)) == 0 && a->number == b->number;
}

/* func_0207d6c4: whether the villager lives in the town as usual and is not the one the town's
 * plan to move away names (the personality is not compared). */
int VillagerCheck_IsStayingResident(u8 *villager)
{
    NpcId *npc = func_0208150c(villager);
    if (!NpcId_IsValid(npc) || func_0207f150(villager) != VILLAGER_CHECK_RESIDENT) {
        return 0;
    }
    NpcId *moving = func_0209a774(VillagerMove_Record(town()));
    return !same_npc(npc, moving);
}
CLEAN_AS(func_0207d6c4, VillagerCheck_IsStayingResident)

/* func_0207dca8: 1 unless the record of one of the town's four players (one whose id is set)
 * holds an object for the villager. */
int VillagerCheck_NoPlayerHolds(u8 *villager)
{
    for (int i = 0; i < PLAYER_RECORDS_TOWN; i++) {
        u8 *record = PlayerRecords_TownRecord(data_021dc7bc, i);
        if (func_020951bc(func_02099870(record)) == 0) {
            continue;
        }
        if (func_0207ef54(villager, func_02099640(record)) != 0) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_0207dca8, VillagerCheck_NoPlayerHolds)

/* func_0207dd1c: whether the villager is the one the state table names at 0x161. */
int VillagerCheck_IsIndex161(u8 *villager)
{
    int named = (s8) VillagerState_Table()->byte_161;
    int index = VillagerRoster_IndexOf(town(), func_0208150c(villager));
    return NpcId_IsValid(func_0208150c(villager)) && index == named;
}
CLEAN_AS(func_0207dd1c, VillagerCheck_IsIndex161)

/* func_0207dd60: the state table's index 0x160 cleared (-1) when it names the villager. */
void VillagerCheck_ClearIndex160IfSelf(u8 *villager)
{
    if (VillagerCheck_IsIndex160(villager)) {
        VillagerState_Table()->index_160 = VILLAGER_STATE_NONE;
    }
}
CLEAN_AS(func_0207dd60, VillagerCheck_ClearIndex160IfSelf)

/* func_0207dd84: whether the villager is the one the state table names at 0x160 (-1 names
 * none). */
int VillagerCheck_IsIndex160(u8 *villager)
{
    int named = VillagerState_Table()->index_160;
    int index = VillagerRoster_IndexOf(town(), func_0208150c(villager));
    return NpcId_IsValid(func_0208150c(villager)) && named != VILLAGER_STATE_NONE && index == named;
}
CLEAN_AS(func_0207dd84, VillagerCheck_IsIndex160)
