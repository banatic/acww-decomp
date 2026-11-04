/* The running state of the town's villagers (villager_state.h). */
#include "villager_state.h"

#include "clean.h"
#include "session.h"
#include "item_object.h"
#include "scene_query.h"
#include "villager_mode_record.h"

extern VillagerStates data_021d13e4;
extern u8 data_020e54a8;          /* 0 or 1, a mode many scenes test */
extern NetSession *data_020ccf94; /* the game's session */

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

static_assert(sizeof(VillagerTally) == 4, "tally size");
static_assert(offsetof(VillagerState, object) == 0x04, "object");
static_assert(offsetof(VillagerState, bytes_10) == 0x10, "bytes 0x10");
static_assert(offsetof(VillagerState, mood) == 0x18, "mood");
static_assert(offsetof(VillagerState, mood_frames) == 0x1a, "mood frames");
static_assert(offsetof(VillagerState, flags) == 0x1d, "flags");
static_assert(offsetof(VillagerState, room_score) == 0x20, "room score");
static_assert(offsetof(VillagerState, held_item) == 0x26, "held item");
static_assert(offsetof(VillagerState, tally) == 0x28, "tally");
static_assert(sizeof(VillagerState) == 0x2c, "entry size");
static_assert(offsetof(VillagerStates, flea_villager) == 0x160, "flea_villager");
static_assert(offsetof(VillagerStates, flea_market_visitor) == 0x164, "flea_market_visitor");
static_assert(offsetof(VillagerStates, idle_frames) == 0x168, "idle_frames");
static_assert(offsetof(VillagerStates, birthday_greeter) == 0x16c, "birthday_greeter");

/* Whether this system holds its slot of the session (Session_IsSlotTaken). */
static int has_session_slot(void)
{
    return Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot) != 0;
}

/* ---- The table */

/* func_02079144 */
void VillagerState_ClearIdleFrames(void)
{
    VillagerState_Table()->idle_frames = 0;
}
CLEAN_AS(func_02079144, VillagerState_ClearIdleFrames)

/* func_0207915c */
int VillagerState_GetFleaMarketVisitor(void)
{
    return VillagerState_Table()->flea_market_visitor;
}
CLEAN_AS(func_0207915c, VillagerState_GetFleaMarketVisitor)

/* func_02079174 */
void VillagerState_SetFleaMarketVisitor(unsigned char index)
{
    VillagerState_Table()->flea_market_visitor = (s8) index;
}
CLEAN_AS(func_02079174, VillagerState_SetFleaMarketVisitor)

/* func_0207918c */
int VillagerState_GetBirthdayGreeter(void)
{
    return VillagerState_Table()->birthday_greeter;
}
CLEAN_AS(func_0207918c, VillagerState_GetBirthdayGreeter)

/* func_020791a4 */
void VillagerState_SetBirthdayGreeter(char index)
{
    VillagerState_Table()->birthday_greeter = (s8) index;
}
CLEAN_AS(func_020791a4, VillagerState_SetBirthdayGreeter)

/* func_020791bc */
signed char VillagerState_GetBirthdayCompanion(void)
{
    return VillagerState_Table()->birthday_companion;
}
CLEAN_AS(func_020791bc, VillagerState_GetBirthdayCompanion)

/* func_020791d4 */
void VillagerState_SetBirthdayCompanion(unsigned char index)
{
    VillagerState_Table()->birthday_companion = (s8) index;
}
CLEAN_AS(func_020791d4, VillagerState_SetBirthdayCompanion)

/* func_020791ec */
int VillagerState_GetBirthdayVillager(void)
{
    return VillagerState_Table()->birthday_villager;
}
CLEAN_AS(func_020791ec, VillagerState_GetBirthdayVillager)

/* func_02079204 */
void VillagerState_SetBirthdayVillager(unsigned char index)
{
    VillagerState_Table()->birthday_villager = (s8) index;
}
CLEAN_AS(func_02079204, VillagerState_SetBirthdayVillager)

/* func_0207921c */
void VillagerState_ClearFleaVillager(void)
{
    VillagerState_Table()->flea_villager = VILLAGER_STATE_NONE;
}
CLEAN_AS(func_0207921c, VillagerState_ClearFleaVillager)

/* func_02079238: every entry's tally cleared. */
void VillagerState_ClearAllTallies(void)
{
    VillagerState *entry = VillagerState_Table()->entries;

    for (int i = 0; i < VILLAGER_STATE_ENTRIES; i++) {
        VillagerTally_Clear(VillagerState_Tally(&entry[i]));
    }
}
CLEAN_AS(func_02079238, VillagerState_ClearAllTallies)

/* func_02079260 */
void VillagerState_ClearAllGreeted(void)
{
    VillagerState *entry = VillagerState_Table()->entries;

    for (int i = 0; i < VILLAGER_STATE_ENTRIES; i++) {
        entry[i].flags &= (u8) ~VILLAGER_STATE_FLAG_GREETED;
    }
}
CLEAN_AS(func_02079260, VillagerState_ClearAllGreeted)

/* func_02079280 */
void VillagerState_ClearAllStingSaid(void)
{
    VillagerState *entry = VillagerState_Table()->entries;

    for (int i = 0; i < VILLAGER_STATE_ENTRIES; i++) {
        entry[i].flags &= (u8) ~VILLAGER_STATE_FLAG_STING_SAID;
    }
}
CLEAN_AS(func_02079280, VillagerState_ClearAllStingSaid)

/* func_020792a0 */
void VillagerState_Clear(void)
{
    VillagerState_ClearTable(VillagerState_Table());
}
CLEAN_AS(func_020792a0, VillagerState_Clear)

/* func_020792b4: the table asked for and VillagerState_NoOp called. */
void VillagerState_CallNoOp(void)
{
    (void) VillagerState_Table();
    VillagerState_NoOp();
}
CLEAN_AS(func_020792b4, VillagerState_CallNoOp)

/* func_020792c8 */
void VillagerState_Reset(void)
{
    VillagerState_ResetTable(VillagerState_Table());
}
CLEAN_AS(func_020792c8, VillagerState_Reset)

/* func_020792dc: each entry's state, flag 0, mood (byte 0x18), counter, flag 2 and tally cleared. */
void VillagerState_ClearTable(VillagerStates *table)
{
    for (int i = 0; i < VILLAGER_STATE_ENTRIES; i++) {
        VillagerState *entry = &table->entries[i];

        VillagerState_SetState(entry, 0);
        entry->flags &= (u8) ~VILLAGER_STATE_FLAG_STING_SAID;
        VillagerState_SetMood(entry, 0);
        VillagerState_SetMoodFrames(entry, 0);
        entry->flags &= (u8) ~VILLAGER_STATE_FLAG_GREETED;
        VillagerTally_Clear(VillagerState_Tally(entry));
    }
}
CLEAN_AS(func_020792dc, VillagerState_ClearTable)

/* func_0207932c: does nothing. */
void VillagerState_NoOp(void) {}
CLEAN_AS(func_0207932c, VillagerState_NoOp)

/* func_02079330: the entry of villager index `index`, or null for an index outside 0-7. */
VillagerState *VillagerState_At(VillagerStates *table, int index)
{
    if (!VillagerState_IsIndex(index)) {
        return NULL;
    }
    return &table->entries[index];
}
CLEAN_AS(func_02079330, VillagerState_At)

/* func_02079350 */
VillagerStates *VillagerState_Table(void)
{
    return &data_021d13e4;
}
CLEAN_AS(func_02079350, VillagerState_Table)

/* func_02079358: every entry set up, and the town bytes to none. */
void VillagerState_ResetTable(VillagerStates *table)
{
    for (int i = 0; i < VILLAGER_STATE_ENTRIES; i++) {
        VillagerState_Init(&table->entries[i]);
    }
    table->flea_villager = VILLAGER_STATE_NONE;
    table->fox_password_villager = 0;
    table->birthday_villager = VILLAGER_STATE_NONE;
    table->birthday_companion = VILLAGER_STATE_NONE;
    table->flea_market_visitor = VILLAGER_STATE_NONE;
    table->idle_frames = 0;
    table->birthday_greeter = VILLAGER_STATE_NONE;
}
CLEAN_AS(func_02079358, VillagerState_ResetTable)

/* func_020793b4: 0-7. */
int VillagerState_IsIndex(int index)
{
    return index >= 0 && index < VILLAGER_STATE_ENTRIES;
}
CLEAN_AS(func_020793b4, VillagerState_IsIndex)

/* ---- The tally */

/* func_020793c4: 2 from a count of 10, 1 from 7, else 0; always 0 while data_020e54a8 is set. */
int VillagerTally_Level(const VillagerTally *tally)
{
    if (data_020e54a8 != 0) {
        return 0;
    }
    if (tally->count >= 10) {
        return 2;
    }
    if (tally->count >= 7) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_020793c4, VillagerTally_Level)

/* func_020793f0: the delay and the timer started; the count is kept. */
void VillagerTally_Start(VillagerTally *tally)
{
    tally->delay = VILLAGER_TALLY_DELAY;
    tally->timer = VILLAGER_TALLY_TIMER;
}
CLEAN_AS(func_020793f0, VillagerTally_Start)

/* func_02079400: one more while the delay runs.
 * QUIRK: the count is a byte and wraps from 255 to 0. */
void VillagerTally_Count(VillagerTally *tally)
{
    if (tally->delay != 0) {
        tally->count++;
    }
}
CLEAN_AS(func_02079400, VillagerTally_Count)

/* func_02079410: unless `skip`, one tick off the delay, or off the timer once the delay is out;
 * the count dropped whenever the timer is then out. */
void VillagerTally_Tick(VillagerTally *tally, int skip)
{
    if (skip != 0) {
        return;
    }
    if (tally->delay != 0) {
        tally->delay--;
    } else if (tally->timer != 0) {
        tally->timer--;
    }
    if (tally->timer == 0) {
        tally->count = 0;
    }
}
CLEAN_AS(func_02079410, VillagerTally_Tick)

/* func_02079438 */
void VillagerTally_Clear(VillagerTally *tally)
{
    tally->delay = 0;
    tally->timer = 0;
    tally->count = 0;
}
CLEAN_AS(func_02079438, VillagerTally_Clear)

/* func_02079444: the destructor: does nothing. */
void VillagerTally_Destruct(VillagerTally *tally)
{
    (void) tally;
}
CLEAN_AS(func_02079444, VillagerTally_Destruct)

/* func_02079448: the constructor: does nothing. */
void VillagerTally_Construct(VillagerTally *tally)
{
    (void) tally;
}
CLEAN_AS(func_02079448, VillagerTally_Construct)

/* ---- An entry */

/* func_0207944c */
VillagerTally *VillagerState_Tally(VillagerState *entry)
{
    return &entry->tally;
}
CLEAN_AS(func_0207944c, VillagerState_Tally)

/* func_02079450 */
void VillagerState_ClearHeldItem(VillagerState *entry)
{
    entry->held_item = 0xfff1;
}
CLEAN_AS(func_02079450, VillagerState_ClearHeldItem)

/* func_0207945c */
void VillagerState_SetHeldItem(VillagerState *entry, const u16 *item)
{
    entry->held_item = *item;
}
CLEAN_AS(func_0207945c, VillagerState_SetHeldItem)

/* func_02079464 */
u16 *VillagerState_HeldItem(VillagerState *entry)
{
    return &entry->held_item;
}
CLEAN_AS(func_02079464, VillagerState_HeldItem)

/* func_02079468: byte 0x1e doubled, at most 32. */
void VillagerState_DoubleByte1E(VillagerState *entry)
{
    int doubled = entry->byte_1e * 2;

    entry->byte_1e = (u8) (doubled > 32 ? 32 : doubled);
}
CLEAN_AS(func_02079468, VillagerState_DoubleByte1E)

/* func_02079478: flag 1 set unless the current scene passes func_020b6694. */
void VillagerState_SetFlag1UnlessScene(VillagerState *entry)
{
    if (SceneQuery_InVillagerHouse() == 0) {
        entry->flags |= VILLAGER_STATE_FLAG_1;
    }
}
CLEAN_AS(func_02079478, VillagerState_SetFlag1UnlessScene)

/* func_02079494: one off the counter, which stops at 0. */
void VillagerState_CountDownMood(VillagerState *entry)
{
    if (entry->mood_frames != 0) {
        entry->mood_frames--;
    }
}
CLEAN_AS(func_02079494, VillagerState_CountDownMood)

/* func_020794a0 */
int VillagerState_GetMoodFrames(const VillagerState *entry)
{
    return entry->mood_frames;
}
CLEAN_AS(func_020794a0, VillagerState_GetMoodFrames)

/* func_020794a4: QUIRK: keeps the low 16 bits. */
void VillagerState_SetMoodFrames(VillagerState *entry, int counter)
{
    entry->mood_frames = (u16) counter;
}
CLEAN_AS(func_020794a4, VillagerState_SetMoodFrames)

/* func_020794a8: `amount` added, up to 0xffff.
 * QUIRK: only the top is held: a sum below 0 keeps its low 16 bits (5 - 10 gives 0xfffb), and
 * the sum wraps as the ARM's 32-bit addition does. */
void VillagerState_AddMoodFrames(VillagerState *entry, int amount)
{
    int32_t sum = (int32_t) ((uint32_t) entry->mood_frames + (uint32_t) amount);

    entry->mood_frames = sum >= 0xffff ? 0xffff : (u16) sum;
}
CLEAN_AS(func_020794a8, VillagerState_AddMoodFrames)

/* func_020794c0: QUIRK: keeps the low 8 bits. */
void VillagerState_SetMood(VillagerState *entry, int value)
{
    entry->mood = (u8) value;
}
CLEAN_AS(func_020794c0, VillagerState_SetMood)

/* func_020794c4 */
int VillagerState_GetMood(const VillagerState *entry)
{
    return entry->mood;
}
CLEAN_AS(func_020794c4, VillagerState_GetMood)

/* func_020794c8: QUIRK: keeps the low 8 bits. */
void VillagerState_SetActivity(VillagerState *entry, int value)
{
    entry->activity = (u8) value;
}
CLEAN_AS(func_020794c8, VillagerState_SetActivity)

/* func_020794cc */
int VillagerState_GetActivity(const VillagerState *entry)
{
    return entry->activity;
}
CLEAN_AS(func_020794cc, VillagerState_GetActivity)

/* func_020794d0 */
u8 *VillagerState_Object(VillagerState *entry)
{
    return entry->object;
}
CLEAN_AS(func_020794d0, VillagerState_Object)

/* func_020794d4: QUIRK: keeps the low 8 bits. */
void VillagerState_SetPlace(VillagerState *entry, int value)
{
    entry->place = (u8) value;
}
CLEAN_AS(func_020794d4, VillagerState_SetPlace)

/* func_020794d8: the place, read as at home (1) when it is outside (0) while this system holds
 * its session slot. */
int VillagerState_LinkedPlace(const VillagerState *entry)
{
    if (has_session_slot() && entry->place == 0) {
        return 1;
    }
    return entry->place;
}
CLEAN_AS(func_020794d8, VillagerState_LinkedPlace)

/* func_02079500: a state of 2-6 becomes 1 when VillagerState_LinkedPlace is 0, else 0; other
 * states stay. */
void VillagerState_SettleState(VillagerState *entry)
{
    if (entry->state >= 2 && entry->state <= 6) {
        entry->state = VillagerState_LinkedPlace(entry) == 0 ? 1 : 0;
    }
}
CLEAN_AS(func_02079500, VillagerState_SettleState)

/* func_02079540: QUIRK: keeps the low 8 bits. */
void VillagerState_SetState(VillagerState *entry, int state)
{
    entry->state = (u8) state;
}
CLEAN_AS(func_02079540, VillagerState_SetState)

/* func_02079544: the state, read as 0 unless it is 7 while this system holds its session slot. */
int VillagerState_LinkedState(const VillagerState *entry)
{
    if (has_session_slot() && entry->state != 7) {
        return 0;
    }
    return entry->state;
}
CLEAN_AS(func_02079544, VillagerState_LinkedState)

/* func_0207956c: the entry cleared and set up: state 0, place (byte 0x01) 3, mood (byte 0x18) 5, activity (byte 0x1c) 12,
 * no item. */
void VillagerState_Init(VillagerState *entry)
{
    MI_CpuFill8(entry, 0, sizeof *entry);
    entry->state = 0;
    entry->place = 3;
    ItemObject_Clear((ItemObject *) (void *) entry->object);
    VillagerModeRecord_ClearKindBytes(entry->bytes_10);
    entry->mood = 5;
    entry->activity = 12;
    entry->room_score = 0;
    entry->room_score_flags = 0;
    VillagerState_ClearHeldItem(entry);
}
CLEAN_AS(func_0207956c, VillagerState_Init)

/* func_020795a8: the destructor: the tally, the bytes at 0x10 and the object at 0x04 are
 * destroyed, in that order. */
VillagerState *VillagerState_Destruct(VillagerState *entry)
{
    VillagerTally_Destruct(&entry->tally);
    VillagerModeRecord_DestructKindBytes(entry->bytes_10);
    ItemObject_Destruct((ItemObject *) (void *) entry->object);
    return entry;
}
CLEAN_AS(func_020795a8, VillagerState_Destruct)

/* func_020795c8: the constructor: the object at 0x04 and the bytes at 0x10 are built, the item
 * is none and the tally is built. The other fields are left as they are. */
VillagerState *VillagerState_Construct(VillagerState *entry)
{
    ItemObject_Construct((ItemObject *) (void *) entry->object);
    VillagerModeRecord_ConstructKindBytes(entry->bytes_10);
    entry->held_item = 0xfff1;
    VillagerTally_Construct(&entry->tally);
    return entry;
}
CLEAN_AS(func_020795c8, VillagerState_Construct)

/* The entry destructor, as the game hands it to __cxa_vec_cleanup. */
extern void func_020795a8(void *entry);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* func_02082528: the table's destructor (registered when the game starts): the eight entries,
 * from the last to the first (VillagerState_Destruct). The town bytes need none. */
VillagerStates *VillagerState_DestructTable(VillagerStates *table)
{
    __cxa_vec_cleanup(table->entries, VILLAGER_STATE_ENTRIES, sizeof(VillagerState), func_020795a8);
    return table;
}
CLEAN_AS(func_02082528, VillagerState_DestructTable)
