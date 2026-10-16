/* The running state of the town's villagers (villager_state.h). */
#include "villager_state.h"

#include "clean.h"
#include "session.h"

extern VillagerStates data_021d13e4;
extern u8 data_020e54a8;          /* 0 or 1, a mode many scenes test */
extern NetSession *data_020ccf94; /* the game's session */

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void func_0209bd5c(void *object); /* no item (0xfff1), 0x16 at 0x0a, byte 0x0b cleared */
extern void func_0209c52c(void *bytes);  /* eight bytes cleared */
extern void func_0209bd80(void *object); /* both words cleared, no item (0xfff1), 0x16 at 0x0a */
extern void *func_0209c53c(void *bytes); /* func_0209c52c, then the bytes */
extern void func_0209bd7c(void *object); /* the object's destructor: does nothing */
extern void func_0209c538(void *bytes);  /* the bytes' destructor: does nothing */
/* Whether func_020b6694 accepts the current scene (func_020b65c4). */
extern int func_020b6680(void);

static_assert(sizeof(VillagerTally) == 4, "tally size");
static_assert(offsetof(VillagerState, object) == 0x04, "object");
static_assert(offsetof(VillagerState, bytes_10) == 0x10, "bytes 0x10");
static_assert(offsetof(VillagerState, byte_18) == 0x18, "byte 0x18");
static_assert(offsetof(VillagerState, counter) == 0x1a, "counter");
static_assert(offsetof(VillagerState, flags) == 0x1d, "flags");
static_assert(offsetof(VillagerState, word_20) == 0x20, "word 0x20");
static_assert(offsetof(VillagerState, item) == 0x26, "item");
static_assert(offsetof(VillagerState, tally) == 0x28, "tally");
static_assert(sizeof(VillagerState) == 0x2c, "entry size");
static_assert(offsetof(VillagerStates, index_160) == 0x160, "index 0x160");
static_assert(offsetof(VillagerStates, index_164) == 0x164, "index 0x164");
static_assert(offsetof(VillagerStates, word_168) == 0x168, "word 0x168");
static_assert(offsetof(VillagerStates, index_16c) == 0x16c, "index 0x16c");

/* Whether this system holds its slot of the session (Session_IsSlotTaken). */
static int has_session_slot(void)
{
    return Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot) != 0;
}

/* ---- The table */

/* func_02079144 */
void VillagerState_ClearWord168(void)
{
    VillagerState_Table()->word_168 = 0;
}
CLEAN_AS(func_02079144, VillagerState_ClearWord168)

/* func_0207915c */
int VillagerState_GetIndex164(void)
{
    return VillagerState_Table()->index_164;
}
CLEAN_AS(func_0207915c, VillagerState_GetIndex164)

/* func_02079174 */
void VillagerState_SetIndex164(unsigned char index)
{
    VillagerState_Table()->index_164 = (s8) index;
}
CLEAN_AS(func_02079174, VillagerState_SetIndex164)

/* func_0207918c */
int VillagerState_GetIndex16C(void)
{
    return VillagerState_Table()->index_16c;
}
CLEAN_AS(func_0207918c, VillagerState_GetIndex16C)

/* func_020791a4 */
void VillagerState_SetIndex16C(char index)
{
    VillagerState_Table()->index_16c = (s8) index;
}
CLEAN_AS(func_020791a4, VillagerState_SetIndex16C)

/* func_020791bc */
signed char VillagerState_GetIndex163(void)
{
    return VillagerState_Table()->index_163;
}
CLEAN_AS(func_020791bc, VillagerState_GetIndex163)

/* func_020791d4 */
void VillagerState_SetIndex163(unsigned char index)
{
    VillagerState_Table()->index_163 = (s8) index;
}
CLEAN_AS(func_020791d4, VillagerState_SetIndex163)

/* func_020791ec */
int VillagerState_GetIndex162(void)
{
    return VillagerState_Table()->index_162;
}
CLEAN_AS(func_020791ec, VillagerState_GetIndex162)

/* func_02079204 */
void VillagerState_SetIndex162(unsigned char index)
{
    VillagerState_Table()->index_162 = (s8) index;
}
CLEAN_AS(func_02079204, VillagerState_SetIndex162)

/* func_0207921c */
void VillagerState_ClearIndex160(void)
{
    VillagerState_Table()->index_160 = VILLAGER_STATE_NONE;
}
CLEAN_AS(func_0207921c, VillagerState_ClearIndex160)

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
void VillagerState_ClearAllFlag2(void)
{
    VillagerState *entry = VillagerState_Table()->entries;

    for (int i = 0; i < VILLAGER_STATE_ENTRIES; i++) {
        entry[i].flags &= (u8) ~VILLAGER_STATE_FLAG_2;
    }
}
CLEAN_AS(func_02079260, VillagerState_ClearAllFlag2)

/* func_02079280 */
void VillagerState_ClearAllFlag0(void)
{
    VillagerState *entry = VillagerState_Table()->entries;

    for (int i = 0; i < VILLAGER_STATE_ENTRIES; i++) {
        entry[i].flags &= (u8) ~VILLAGER_STATE_FLAG_0;
    }
}
CLEAN_AS(func_02079280, VillagerState_ClearAllFlag0)

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

/* func_020792dc: each entry's state, flag 0, byte 0x18, counter, flag 2 and tally cleared. */
void VillagerState_ClearTable(VillagerStates *table)
{
    for (int i = 0; i < VILLAGER_STATE_ENTRIES; i++) {
        VillagerState *entry = &table->entries[i];

        VillagerState_SetState(entry, 0);
        entry->flags &= (u8) ~VILLAGER_STATE_FLAG_0;
        VillagerState_SetByte18(entry, 0);
        VillagerState_SetCounter(entry, 0);
        entry->flags &= (u8) ~VILLAGER_STATE_FLAG_2;
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
    table->index_160 = VILLAGER_STATE_NONE;
    table->byte_161 = 0;
    table->index_162 = VILLAGER_STATE_NONE;
    table->index_163 = VILLAGER_STATE_NONE;
    table->index_164 = VILLAGER_STATE_NONE;
    table->word_168 = 0;
    table->index_16c = VILLAGER_STATE_NONE;
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
void VillagerState_ClearItem(VillagerState *entry)
{
    entry->item = 0xfff1;
}
CLEAN_AS(func_02079450, VillagerState_ClearItem)

/* func_0207945c */
void VillagerState_SetItem(VillagerState *entry, const u16 *item)
{
    entry->item = *item;
}
CLEAN_AS(func_0207945c, VillagerState_SetItem)

/* func_02079464 */
u16 *VillagerState_Item(VillagerState *entry)
{
    return &entry->item;
}
CLEAN_AS(func_02079464, VillagerState_Item)

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
    if (func_020b6680() == 0) {
        entry->flags |= VILLAGER_STATE_FLAG_1;
    }
}
CLEAN_AS(func_02079478, VillagerState_SetFlag1UnlessScene)

/* func_02079494: one off the counter, which stops at 0. */
void VillagerState_CountDown(VillagerState *entry)
{
    if (entry->counter != 0) {
        entry->counter--;
    }
}
CLEAN_AS(func_02079494, VillagerState_CountDown)

/* func_020794a0 */
int VillagerState_GetCounter(const VillagerState *entry)
{
    return entry->counter;
}
CLEAN_AS(func_020794a0, VillagerState_GetCounter)

/* func_020794a4: QUIRK: keeps the low 16 bits. */
void VillagerState_SetCounter(VillagerState *entry, int counter)
{
    entry->counter = (u16) counter;
}
CLEAN_AS(func_020794a4, VillagerState_SetCounter)

/* func_020794a8: `amount` added, up to 0xffff.
 * QUIRK: only the top is held: a sum below 0 keeps its low 16 bits (5 - 10 gives 0xfffb), and
 * the sum wraps as the ARM's 32-bit addition does. */
void VillagerState_AddCounter(VillagerState *entry, int amount)
{
    int32_t sum = (int32_t) ((uint32_t) entry->counter + (uint32_t) amount);

    entry->counter = sum >= 0xffff ? 0xffff : (u16) sum;
}
CLEAN_AS(func_020794a8, VillagerState_AddCounter)

/* func_020794c0: QUIRK: keeps the low 8 bits. */
void VillagerState_SetByte18(VillagerState *entry, int value)
{
    entry->byte_18 = (u8) value;
}
CLEAN_AS(func_020794c0, VillagerState_SetByte18)

/* func_020794c4 */
int VillagerState_GetByte18(const VillagerState *entry)
{
    return entry->byte_18;
}
CLEAN_AS(func_020794c4, VillagerState_GetByte18)

/* func_020794c8: QUIRK: keeps the low 8 bits. */
void VillagerState_SetByte1C(VillagerState *entry, int value)
{
    entry->byte_1c = (u8) value;
}
CLEAN_AS(func_020794c8, VillagerState_SetByte1C)

/* func_020794cc */
int VillagerState_GetByte1C(const VillagerState *entry)
{
    return entry->byte_1c;
}
CLEAN_AS(func_020794cc, VillagerState_GetByte1C)

/* func_020794d0 */
u8 *VillagerState_Object(VillagerState *entry)
{
    return entry->object;
}
CLEAN_AS(func_020794d0, VillagerState_Object)

/* func_020794d4: QUIRK: keeps the low 8 bits. */
void VillagerState_SetByte01(VillagerState *entry, int value)
{
    entry->byte_01 = (u8) value;
}
CLEAN_AS(func_020794d4, VillagerState_SetByte01)

/* func_020794d8: byte 0x01, read as 1 when it is 0 while this system holds its session slot. */
int VillagerState_LinkedByte01(const VillagerState *entry)
{
    if (has_session_slot() && entry->byte_01 == 0) {
        return 1;
    }
    return entry->byte_01;
}
CLEAN_AS(func_020794d8, VillagerState_LinkedByte01)

/* func_02079500: a state of 2-6 becomes 1 when VillagerState_LinkedByte01 is 0, else 0; other
 * states stay. */
void VillagerState_SettleState(VillagerState *entry)
{
    if (entry->state >= 2 && entry->state <= 6) {
        entry->state = VillagerState_LinkedByte01(entry) == 0 ? 1 : 0;
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

/* func_0207956c: the entry cleared and set up: state 0, byte 0x01 3, byte 0x18 5, byte 0x1c 12,
 * no item. */
void VillagerState_Init(VillagerState *entry)
{
    MI_CpuFill8(entry, 0, sizeof *entry);
    entry->state = 0;
    entry->byte_01 = 3;
    func_0209bd5c(entry->object);
    func_0209c52c(entry->bytes_10);
    entry->byte_18 = 5;
    entry->byte_1c = 12;
    entry->word_20 = 0;
    entry->half_24 = 0;
    VillagerState_ClearItem(entry);
}
CLEAN_AS(func_0207956c, VillagerState_Init)

/* func_020795a8: the destructor: the tally, the bytes at 0x10 and the object at 0x04 are
 * destroyed, in that order. */
VillagerState *VillagerState_Destruct(VillagerState *entry)
{
    VillagerTally_Destruct(&entry->tally);
    func_0209c538(entry->bytes_10);
    func_0209bd7c(entry->object);
    return entry;
}
CLEAN_AS(func_020795a8, VillagerState_Destruct)

/* func_020795c8: the constructor: the object at 0x04 and the bytes at 0x10 are built, the item
 * is none and the tally is built. The other fields are left as they are. */
VillagerState *VillagerState_Construct(VillagerState *entry)
{
    func_0209bd80(entry->object);
    func_0209c53c(entry->bytes_10);
    entry->item = 0xfff1;
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
