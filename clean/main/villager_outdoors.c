/* Which of the town's villagers are out walking, at home or asleep (villager_outdoors.h). */
#include "villager_outdoors.h"

#include <string.h>

#include "clean.h"
#include "date_time.h"
#include "npc_id.h"
#include "villager_state.h"
#include "actor_table.h"
#include "insect_tables.h"
#include "item_traits.h"
#include "main_random.h"
#include "npc_lookup.h"
#include "player_id.h"
#include "player_record.h"
#include "player_records.h"
#include "town_villager.h"
#include "villager_checks.h"
#include "villager_memories.h"
#include "villager_move.h"
#include "villager_roster.h"
#include "villager_status.h"

#define VILLAGERS 8
#define VILLAGER_SIZE 0x7ec
/* Where the town's villagers are found from the object func_0204c7c0 gives. */
#define VILLAGER_OUTDOORS_VILLAGERS_FROM_0204C7C0 0x9284
/* The candidates VillagerOutdoors_DrawRandom looks at, at most. */
#define VILLAGER_OUTDOORS_CANDIDATES 6
/* The minutes after which the ones out are drawn again. */
#define VILLAGER_OUTDOORS_DRAW_MINUTES 60
/* The bit of the current player's record that keeps the villagers awake. */
#define VILLAGER_OUTDOORS_PLAYER_NO_SLEEP 1
/* The entry of the month's table VillagerOutdoors_MonthChance looks for. */
#define VILLAGER_OUTDOORS_MONTH_ENTRY 0x30

static_assert(offsetof(VillagerOutdoors, outside) == 0x08, "outside");
static_assert(offsetof(VillagerOutdoors, drawn_at) == 0x0c, "drawn at");
static_assert(sizeof(VillagerOutdoors) == 0x14, "size");

/* A month's table: `count` pairs of an entry and a running total. */
typedef struct VillagerOutdoorsMonth {
    const u8 *pairs;
    u8 count;
} VillagerOutdoorsMonth;

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

static const u8 *villager_at(const u8 *villagers, int index)
{
    return (const u8 *) ((uintptr_t) villagers + (uintptr_t) (index * VILLAGER_SIZE));
}

/* The state table's entry for villager `index`, by address as the ROM computes it. */
static VillagerState *state_at(u8 *states, int index)
{
    return (VillagerState *) ((uintptr_t) states + (uintptr_t) (index * (int) sizeof(VillagerState)));
}

static void set_place(VillagerState *entry, int place, int state)
{
    VillagerState_SetByte01(entry, place);
    VillagerState_SetState(entry, state);
}

static void mark_all_absent(VillagerStates *table)
{
    for (int i = 0; i < VILLAGERS; i++) {
        VillagerState_SetByte01(&table->entries[i], VILLAGER_PLACE_NONE);
    }
}

/* ---- Each hour */

/* func_02079cc4: every villager first marked as none; then, when the ones out are due to be
 * drawn again, a new draw (and with `keep_time` the time of it kept), else the last draw's
 * places again; then the sleepers. */
void VillagerOutdoors_Update(VillagerOutdoors *outdoors, u8 *villagers, int keep_time)
{
    DateTime now = {0};

    mark_all_absent(VillagerState_Table());
    DateTime_Now(&now);
    if (VillagerOutdoors_IsDue(outdoors, &now)) {
        VillagerOutdoors_Draw(outdoors, villagers);
        if (keep_time != 0) {
            MI_CpuCopy8(&now, &outdoors->drawn_at, sizeof(DateTime));
        }
    } else {
        VillagerOutdoors_Restore(outdoors, villagers);
    }
    VillagerOutdoors_PutToSleep(outdoors, villagers, &now);
}
CLEAN_AS(func_02079cc4, VillagerOutdoors_Update)

/* func_02079d38: the places from the list: a villager in the outside slots is out, another one
 * at home, and an index without a villager none. */
void VillagerOutdoors_Restore(VillagerOutdoors *outdoors, u8 *villagers)
{
    VillagerState *entry = VillagerState_Table()->entries;

    for (int i = 0; i < VILLAGERS; i++) {
        if (NpcId_IsValid(TownVillager_NpcId((u8 *) villager_at(villagers, i)))) {
            if (VillagerOutdoors_FindOutside(outdoors, i) != VILLAGER_OUTDOORS_NONE) {
                set_place(&entry[i], VILLAGER_PLACE_OUTSIDE, 1);
            } else {
                set_place(&entry[i], VILLAGER_PLACE_HOME, 0);
            }
        } else {
            set_place(&entry[i], VILLAGER_PLACE_NONE, 7);
        }
    }
}
CLEAN_AS(func_02079d38, VillagerOutdoors_Restore)

/* func_02079db8: a new draw. From the old order, the villager of index 0x16c and then random
 * ones are chosen to go out, up to the limit; the order is made again of the others (at home,
 * in their old order) followed by the chosen (out, in the order chosen, also in the outside
 * slots). */
void VillagerOutdoors_Draw(VillagerOutdoors *outdoors, u8 *villagers)
{
    VillagerStates *table = VillagerState_Table();
    int chosen_count = 0;
    int limit = NpcLookup_FourUnlessSlotTaken();
    int residents = VillagerRoster_CountFilled(villagers);
    int placed = 0;
    s8 list[VILLAGER_OUTDOORS_ORDER];
    s8 chosen[VILLAGER_OUTDOORS_ORDER];

    mark_all_absent(table);
    VillagerOutdoors_CopyList(outdoors, list, outdoors->order);
    VillagerOutdoors_ClearList(outdoors, outdoors->order);
    VillagerOutdoors_ClearList(outdoors, chosen);
    /* three quarters of the villagers, rounded down */
    if (limit > (residents * 3) >> 2) {
        limit = (residents * 3) >> 2;
    }
    VillagerOutdoors_ClearOutside(outdoors);
    VillagerOutdoors_TakeIndex16C(outdoors, chosen, &chosen_count, list, villagers);
    VillagerOutdoors_DrawRandom(outdoors, (u8 *) chosen, &chosen_count, list, villagers, limit);
    VillagerOutdoors_KeepHome(outdoors, list, &placed, (u8 *) table);
    VillagerOutdoors_SendOut(outdoors, chosen, &placed, (u8 *) table, chosen_count);
}
CLEAN_AS(func_02079db8, VillagerOutdoors_Draw)

/* func_02079e64: unless bit 1 of the current player's record is set, every villager whose
 * personality sleeps at `now` is asleep (state 0); an index without a villager is none. */
void VillagerOutdoors_PutToSleep(VillagerOutdoors *outdoors, u8 *villagers, const DateTime *now)
{
    (void) outdoors;
    int record = (int) (uintptr_t) PlayerRecords_Current();
    int awake = record != 0 && PlayerRecord_TestFlag((u8 *) (uintptr_t) record, VILLAGER_OUTDOORS_PLAYER_NO_SLEEP) != 0;
    VillagerState *entry = VillagerState_Table()->entries;

    for (int i = 0; i < VILLAGERS; i++) {
        NpcId *npc = TownVillager_NpcId((u8 *) villager_at(villagers, i));
        if (NpcId_IsValid(npc)) {
            if (!awake && NpcLookup_IsInNightWindow(NpcId_Personality(npc), now)) {
                set_place(&entry[i], VILLAGER_PLACE_ASLEEP, 0);
            }
        } else {
            set_place(&entry[i], VILLAGER_PLACE_NONE, 7);
        }
    }
}
CLEAN_AS(func_02079e64, VillagerOutdoors_PutToSleep)

/* ---- The draw */

/* func_02079ef0: the villager the state table names at 0x16c, when it is in `list`, leaves the
 * list and, with a valid NpcId, is chosen. */
void VillagerOutdoors_TakeIndex16C(VillagerOutdoors *outdoors, s8 *chosen, int *count, s8 *list, u8 *villagers)
{
    (void) outdoors;
    int wanted = VillagerState_GetIndex16C();

    if (!ActorTable_IsKindESlot((u32) wanted)) {
        return;
    }
    for (int i = 0; i < VILLAGERS; i++) {
        int villager = list[i];
        if (ActorTable_IsKindESlot((u32) villager) && villager == wanted) {
            if (NpcId_IsValid(TownVillager_NpcId((u8 *) villager_at(villagers, villager)))) {
                chosen[*count] = (s8) villager;
                (*count)++;
            }
            list[i] = VILLAGER_OUTDOORS_NONE;
        }
    }
}
CLEAN_AS(func_02079ef0, VillagerOutdoors_TakeIndex16C)

/* func_02079f60: the first `chosen_count` chosen villagers go out: each is put next in the order
 * (while there is room), marked out and put in the outside slot of its place in the choice. */
void VillagerOutdoors_SendOut(VillagerOutdoors *outdoors, s8 *chosen, int *count, u8 *states, int chosen_count)
{
    for (int i = 0; i < chosen_count; i++) {
        int villager = chosen[i];
        if (VillagerOutdoors_SetOrder(outdoors, *count, villager)) {
            (*count)++;
            set_place(state_at(states, villager), VILLAGER_PLACE_OUTSIDE, 1);
            VillagerOutdoors_SetOutside(outdoors, (unsigned int) i, (char) villager);
        }
    }
}
CLEAN_AS(func_02079f60, VillagerOutdoors_SendOut)

/* func_02079fc8: the villagers left in `list` are put next in the order (while there is room),
 * marked at home and taken off the list. */
void VillagerOutdoors_KeepHome(VillagerOutdoors *outdoors, s8 *list, int *count, u8 *states)
{
    for (int i = 0; i < VILLAGERS; i++) {
        int villager = list[i];
        if (ActorTable_IsKindESlot((u32) villager) && VillagerOutdoors_SetOrder(outdoors, *count, villager)) {
            (*count)++;
            set_place(state_at(states, villager), VILLAGER_PLACE_HOME, 0);
            list[i] = VILLAGER_OUTDOORS_NONE;
        }
    }
}
CLEAN_AS(func_02079fc8, VillagerOutdoors_KeepHome)

/* func_0207a02c: random villagers of `list` are chosen until `limit` are. The candidates are the
 * first six in the list that func_0207d6c4 accepts, leaving out the one the record at 0x3f90
 * names; each round one of those left is drawn, taken off the list and chosen.
 * QUIRK: the number of rounds is the number of candidates even when some are chosen already. */
void VillagerOutdoors_DrawRandom(VillagerOutdoors *outdoors, u8 *chosen, int *count, s8 *list, u8 *villagers, int limit)
{
    (void) outdoors;
    u8 candidates = 0;
    int left = 0;
    void *town = (void *) (uintptr_t) (u32) (ItemTraits_StateBlockAddress() + VILLAGER_OUTDOORS_VILLAGERS_FROM_0204C7C0);
    int excluded = VillagerMove_VillagerIndex(town);

    for (int i = 0; i < VILLAGERS; i++) {
        int villager = list[i];
        if (!ActorTable_IsKindESlot((u32) villager) || villager == excluded) {
            continue;
        }
        if (VillagerCheck_IsStayingResident((u8 *) villager_at(villagers, villager))) {
            candidates = (u8) (candidates | (1 << i));
            left++;
            if (left >= VILLAGER_OUTDOORS_CANDIDATES) {
                break;
            }
        }
    }
    while (left > 0 && *count < limit) {
        int pick = (int) MainRandom_Below(left);
        for (int j = 0; j < VILLAGERS; j++) {
            if ((candidates >> j) & 1) {
                if (pick == 0) {
                    chosen[*count] = (u8) list[j];
                    (*count)++;
                    list[j] = VILLAGER_OUTDOORS_NONE;
                    candidates = (u8) (candidates & ~(1 << j));
                    break;
                }
                pick--;
            }
        }
        left--;
    }
}
CLEAN_AS(func_0207a02c, VillagerOutdoors_DrawRandom)

static int is_all_zero(const DateTime *when)
{
    static const DateTime zero;
    return memcmp(when, &zero, sizeof zero) == 0;
}

/* func_0207a118: whether the ones out are due to be drawn again: never drawn (all eight bytes
 * zero), an invalid time, or at least 60 minutes between it and `now` either way, counting
 * whole minutes (the seconds are not looked at). */
int VillagerOutdoors_IsDue(VillagerOutdoors *outdoors, const DateTime *now)
{
    const DateTime *drawn = &outdoors->drawn_at;

    if (is_all_zero(drawn) || DateTime_IsInvalid(drawn) != 0) {
        return 1;
    }
    int minutes = 0;
    int order =
        DateTime_Compare(now, drawn, DATE_TIME_MINUTE | DATE_TIME_HOUR | DATE_TIME_DAY | DATE_TIME_MONTH | DATE_TIME_YEAR);
    if (order == -1) {
        minutes = DateTime_MinutesBetween(now, drawn);
    } else if (order == 1) {
        minutes = DateTime_MinutesBetween(drawn, now);
    }
    return minutes >= VILLAGER_OUTDOORS_DRAW_MINUTES;
}
CLEAN_AS(func_0207a118, VillagerOutdoors_IsDue)

/* ---- The list */

/* func_0207a180: the time of the draw forgotten, so that the next update draws again. */
void VillagerOutdoors_ClearTime(VillagerOutdoors *outdoors)
{
    memset(&outdoors->drawn_at, 0, sizeof(DateTime));
}
CLEAN_AS(func_0207a180, VillagerOutdoors_ClearTime)

/* func_0207a188: the order made of the villager indexes in turn, -1 for each without a valid
 * NpcId. */
void VillagerOutdoors_ListResidents(VillagerOutdoors *outdoors, u8 *villagers)
{
    for (int i = 0; i < VILLAGERS; i++) {
        if (NpcId_IsValid(TownVillager_NpcId((u8 *) villager_at(villagers, i)))) {
            outdoors->order[i] = (s8) i;
        } else {
            outdoors->order[i] = VILLAGER_OUTDOORS_NONE;
        }
    }
}
CLEAN_AS(func_0207a188, VillagerOutdoors_ListResidents)

/* func_0207a1c0 */
int VillagerOutdoors_OutsideSlot(VillagerOutdoors *outdoors, int villager)
{
    return VillagerOutdoors_FindOutside(outdoors, villager);
}
CLEAN_AS(func_0207a1c0, VillagerOutdoors_OutsideSlot)

/* func_0207a1c8: the villager taken out of the order and the outside slots. */
void VillagerOutdoors_Remove(VillagerOutdoors *outdoors, int villager)
{
    VillagerOutdoors_RemoveFromOrder(outdoors, villager);
    VillagerOutdoors_RemoveOutside(outdoors, villager);
}
CLEAN_AS(func_0207a1c8, VillagerOutdoors_Remove)

/* func_0207a1e4: the villager taken out of the outside slots, the ones after it moving up. */
void VillagerOutdoors_RemoveOutside(VillagerOutdoors *outdoors, int villager)
{
    int slot = VillagerOutdoors_FindOutside(outdoors, villager);

    if ((unsigned int) slot >= VILLAGER_OUTDOORS_OUTSIDE) {
        return;
    }
    for (; slot < VILLAGER_OUTDOORS_OUTSIDE - 1; slot++) {
        outdoors->outside[slot] = outdoors->outside[slot + 1];
    }
    outdoors->outside[VILLAGER_OUTDOORS_OUTSIDE - 1] = VILLAGER_OUTDOORS_NONE;
}
CLEAN_AS(func_0207a1e4, VillagerOutdoors_RemoveOutside)

/* func_0207a210: the outside slot of villager `villager` (0-7), or -1. */
int VillagerOutdoors_FindOutside(VillagerOutdoors *outdoors, int villager)
{
    if (!ActorTable_IsKindESlot((u32) villager)) {
        return VILLAGER_OUTDOORS_NONE;
    }
    for (int slot = 0; slot < VILLAGER_OUTDOORS_OUTSIDE; slot++) {
        if (outdoors->outside[slot] == villager) {
            return slot;
        }
    }
    return VILLAGER_OUTDOORS_NONE;
}
CLEAN_AS(func_0207a210, VillagerOutdoors_FindOutside)

/* func_0207a244: whether `slot` is 0-3; then it holds `villager`. */
int VillagerOutdoors_SetOutside(VillagerOutdoors *outdoors, unsigned int slot, char villager)
{
    if (slot >= VILLAGER_OUTDOORS_OUTSIDE) {
        return 0;
    }
    outdoors->outside[slot] = (s8) villager;
    return 1;
}
CLEAN_AS(func_0207a244, VillagerOutdoors_SetOutside)

/* func_0207a254 */
void VillagerOutdoors_ClearOutside(VillagerOutdoors *outdoors)
{
    MI_CpuFill8(outdoors->outside, 0xff, VILLAGER_OUTDOORS_OUTSIDE);
}
CLEAN_AS(func_0207a254, VillagerOutdoors_ClearOutside)

/* func_0207a264: villager `villager` (0-7) taken out of the order at its first place, the ones
 * after it moving up. */
void VillagerOutdoors_RemoveFromOrder(VillagerOutdoors *outdoors, int villager)
{
    if (!ActorTable_IsKindESlot((u32) villager)) {
        return;
    }
    for (int i = 0; i < VILLAGER_OUTDOORS_ORDER; i++) {
        if (outdoors->order[i] == villager) {
            for (; i < VILLAGER_OUTDOORS_ORDER - 1; i++) {
                outdoors->order[i] = outdoors->order[i + 1];
            }
            outdoors->order[VILLAGER_OUTDOORS_ORDER - 1] = VILLAGER_OUTDOORS_NONE;
            return;
        }
    }
}
CLEAN_AS(func_0207a264, VillagerOutdoors_RemoveFromOrder)

/* func_0207a2a4: villager `villager` (0-7) put in the first free place of the order, if any. */
void VillagerOutdoors_AddToOrder(VillagerOutdoors *outdoors, int villager)
{
    if (!ActorTable_IsKindESlot((u32) villager)) {
        return;
    }
    for (int i = 0; i < VILLAGER_OUTDOORS_ORDER; i++) {
        if (outdoors->order[i] == VILLAGER_OUTDOORS_NONE) {
            outdoors->order[i] = (s8) villager;
            return;
        }
    }
}
CLEAN_AS(func_0207a2a4, VillagerOutdoors_AddToOrder)

/* func_0207a2d8: whether `position` is 0-7; then that place of the order holds `villager`. */
int VillagerOutdoors_SetOrder(VillagerOutdoors *outdoors, int position, int villager)
{
    if (!ActorTable_IsKindESlot((u32) position)) {
        return 0;
    }
    outdoors->order[position] = (s8) villager;
    return 1;
}
CLEAN_AS(func_0207a2d8, VillagerOutdoors_SetOrder)

/* func_0207a2fc: eight places copied from `src` to `dst`. */
void VillagerOutdoors_CopyList(VillagerOutdoors *outdoors, s8 *dst, const s8 *src)
{
    (void) outdoors;
    MI_CpuCopy8(src, dst, VILLAGER_OUTDOORS_ORDER);
}
CLEAN_AS(func_0207a2fc, VillagerOutdoors_CopyList)

/* func_0207a308: eight places of `list` set to -1. */
void VillagerOutdoors_ClearList(VillagerOutdoors *outdoors, s8 *list)
{
    (void) outdoors;
    MI_CpuFill8(list, 0xff, VILLAGER_OUTDOORS_ORDER);
}
CLEAN_AS(func_0207a308, VillagerOutdoors_ClearList)

/* func_0207a318: the order and the outside slots empty, never drawn. */
void VillagerOutdoors_Init(VillagerOutdoors *outdoors)
{
    VillagerOutdoors_ClearList(outdoors, outdoors->order);
    VillagerOutdoors_ClearOutside(outdoors);
    memset(&outdoors->drawn_at, 0, sizeof(DateTime));
}
CLEAN_AS(func_0207a318, VillagerOutdoors_Init)

/* func_0207a334: the destructor: does nothing. */
void VillagerOutdoors_Destruct(VillagerOutdoors *outdoors)
{
    (void) outdoors;
}
CLEAN_AS(func_0207a334, VillagerOutdoors_Destruct)

/* func_0207a338: the constructor: never drawn. */
void VillagerOutdoors_Construct(VillagerOutdoors *outdoors)
{
    memset(&outdoors->drawn_at, 0, sizeof(DateTime));
}
CLEAN_AS(func_0207a338, VillagerOutdoors_Construct)

/* ---- A villager out for the player */

/* func_0207a340: the state table's index 0x160 is set to none, then, for a player whose name
 * is set, to a villager drawn from the ones that remember the player and are out walking: they
 * are drawn one by one in random order, and each is taken with this month's chance in 100
 * (VillagerOutdoors_MonthChance) until one is. */
void VillagerOutdoors_DrawIndex160(const u8 *villagers, const void *player)
{
    VillagerState_Table()->index_160 = VILLAGER_STATE_NONE;
    if (player == NULL || PlayerId_IsSet((DesignCreator *) player) == 0) {
        return;
    }
    int chance = VillagerOutdoors_MonthChance();

    u8 candidates = 0;
    int left = 0;
    for (int i = 0; i < VILLAGERS; i++) {
        const u8 *villager = villager_at(villagers, i);
        if (NpcId_IsValid(TownVillager_NpcId((u8 *) villager)) && VillagerMemory_Of((u8 *) villager, player) != 0 &&
            VillagerStatus_Get((u8 *) villager) == 0) {
            candidates = (u8) (candidates | (1 << i));
            left++;
        }
    }
    while (left > 0) {
        int pick = (int) MainRandom_Below(left);
        left--;
        for (int i = 0; i < VILLAGERS; i++) {
            if ((candidates >> i) & 1) {
                if (pick == 0) {
                    if ((int) MainRandom_Below(100) < chance) {
                        VillagerState_Table()->index_160 = (s8) i;
                        left = 0;
                    }
                    candidates = (u8) (candidates & ~(1 << i));
                    break;
                }
                pick--;
            }
        }
    }
}
CLEAN_AS(func_0207a340, VillagerOutdoors_DrawIndex160)

/* func_0207a404: the share of entry 0x30 in this month's table: its running total less the one
 * before it; 0 when the month has no table or no such entry. */
int VillagerOutdoors_MonthChance(void)
{
    DateTime now = {0};

    DateTime_Now(&now);
    const VillagerOutdoorsMonth *month = (const VillagerOutdoorsMonth *) InsectTables_MonthLists(now.month - 1);
    if (month == NULL) {
        return 0;
    }
    const u8 *pair = month->pairs;
    int before = 0;
    for (int i = 0; i < month->count; i++, pair += 2) {
        if (pair[0] == VILLAGER_OUTDOORS_MONTH_ENTRY) {
            return pair[1] - before;
        }
        before = pair[1];
    }
    return 0;
}
CLEAN_AS(func_0207a404, VillagerOutdoors_MonthChance)
