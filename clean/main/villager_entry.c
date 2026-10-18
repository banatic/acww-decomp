/* One of the town's villagers (villager_entry.h). */
#include "villager_entry.h"

#include "clean.h"
#include "npc_id.h"
#include "villager_roster.h"
#include "villager_state.h"
#include "date_time.h"
#include "item_code.h"
#include "main_random.h"
#include "npc_lookup.h"
#include "player_id.h"
#include "player_record.h"
#include "player_records.h"
#include "town_villager.h"
#include "villager_house_items.h"
#include "villager_memories.h"
#include "villager_memory_bits.h"
#include "villager_memory_entry.h"
#include "villager_status.h"

#define VILLAGER_ENTRY_ITEM_CODES 0x78c
#define VILLAGER_ENTRY_ITEM_MARKS 0x7d0
/* VillagerEntry_MarkItems marks three to five items, fewer when it has fewer. */
#define VILLAGER_ENTRY_MARK_LEAST 3
#define VILLAGER_ENTRY_MARK_MOST 5
/* The bit of a player's record flags (func_02099020) under which the villagers leave the player
 * be. */
#define VILLAGER_ENTRY_RECORD_FLAG 1
/* The draws that scale how fond the villager is into byte 0x1e. */
#define VILLAGER_ENTRY_RAISE_DRAW 3
#define VILLAGER_ENTRY_SET_DRAW 10
/* What a player's town gives in func_02094ffc for a town other than this one. */
#define VILLAGER_ENTRY_OTHER_TOWN 1

extern const NpcIdHead data_021dc7aa; /* this town (number and name) */

static int has_villager(const u8 *villager)
{
    return NpcId_IsValid(TownVillager_NpcId((u8 *) villager));
}

static u16 *item_codes(u8 *villager)
{
    return (u16 *) (void *) (villager + VILLAGER_ENTRY_ITEM_CODES);
}

static u16 *item_marks(u8 *villager)
{
    return (u16 *) (void *) (villager + VILLAGER_ENTRY_ITEM_MARKS);
}

/* How fond of a player the villager is, as a factor: 1 below 0, 2 from 0. */
static int fondness_factor(const s8 *memory)
{
    return (VillagerMemoryEntry_Fondness((VillagerMemory *) (void *) memory) + 0x100) >> 7;
}

/* ---- Byte 0x1e of its state entry */

/* func_0207d0f0: `amount` added to byte 0x1e, kept within 0-32. */
void VillagerEntry_AddByte1E(u8 *villager, int amount)
{
    if (!has_villager(villager)) {
        return;
    }
    VillagerState *state = VillagerStatus_StateEntry(villager);
    int value = amount + state->byte_1e;
    if (value < 0) {
        value = 0;
    } else if (value > VILLAGER_ENTRY_BYTE_1E_MAX) {
        value = VILLAGER_ENTRY_BYTE_1E_MAX;
    }
    state->byte_1e = (u8) value;
}
CLEAN_AS(func_0207d0f0, VillagerEntry_AddByte1E)

/* func_0207d128: byte 0x1e doubled (VillagerState_DoubleByte1E). */
void VillagerEntry_DoubleByte1E(u8 *villager)
{
    if (has_villager(villager)) {
        VillagerState_DoubleByte1E(VillagerStatus_StateEntry(villager));
    }
}
CLEAN_AS(func_0207d128, VillagerEntry_DoubleByte1E)

/* func_0207d148: byte 0x1e halved. */
void VillagerEntry_HalveByte1E(u8 *villager)
{
    if (has_villager(villager)) {
        VillagerState *state = VillagerStatus_StateEntry(villager);
        state->byte_1e = (u8) (state->byte_1e >> 1);
    }
}
CLEAN_AS(func_0207d148, VillagerEntry_HalveByte1E)

/* func_0207d16c: byte 0x1e cleared. */
void VillagerEntry_ClearByte1E(u8 *villager)
{
    if (has_villager(villager)) {
        VillagerStatus_StateEntry(villager)->byte_1e = 0;
    }
}
CLEAN_AS(func_0207d16c, VillagerEntry_ClearByte1E)

/* The player's record, the current player's for NULL, when it can be used here: it exists, its
 * player id is set and its flag 1 is clear; else NULL. */
static void *usable_record(void *record)
{
    if (record == NULL) {
        record = PlayerRecords_Current();
    }
    if (record == NULL || PlayerId_IsSet(PlayerRecord_Player(record)) == 0 ||
        PlayerRecord_TestFlag(record, VILLAGER_ENTRY_RECORD_FLAG) != 0) {
        return NULL;
    }
    return record;
}

/* func_0207d18c: whether byte 0x1e is full (32) and byte 0x18 of the entry 0 or 1, for a usable
 * player record (`record`, else the current player's). */
int VillagerEntry_IsByte1EFull(u8 *villager, void *record)
{
    int full = 0;
    if (usable_record(record) != NULL && has_villager(villager) &&
        VillagerStatus_StateEntry(villager)->byte_1e == VILLAGER_ENTRY_BYTE_1E_MAX) {
        full = 1;
    }
    return full && VillagerEntry_IsByte18Low(villager) != 0;
}
CLEAN_AS(func_0207d18c, VillagerEntry_IsByte1EFull)

/* func_0207d1f8: byte 0x1e raised by a draw of 0-2 times how fond the villager is of the
 * player (a factor of 1 or 2), when the player's record is usable, byte 0x18 is 0 or 1 and the
 * villager knows the player; else by nothing (kept within 0-32 all the same). */
void VillagerEntry_RaiseByte1E(u8 *villager, void *record)
{
    if (!has_villager(villager)) {
        return;
    }
    int amount = 0;
    record = usable_record(record);
    if (record != NULL && VillagerEntry_IsByte18Low(villager)) {
        const s8 *memory = (const s8 *) VillagerMemory_Of(villager, PlayerRecord_Player(record));
        if (memory != NULL) {
            int factor = fondness_factor(memory);
            amount = (int) MainRandom_Below(VILLAGER_ENTRY_RAISE_DRAW) * factor;
        }
    }
    VillagerEntry_AddByte1E(villager, amount);
}
CLEAN_AS(func_0207d1f8, VillagerEntry_RaiseByte1E)

/* func_0207d278: whether byte 0x18 of the villager's state entry is 0 or 1. */
int VillagerEntry_IsByte18Low(u8 *villager)
{
    if (!has_villager(villager)) {
        return 0;
    }
    VillagerState *state = VillagerStatus_StateEntry(villager);
    if (state == NULL) {
        return 0;
    }
    return VillagerState_GetByte18(state) == 0 || VillagerState_GetByte18(state) == 1;
}
CLEAN_AS(func_0207d278, VillagerEntry_IsByte18Low)

/* func_0207d2b4: byte 0x1e cleared, then, when the player's record is usable and the villager
 * knows the player, set to how fond the villager is (a factor of 1 or 2) times a draw of 1-10,
 * within 0-32. */
void VillagerEntry_SetByte1E(u8 *villager, void *record)
{
    if (!has_villager(villager)) {
        return;
    }
    VillagerState *state = VillagerStatus_StateEntry(villager);
    state->byte_1e = 0;
    record = usable_record(record);
    if (record == NULL) {
        return;
    }
    const s8 *memory = (const s8 *) VillagerMemory_Of(villager, PlayerRecord_Player(record));
    if (memory == NULL) {
        return;
    }
    int factor = fondness_factor(memory);
    int value = factor * ((int) MainRandom_Below(VILLAGER_ENTRY_SET_DRAW) + 1);
    if (value < 0) {
        value = 0;
    } else if (value > VILLAGER_ENTRY_BYTE_1E_MAX) {
        value = VILLAGER_ENTRY_BYTE_1E_MAX;
    }
    state->byte_1e = (u8) value;
}
CLEAN_AS(func_0207d2b4, VillagerEntry_SetByte1E)

/* ---- Players */

/* func_0207d4bc: for a player of another town (`record`, else the current player's) that the
 * villager knows, the villager put on the player's record at 0x245c (func_02099d08) with how
 * fond it is of the player and this town; its result, else 0. */
int VillagerEntry_NoteVisitor(u8 *villager, void *record)
{
    if (!has_villager(villager)) {
        return 0;
    }
    if (record == NULL) {
        record = PlayerRecords_Current();
    }
    if (record == NULL) {
        return 0;
    }
    u8 *player = (u8 *) PlayerRecord_Player(record);
    if (PlayerId_IsSet((DesignCreator *) (void *) player) == 0 ||
        PlayerId_WhichTown((DesignCreator *) (void *) player) != VILLAGER_ENTRY_OTHER_TOWN) {
        return 0;
    }
    const s8 *memory = (const s8 *) VillagerMemory_Of(villager, (const DesignCreator *) (void *) player);
    if (memory == NULL) {
        return 0;
    }
    u8 *part = (u8 *) PlayerRecord_Villager(record);
    const NpcId *npc = TownVillager_NpcId(villager);
    return PlayerRecordVillager_Note((PlayerRecordVillager *) (void *) part, npc,
                                     VillagerMemoryEntry_Fondness((VillagerMemory *) (void *) memory), &data_021dc7aa);
}
CLEAN_AS(func_0207d4bc, VillagerEntry_NoteVisitor)

/* func_0207d540: bit 14 of the flags of the villager's memory of `player` set, when it knows
 * the player. */
void VillagerEntry_FlagMemory(u8 *villager, const void *player)
{
    if (!has_villager(villager) || PlayerId_IsSet((DesignCreator *) player) == 0) {
        return;
    }
    s8 *memory = (s8 *) VillagerMemory_Of(villager, player);
    if (memory != NULL) {
        VillagerMemoryBits_SetBit14((VillagerMemory *) (void *) memory);
    }
}
CLEAN_AS(func_0207d540, VillagerEntry_FlagMemory)

/* func_0207d5bc: bit 6 of the flags of all eight memories cleared. */
void VillagerEntry_ClearMemoryFlag6(u8 *villager)
{
    for (int i = 0; i < VILLAGER_ENTRY_MEMORIES; i++) {
        VillagerMemoryEntry_ClearBit6((VillagerMemory *) (void *) (villager + i * VILLAGER_ENTRY_MEMORY_SIZE));
    }
}
CLEAN_AS(func_0207d5bc, VillagerEntry_ClearMemoryFlag6)

/* func_0207d578: whether `when` (the clock's time for NULL) falls in the hours the villager's
 * personality sleeps; 0 without a villager. */
int VillagerEntry_IsSleepTime(u8 *villager, const DateTime *when)
{
    if (!has_villager(villager)) {
        return 0;
    }
    DateTime now = {0};
    if (when == NULL) {
        DateTime_Now(&now);
        when = &now;
    }
    return NpcLookup_IsInNightWindow(NpcId_Personality(TownVillager_NpcId(villager)), when);
}
CLEAN_AS(func_0207d578, VillagerEntry_IsSleepTime)

/* ---- Its items */

/* func_0207d5dc: item `item` (0-9) unmarked. */
void VillagerEntry_UnmarkItem(u8 *villager, int item)
{
    if (VillagerHouseItems_IsSlot(villager, (u32) item)) {
        *item_marks(villager) &= (u16) ~(1u << item);
    }
}
CLEAN_AS(func_0207d5dc, VillagerEntry_UnmarkItem)

/* func_0207d608: whether item `item` (0-9) is marked. */
int VillagerEntry_IsItemMarked(u8 *villager, int item)
{
    return VillagerHouseItems_IsSlot(villager, (u32) item) && ((*item_marks(villager) >> item) & 1);
}
CLEAN_AS(func_0207d608, VillagerEntry_IsItemMarked)

/* func_0207d634: the marks cleared, then of the items of kinds 3 and 4 (func_0204bcdc), all of
 * them up to three; of four or more, three to five (a draw), picked at random. */
void VillagerEntry_MarkItems(u8 *villager)
{
    u16 *items = item_codes(villager);
    u16 *marks = item_marks(villager);
    u16 candidates = 0;
    int count = 0;

    *marks = 0;
    for (int i = 0; i < VILLAGER_ENTRY_ITEMS; i++) {
        if (ItemCode_HasVariant(&items[i])) {
            candidates |= (u16) (1u << i);
            count++;
        }
    }

    int to_mark = count > VILLAGER_ENTRY_MARK_MOST ? VILLAGER_ENTRY_MARK_MOST : count;
    if (to_mark > VILLAGER_ENTRY_MARK_LEAST) {
        to_mark = (int) MainRandom_Below(to_mark - (VILLAGER_ENTRY_MARK_LEAST - 1)) + VILLAGER_ENTRY_MARK_LEAST;
    }
    if (count <= 0) {
        return;
    }
    for (; to_mark > 0; to_mark--) {
        int item = VillagerRoster_PickBit(candidates, count, VILLAGER_ENTRY_ITEMS);
        if (item != -1) {
            *marks |= (u16) (1u << item);
            candidates &= (u16) ~(1u << item);
            count--;
        }
    }
}
CLEAN_AS(func_0207d634, VillagerEntry_MarkItems)
