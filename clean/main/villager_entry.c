/* One of the town's villagers (villager_entry.h). */
#include "villager_entry.h"

#include "clean.h"
#include "npc_id.h"
#include "villager_roster.h"
#include "villager_state.h"

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

extern NpcId *func_0208150c(const void *villager);         /* the villager's NpcId, at 0x7a0 */
extern VillagerState *func_0207f270(const void *villager); /* its entry of the state table */
extern unsigned int func_020644cc(int bound);              /* a random number below `bound` */
extern void func_0209e474(DateTime *now);                  /* the clock's date and time */
/* Whether `when` falls in the hours a villager of that personality sleeps. */
extern int func_020821d4(int personality, const DateTime *when);
extern void *func_020984e8(void);                /* the current player's record, or NULL */
extern u8 *func_02099870(void *record);          /* the player's id (town and name), at 0x247e */
extern u8 *func_02099158(void *record);          /* the record's part at 0x245c */
extern int func_02099020(void *record, u32 bit); /* a bit of the record's flags */
extern int func_020951bc(const void *player);    /* whether the player id is set */
/* 0 for a player of this town, 1 for one of another town, 2 for an id not set. */
extern int func_02094ffc(const void *player);
/* The villager's memory of the player (0x80 bytes), or NULL when it does not know the player. */
extern s8 *func_020807a8(const void *villager, const void *player);
extern int func_02081d20(const s8 *memory); /* how fond the villager is (signed byte 0x6c) */
extern void func_020818c0(s8 *memory);      /* sets bit 14 of its halfword 0x7c */
extern void func_020819d0(u8 *memory);      /* clears bit 6 of its halfword 0x7c */
/* The villager put on the record's part at 0x245c with how fond it is and its town. */
extern int func_02099d08(u8 *part, const NpcId *npc, int fondness, const NpcIdHead *town);
extern int func_0207ffa0(const u8 *villager, u32 item); /* whether the item index is 0-9 */
extern int func_0204bcdc(u16 *item);                    /* whether the item code is of kind 3 or 4 (its top four bits) */

static int has_villager(const u8 *villager)
{
    return NpcId_IsValid(func_0208150c(villager));
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
    return (func_02081d20(memory) + 0x100) >> 7;
}

/* ---- Byte 0x1e of its state entry */

/* func_0207d0f0: `amount` added to byte 0x1e, kept within 0-32. */
void VillagerEntry_AddByte1E(u8 *villager, int amount)
{
    if (!has_villager(villager)) {
        return;
    }
    VillagerState *state = func_0207f270(villager);
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
        VillagerState_DoubleByte1E(func_0207f270(villager));
    }
}
CLEAN_AS(func_0207d128, VillagerEntry_DoubleByte1E)

/* func_0207d148: byte 0x1e halved. */
void VillagerEntry_HalveByte1E(u8 *villager)
{
    if (has_villager(villager)) {
        VillagerState *state = func_0207f270(villager);
        state->byte_1e = (u8) (state->byte_1e >> 1);
    }
}
CLEAN_AS(func_0207d148, VillagerEntry_HalveByte1E)

/* func_0207d16c: byte 0x1e cleared. */
void VillagerEntry_ClearByte1E(u8 *villager)
{
    if (has_villager(villager)) {
        func_0207f270(villager)->byte_1e = 0;
    }
}
CLEAN_AS(func_0207d16c, VillagerEntry_ClearByte1E)

/* The player's record, the current player's for NULL, when it can be used here: it exists, its
 * player id is set and its flag 1 is clear; else NULL. */
static void *usable_record(void *record)
{
    if (record == NULL) {
        record = func_020984e8();
    }
    if (record == NULL || func_020951bc(func_02099870(record)) == 0 ||
        func_02099020(record, VILLAGER_ENTRY_RECORD_FLAG) != 0) {
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
        func_0207f270(villager)->byte_1e == VILLAGER_ENTRY_BYTE_1E_MAX) {
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
        const s8 *memory = func_020807a8(villager, func_02099870(record));
        if (memory != NULL) {
            int factor = fondness_factor(memory);
            amount = (int) func_020644cc(VILLAGER_ENTRY_RAISE_DRAW) * factor;
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
    VillagerState *state = func_0207f270(villager);
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
    VillagerState *state = func_0207f270(villager);
    state->byte_1e = 0;
    record = usable_record(record);
    if (record == NULL) {
        return;
    }
    const s8 *memory = func_020807a8(villager, func_02099870(record));
    if (memory == NULL) {
        return;
    }
    int factor = fondness_factor(memory);
    int value = factor * ((int) func_020644cc(VILLAGER_ENTRY_SET_DRAW) + 1);
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
        record = func_020984e8();
    }
    if (record == NULL) {
        return 0;
    }
    u8 *player = func_02099870(record);
    if (func_020951bc(player) == 0 || func_02094ffc(player) != VILLAGER_ENTRY_OTHER_TOWN) {
        return 0;
    }
    const s8 *memory = func_020807a8(villager, player);
    if (memory == NULL) {
        return 0;
    }
    u8 *part = func_02099158(record);
    const NpcId *npc = func_0208150c(villager);
    return func_02099d08(part, npc, func_02081d20(memory), &data_021dc7aa);
}
CLEAN_AS(func_0207d4bc, VillagerEntry_NoteVisitor)

/* func_0207d540: bit 14 of the flags of the villager's memory of `player` set, when it knows
 * the player. */
void VillagerEntry_FlagMemory(u8 *villager, const void *player)
{
    if (!has_villager(villager) || func_020951bc(player) == 0) {
        return;
    }
    s8 *memory = func_020807a8(villager, player);
    if (memory != NULL) {
        func_020818c0(memory);
    }
}
CLEAN_AS(func_0207d540, VillagerEntry_FlagMemory)

/* func_0207d5bc: bit 6 of the flags of all eight memories cleared. */
void VillagerEntry_ClearMemoryFlag6(u8 *villager)
{
    for (int i = 0; i < VILLAGER_ENTRY_MEMORIES; i++) {
        func_020819d0(villager + i * VILLAGER_ENTRY_MEMORY_SIZE);
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
        func_0209e474(&now);
        when = &now;
    }
    return func_020821d4(NpcId_Personality(func_0208150c(villager)), when);
}
CLEAN_AS(func_0207d578, VillagerEntry_IsSleepTime)

/* ---- Its items */

/* func_0207d5dc: item `item` (0-9) unmarked. */
void VillagerEntry_UnmarkItem(u8 *villager, int item)
{
    if (func_0207ffa0(villager, (u32) item)) {
        *item_marks(villager) &= (u16) ~(1u << item);
    }
}
CLEAN_AS(func_0207d5dc, VillagerEntry_UnmarkItem)

/* func_0207d608: whether item `item` (0-9) is marked. */
int VillagerEntry_IsItemMarked(u8 *villager, int item)
{
    return func_0207ffa0(villager, (u32) item) && ((*item_marks(villager) >> item) & 1);
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
        if (func_0204bcdc(&items[i])) {
            candidates |= (u16) (1u << i);
            count++;
        }
    }

    int to_mark = count > VILLAGER_ENTRY_MARK_MOST ? VILLAGER_ENTRY_MARK_MOST : count;
    if (to_mark > VILLAGER_ENTRY_MARK_LEAST) {
        to_mark = (int) func_020644cc(to_mark - (VILLAGER_ENTRY_MARK_LEAST - 1)) + VILLAGER_ENTRY_MARK_LEAST;
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
