/* The errand each villager is given (villager_errands.h). */
#include "villager_errands.h"

#include <string.h>

#include "clean.h"
#include "item_code.h"
#include "session.h"
#include "villager_town.h"
#include "villager_errand.h"
#include "main_random.h"
#include "player_record.h"
#include "player_records.h"
#include "town_villager.h"
#include "villager_mode_record.h"
#include "villager_sickness_record.h"
#include "villager_object.h"
#include "villager_part.h"
#include "villager_part_block.h"
#include "villager_house_visit.h"
#include "villager_roster.h"
#include "villager_status.h"

/* The errand types a player's record holds itself (part 0x1e40), whose group 1 places are not
 * dealt. */
#define VILLAGER_ERRANDS_RECORD_TYPES 13

extern NetSession *data_020ccf94;                        /* the game's session */
extern u8 data_021d12b4[VILLAGER_ERRANDS_GROUP_1_COUNT]; /* which group 1 places are taken */
extern u8 data_021d1248[VILLAGER_TOWN_VILLAGERS];        /* which villagers have been dealt with */
extern const u8 data_020cd454[VILLAGER_ERRANDS_RECORD_TYPES];

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

static int has_villager(const u8 *villager)
{
    return NpcId_IsValid(TownVillager_NpcId((u8 *) villager));
}

static int same_npc(const NpcId *a, const NpcId *b)
{
    return a->town.number == b->town.number && memcmp(a->town.name, b->town.name, sizeof(a->town.name)) == 0 &&
           a->number == b->number;
}

/* func_0207b57c: VillagerErrands_Deal when VillagerErrands_IsDealNeeded. */
void VillagerErrands_DealIfNeeded(VillagerTown *town)
{
    if (VillagerErrands_IsDealNeeded(town)) {
        VillagerErrands_Deal(town);
    }
}
CLEAN_AS(func_0207b57c, VillagerErrands_DealIfNeeded)

/* func_0207b594: types dealt to the villagers, each group 1 type to one villager at most.
 * Taken first are the group 1 places of the 13 types of data_020cd454, and of each resident
 * villager (other than the sick one) that already has a group 1 type
 * (VillagerErrands_TypeOf with the current player). An empty place, a villager that is not resident
 * and the sick one are left out. A villager whose record's mode has a group 0
 * value in its byte 0x10 (below 5) gets that as its type. Then, while villagers and group 1
 * types are left, a random villager left gets a random type left. Nothing without a current
 * player.
 * REQUIRES: the places VillagerErrand_PlaceInGroupOfType gives are 0-16, as they are for the types of group 1. */
void VillagerErrands_Deal(VillagerTown *town)
{
    void *record = PlayerRecords_Current();
    int types_left = VILLAGER_ERRANDS_GROUP_1_COUNT;
    int villagers_left = VILLAGER_TOWN_VILLAGERS;
    if (record == NULL) {
        return;
    }
    int place = 0;
    int sick = VillagerSickness_VillagerIndex(town);
    MI_CpuFill8(data_021d12b4, 0, (u32) types_left);
    MI_CpuFill8(data_021d1248, 0, (u32) villagers_left);

    for (int i = 0; i < VILLAGER_ERRANDS_RECORD_TYPES; i++) {
        if (VillagerErrand_PlaceInGroupOfType(&place, data_020cd454[i])) {
            data_021d12b4[place] = 1;
            types_left--;
        }
    }
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        u8 *villager = town->villagers[i];
        if (!has_villager(villager) || VillagerStatus_Stay(villager) != 3 || i == sick) {
            data_021d1248[i] = 1;
            villagers_left--;
            continue;
        }
        int type = VillagerErrands_TypeOf(town, villager, record);
        if ((unsigned int) type >= VILLAGER_ERRANDS_NONE ||
            VillagerErrand_GroupOfType((u32) type) != VILLAGER_ERRANDS_GROUP_1 ||
            !VillagerErrand_PlaceInGroupOfType(&place, type)) {
            continue;
        }
        data_021d1248[i] = 1;
        villagers_left--;
        data_021d12b4[place] = 1;
        types_left--;
    }
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (data_021d1248[i] != 0) {
            continue;
        }
        const u8 *villager = town->villagers[i];
        const u8 *own =
            (const u8 *) (VillagerObject_RecordMode((VillagerRecord *) VillagerStatus_ModeRecord((u8 *) villager)));
        if (!VillagerModeRecord_IsKind((VillagerModeRecord *) (void *) own) ||
            VillagerModeRecord_Group((VillagerModeRecord *) (void *) own) != 0) {
            continue;
        }
        u8 *object = VillagerState_Errand(VillagerStatus_StateEntry((u8 *) villager));
        u16 item = ITEM_CODE_NONE;
        VillagerErrand_Set((VillagerErrand *) (void *) object, VillagerModeRecord_Mode((VillagerModeRecord *) (void *) own),
                           &item, 0);
        data_021d1248[i] = 1;
        villagers_left--;
    }
    while (villagers_left > 0 && types_left > 0) {
        int nth_villager = (int) MainRandom_Below(villagers_left);
        for (int j = 0; j < VILLAGER_TOWN_VILLAGERS; j++) {
            if (data_021d1248[j] != 0) {
                continue;
            }
            if (nth_villager != 0) {
                nth_villager--;
                continue;
            }
            u8 *object = VillagerState_Errand(VillagerStatus_StateEntry(town->villagers[j]));
            int nth_type = (int) MainRandom_Below(types_left);
            for (int k = 0; k < VILLAGER_ERRANDS_GROUP_1_COUNT; k++) {
                if (data_021d12b4[k] != 0) {
                    continue;
                }
                if (nth_type == 0) {
                    u16 item = ITEM_CODE_NONE;
                    VillagerErrand_Set((VillagerErrand *) (void *) object, (u8) (k + VILLAGER_ERRANDS_GROUP_1_FIRST), &item,
                                       0);
                    data_021d12b4[k] = 1;
                    types_left--;
                    break;
                }
                nth_type--;
            }
            data_021d1248[j] = 1;
            villagers_left--;
            break;
        }
    }
}
CLEAN_AS(func_0207b594, VillagerErrands_Deal)

/* func_0207b764: every entry of the state table back to no type. */
void VillagerErrands_ClearAll(void)
{
    VillagerState *entry = VillagerState_Table()->entries;
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        VillagerErrand_Clear((VillagerErrand *) (void *) VillagerState_Errand(entry));
        entry++;
    }
}
CLEAN_AS(func_0207b764, VillagerErrands_ClearAll)

/* func_0207b78c: whether the types need dealing: never while this system is linked with
 * others; else when the villagers with no type outnumber half of the villagers less those with
 * a type outside group 1. */
int VillagerErrands_IsDealNeeded(VillagerTown *town)
{
    if (Session_IsLinked(data_020ccf94)) {
        return 0;
    }
    int villagers = VillagerRoster_Count(town);
    int without = 0;
    int other_group = 0;
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        u8 *villager = town->villagers[i];
        if (!has_villager(villager)) {
            continue;
        }
        int type = VillagerErrands_TypeOf(town, villager, NULL);
        if (type == VILLAGER_ERRANDS_NONE) {
            without++;
        } else if (VillagerErrand_GroupOfType((u32) type) != VILLAGER_ERRANDS_GROUP_1) {
            other_group++;
        }
    }
    if (villagers < other_group) {
        return 0;
    }
    return (villagers - other_group) / 2 < without;
}
CLEAN_AS(func_0207b78c, VillagerErrands_IsDealNeeded)

/* func_0207b810: the villager's type: VillagerErrands_KnownType when that finds one, else the type
 * of its state entry's errand when it holds one; 22 for none, also without a state entry or
 * a player's record (the current player's when `record` is NULL). */
int VillagerErrands_TypeOf(VillagerTown *town, u8 *villager, void *record)
{
    VillagerState *entry = VillagerStatus_StateEntry(villager);
    int type = VILLAGER_ERRANDS_NONE;
    if (record == NULL) {
        record = PlayerRecords_Current();
    }
    if (entry != NULL && record != NULL) {
        unsigned int known = (unsigned int) VillagerErrands_KnownType(town, villager, record);
        if (known < VILLAGER_ERRANDS_NONE) {
            type = (int) known;
        } else if (VillagerErrand_IsInUse((VillagerErrand *) (void *) VillagerState_Errand(entry))) {
            type = VillagerErrand_Type((VillagerErrand *) (void *) VillagerState_Errand(entry));
        }
    }
    return type;
}
CLEAN_AS(func_0207b810, VillagerErrands_TypeOf)

/* func_0207b86c: the type of the errand something holds for the villager, looked for in turn
 * in: the two blocks of the player's record part (when their first NpcId is the villager's),
 * the sickness record (when it names the villager), the errand at 0xb4 of the part
 * (func_0209aebc) and the errand of the villager's own record; 22 for none, or without a
 * player's record (the current player's when `record` is NULL). */
int VillagerErrands_KnownType(VillagerTown *town, u8 *villager, void *record)
{
    const NpcId *npc = TownVillager_NpcId(villager);
    if (record == NULL) {
        record = PlayerRecords_Current();
    }
    if (record == NULL) {
        return VILLAGER_ERRANDS_NONE;
    }
    u8 *part = PlayerRecord_VillagerPart(record);
    u8 *blocks[2];
    blocks[0] = (u8 *) (VillagerPart_Block((VillagerPart *) (void *) part, 0));
    blocks[1] = (u8 *) (VillagerPart_Block((VillagerPart *) (void *) part, 1));
    part += 0xa4;

    for (int i = 0; i < 2; i++) {
        if (VillagerErrand_IsInUse(
                (VillagerErrand *) (void *) VillagerPartBlock_Errand((VillagerPartBlock *) (void *) blocks[i])) &&
            same_npc(VillagerPartBlock_Npc((VillagerPartBlock *) (void *) blocks[i], 0), npc)) {
            return VillagerErrand_Type(
                (VillagerErrand *) (void *) VillagerPartBlock_Errand((VillagerPartBlock *) (void *) blocks[i]));
        }
    }
    if (VillagerErrand_IsInUse((VillagerErrand *) (void *) VillagerSicknessRecord_Errand(&town->sickness)) &&
        same_npc(VillagerSicknessRecord_Npc(&town->sickness), npc)) {
        return VillagerErrand_Type((VillagerErrand *) (void *) VillagerSicknessRecord_Errand(&town->sickness));
    }
    if (VillagerHouseVisit_IsFrom((VillagerHouseVisit *) (void *) part, npc)) {
        return VillagerErrand_Type((VillagerErrand *) (void *) (part + 0x10));
    }
    if (VillagerErrand_IsInUse((VillagerErrand *) (void *) (VillagerObject_Errand(
            VillagerObject_OfRecord((VillagerRecord *) VillagerStatus_ModeRecord(villager)))))) {
        return VillagerErrand_Type((VillagerErrand *) (void *) (VillagerObject_Errand(
            VillagerObject_OfRecord((VillagerRecord *) VillagerStatus_ModeRecord(villager)))));
    }
    return VILLAGER_ERRANDS_NONE;
}
CLEAN_AS(func_0207b86c, VillagerErrands_KnownType)
