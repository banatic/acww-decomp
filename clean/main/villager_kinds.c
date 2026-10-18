/* The kind each villager is given (villager_kinds.h). */
#include "villager_kinds.h"

#include <string.h>

#include "clean.h"
#include "session.h"
#include "villager_town.h"
#include "item_object.h"
#include "main_random.h"
#include "player_record.h"
#include "player_records.h"
#include "town_villager.h"
#include "villager_mode_record.h"
#include "villager_move_record.h"
#include "villager_object.h"
#include "villager_part.h"
#include "villager_part_block.h"
#include "villager_part_handover.h"
#include "villager_roster.h"
#include "villager_status.h"

/* The types of object a player's record holds itself (part 0x1e40), whose group 1 places are
 * not dealt. */
#define VILLAGER_KIND_RECORD_TYPES 13
/* The item of the object dealt: none. */
#define VILLAGER_KIND_NO_ITEM 0xfff1

extern NetSession *data_020ccf94;                     /* the game's session */
extern u8 data_021d12b4[VILLAGER_KIND_GROUP_1_COUNT]; /* which group 1 places are taken */
extern u8 data_021d1248[VILLAGER_TOWN_VILLAGERS];     /* which villagers have been dealt with */
extern const u8 data_020cd454[VILLAGER_KIND_RECORD_TYPES];

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

static int has_villager(const u8 *villager)
{
    return NpcId_IsValid(TownVillager_NpcId((u8 *) villager));
}

static int same_npc(const NpcId *a, const NpcId *b)
{
    return a->head.id == b->head.id && memcmp(a->head.data, b->head.data, sizeof(a->head.data)) == 0 && a->number == b->number;
}

/* func_0207b57c: VillagerKind_Deal when VillagerKind_IsDealNeeded. */
void VillagerKind_DealIfNeeded(VillagerTown *town)
{
    if (VillagerKind_IsDealNeeded(town)) {
        VillagerKind_Deal(town);
    }
}
CLEAN_AS(func_0207b57c, VillagerKind_DealIfNeeded)

/* func_0207b594: types dealt to the villagers, each group 1 type to one villager at most.
 * Taken first are the group 1 places of the 13 types of data_020cd454, and of each resident
 * villager (other than the one planning to move away) that already has a group 1 type
 * (VillagerKind_Of with the current player). An empty place, a villager that is not resident
 * and the one planning to move are left out. A villager whose record's object has a group 0
 * value in its byte 0x10 (below 5) gets that as its type. Then, while villagers and group 1
 * types are left, a random villager left gets a random type left. Nothing without a current
 * player.
 * REQUIRES: the places func_0209bcd4 gives are 0-16, as they are for the types of group 1. */
void VillagerKind_Deal(VillagerTown *town)
{
    void *record = PlayerRecords_Current();
    int types_left = VILLAGER_KIND_GROUP_1_COUNT;
    int villagers_left = VILLAGER_TOWN_VILLAGERS;
    if (record == NULL) {
        return;
    }
    int place = 0;
    int moving = VillagerMove_VillagerIndex(town);
    MI_CpuFill8(data_021d12b4, 0, (u32) types_left);
    MI_CpuFill8(data_021d1248, 0, (u32) villagers_left);

    for (int i = 0; i < VILLAGER_KIND_RECORD_TYPES; i++) {
        if (ItemObject_PlaceInGroupOfType(&place, data_020cd454[i])) {
            data_021d12b4[place] = 1;
            types_left--;
        }
    }
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        u8 *villager = town->villagers[i];
        if (!has_villager(villager) || VillagerStatus_Stay(villager) != 3 || i == moving) {
            data_021d1248[i] = 1;
            villagers_left--;
            continue;
        }
        int type = VillagerKind_Of(town, villager, record);
        if ((unsigned int) type >= VILLAGER_KIND_NONE || ItemObject_GroupOfType((u32) type) != VILLAGER_KIND_GROUP_1 ||
            !ItemObject_PlaceInGroupOfType(&place, type)) {
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
        u8 *object = VillagerState_Object(VillagerStatus_StateEntry((u8 *) villager));
        u16 item = VILLAGER_KIND_NO_ITEM;
        ItemObject_Set((ItemObject *) (void *) object, VillagerModeRecord_Mode((VillagerModeRecord *) (void *) own), &item, 0);
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
            u8 *object = VillagerState_Object(VillagerStatus_StateEntry(town->villagers[j]));
            int nth_type = (int) MainRandom_Below(types_left);
            for (int k = 0; k < VILLAGER_KIND_GROUP_1_COUNT; k++) {
                if (data_021d12b4[k] != 0) {
                    continue;
                }
                if (nth_type == 0) {
                    u16 item = VILLAGER_KIND_NO_ITEM;
                    ItemObject_Set((ItemObject *) (void *) object, (u8) (k + VILLAGER_KIND_GROUP_1_FIRST), &item, 0);
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
CLEAN_AS(func_0207b594, VillagerKind_Deal)

/* func_0207b764: every entry of the state table back to no type. */
void VillagerKind_ClearAll(void)
{
    VillagerState *entry = VillagerState_Table()->entries;
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        ItemObject_Clear((ItemObject *) (void *) VillagerState_Object(entry));
        entry++;
    }
}
CLEAN_AS(func_0207b764, VillagerKind_ClearAll)

/* func_0207b78c: whether the types need dealing: never while this system is linked with
 * others; else when the villagers with no type outnumber half of the villagers less those with
 * a type outside group 1. */
int VillagerKind_IsDealNeeded(VillagerTown *town)
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
        int type = VillagerKind_Of(town, villager, NULL);
        if (type == VILLAGER_KIND_NONE) {
            without++;
        } else if (ItemObject_GroupOfType((u32) type) != VILLAGER_KIND_GROUP_1) {
            other_group++;
        }
    }
    if (villagers < other_group) {
        return 0;
    }
    return (villagers - other_group) / 2 < without;
}
CLEAN_AS(func_0207b78c, VillagerKind_IsDealNeeded)

/* func_0207b810: the villager's type: VillagerKind_Known when that finds one, else the type
 * of its state entry's object when it holds one; 22 for none, also without a state entry or
 * a player's record (the current player's when `record` is NULL). */
int VillagerKind_Of(VillagerTown *town, u8 *villager, void *record)
{
    VillagerState *entry = VillagerStatus_StateEntry(villager);
    int type = VILLAGER_KIND_NONE;
    if (record == NULL) {
        record = PlayerRecords_Current();
    }
    if (entry != NULL && record != NULL) {
        unsigned int known = (unsigned int) VillagerKind_Known(town, villager, record);
        if (known < VILLAGER_KIND_NONE) {
            type = (int) known;
        } else if (ItemObject_IsInUse((ItemObject *) (void *) VillagerState_Object(entry))) {
            type = ItemObject_Type((ItemObject *) (void *) VillagerState_Object(entry));
        }
    }
    return type;
}
CLEAN_AS(func_0207b810, VillagerKind_Of)

/* func_0207b86c: the type of the object something holds for the villager, looked for in turn
 * in: the two blocks of the player's record part (when their first NpcId is the villager's),
 * the plan to move away (when it names the villager), the object at 0xb4 of the part
 * (func_0209aebc) and the object of the villager's own record; 22 for none, or without a
 * player's record (the current player's when `record` is NULL). */
int VillagerKind_Known(VillagerTown *town, u8 *villager, void *record)
{
    const NpcId *npc = TownVillager_NpcId(villager);
    if (record == NULL) {
        record = PlayerRecords_Current();
    }
    if (record == NULL) {
        return VILLAGER_KIND_NONE;
    }
    u8 *part = PlayerRecord_VillagerPart(record);
    u8 *blocks[2];
    blocks[0] = (u8 *) (VillagerPart_Block((VillagerPart *) (void *) part, 0));
    blocks[1] = (u8 *) (VillagerPart_Block((VillagerPart *) (void *) part, 1));
    part += 0xa4;

    for (int i = 0; i < 2; i++) {
        if (ItemObject_IsInUse((ItemObject *) (void *) VillagerPartBlock_Object((VillagerPartBlock *) (void *) blocks[i])) &&
            same_npc(VillagerPartBlock_Npc((VillagerPartBlock *) (void *) blocks[i], 0), npc)) {
            return ItemObject_Type((ItemObject *) (void *) VillagerPartBlock_Object((VillagerPartBlock *) (void *) blocks[i]));
        }
    }
    if (ItemObject_IsInUse((ItemObject *) (void *) VillagerMoveRecord_Object(&town->move)) &&
        same_npc(VillagerMoveRecord_Npc(&town->move), npc)) {
        return ItemObject_Type((ItemObject *) (void *) VillagerMoveRecord_Object(&town->move));
    }
    if (VillagerPartHandover_IsFrom((VillagerPartHandover *) (void *) part, npc)) {
        return ItemObject_Type((ItemObject *) (void *) (part + 0x10));
    }
    if (ItemObject_IsInUse((ItemObject *) (void *) (VillagerObject_Base(
            VillagerObject_OfRecord((VillagerRecord *) VillagerStatus_ModeRecord(villager)))))) {
        return ItemObject_Type((ItemObject *) (void *) (VillagerObject_Base(
            VillagerObject_OfRecord((VillagerRecord *) VillagerStatus_ModeRecord(villager)))));
    }
    return VILLAGER_KIND_NONE;
}
CLEAN_AS(func_0207b86c, VillagerKind_Known)
