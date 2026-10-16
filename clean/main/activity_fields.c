/* The fields of the activity process (activity.h): the current activity object, the setters the
 * system packet handlers and session messages use, and the parts it keeps for the card and the
 * packed town. */
#include "activity.h"

#include "clean.h"

static_assert(offsetof(Activity, block_copy) == 0xb8 && offsetof(Activity, exchange_block) == 0xc0, "activity");
static_assert(offsetof(Activity, letters) == 0xc4 && offsetof(Activity, pack_buffer) == 0xc8, "activity");
static_assert(offsetof(Activity, pack_thread) == 0xcc && offsetof(Activity, slot_mask) == 0xd4, "activity");
static_assert(offsetof(Activity, byte_d6) == 0xd6 && offsetof(Activity, byte_d7) == 0xd7, "activity");
static_assert(offsetof(Activity, flag_d9) == 0xd9 && offsetof(Activity, flag_da) == 0xda, "activity");
static_assert(offsetof(Activity, date_time) == 0xdc && offsetof(Activity, flag_e4) == 0xe4, "activity");
static_assert(offsetof(Activity, flag_e5) == 0xe5 && offsetof(Activity, flag_e6) == 0xe6, "activity");
static_assert(offsetof(Activity, slot_e7) == 0xe7 && offsetof(Activity, slot_eb) == 0xeb, "activity");
static_assert(offsetof(Activity, slot_answer) == 0xef && offsetof(Activity, flag_f3) == 0xf3, "activity");
static_assert(offsetof(Activity, slot_ack) == 0xf4 && offsetof(Activity, slot_fc) == 0xfc, "activity");
static_assert(offsetof(Activity, slot_100) == 0x100 && offsetof(Activity, flag_101) == 0x101, "activity");
static_assert(offsetof(Activity, byte_102) == 0x102 && offsetof(Activity, block_source) == 0x103, "activity");
static_assert(offsetof(Activity, slot_107) == 0x107 && offsetof(Activity, card_parts) == 0x10e, "activity");

/* The current activity, or NULL. */
extern Activity *data_021f3c3c;

#define NO_SLOT 4 /* Activity_CurrentSlot100 without an activity */

/* func_020a132c */
Activity *Activity_Current(void)
{
    return data_021f3c3c;
}
CLEAN_AS(func_020a132c, Activity_Current)

/* func_020a1338: NULL without an activity. */
struct TownPackThread *Activity_CurrentPackThread(void)
{
    Activity *activity = data_021f3c3c;
    if (activity == NULL) {
        return NULL;
    }
    return activity->pack_thread;
}
CLEAN_AS(func_020a1338, Activity_CurrentPackThread)

/* func_020a1350: NULL without an activity. */
struct TownPackBuffer *Activity_CurrentPackBuffer(void)
{
    if (data_021f3c3c == NULL) {
        return NULL;
    }
    return data_021f3c3c->pack_buffer;
}
CLEAN_AS(func_020a1350, Activity_CurrentPackBuffer)

/* func_020a1368: NULL without an activity. */
u8 *Activity_CurrentLetters(void)
{
    if (data_021f3c3c == NULL) {
        return NULL;
    }
    return data_021f3c3c->letters;
}
CLEAN_AS(func_020a1368, Activity_CurrentLetters)

/* func_020a1380: 0 without an activity. */
int Activity_CurrentByteD6(void)
{
    if (Activity_Current() == NULL) {
        return 0;
    }
    return Activity_Current()->byte_d6;
}
CLEAN_AS(func_020a1380, Activity_CurrentByteD6)

/* func_020a11c4: NO_SLOT without an activity. */
int Activity_CurrentSlot100(void)
{
    if (data_021f3c3c == NULL) {
        return NO_SLOT;
    }
    return data_021f3c3c->slot_100;
}
CLEAN_AS(func_020a11c4, Activity_CurrentSlot100)

/* func_020a11e0: nothing without an activity. */
void Activity_SetCurrentSlot100(u8 slot)
{
    Activity *activity = data_021f3c3c;
    if (activity != NULL) {
        activity->slot_100 = slot;
    }
}
CLEAN_AS(func_020a11e0, Activity_SetCurrentSlot100)

/* func_020a1210: nothing without an activity. */
void Activity_SetCurrentFlagF3(u8 value)
{
    Activity *activity = data_021f3c3c;
    if (activity != NULL) {
        activity->flag_f3 = value;
    }
}
CLEAN_AS(func_020a1210, Activity_SetCurrentFlagF3)

/* func_020a11b8 */
void Activity_SetFlag101(Activity *activity, u8 value)
{
    activity->flag_101 = value;
}
CLEAN_AS(func_020a11b8, Activity_SetFlag101)

/* func_020a11f8
 * REQUIRES: 0 <= slot < ACTIVITY_SLOTS (as for the other per-slot setters). */
void Activity_SetSlotFC(Activity *activity, int slot, int value)
{
    activity->slot_fc[slot] = (u8) value;
}
CLEAN_AS(func_020a11f8, Activity_SetSlotFC)

/* func_020a1200 */
void Activity_SetSlotReported(Activity *activity, int slot, int value)
{
    activity->slot_reported[slot] = (u8) value;
}
CLEAN_AS(func_020a1200, Activity_SetSlotReported)

/* func_020a1208 */
void Activity_SetSlotAck(Activity *activity, int slot, int value)
{
    activity->slot_ack[slot] = (u8) value;
}
CLEAN_AS(func_020a1208, Activity_SetSlotAck)

/* func_020a1224: every slot's answer back to 0 (none yet). */
void Activity_ClearAnswers(Activity *activity)
{
    for (int slot = ACTIVITY_SLOTS - 1; slot >= 0; slot--) {
        activity->slot_answer[slot] = 0;
    }
}
CLEAN_AS(func_020a1224, Activity_ClearAnswers)

/* func_020a1238 */
void Activity_SetSlotAnswer(Activity *activity, int slot, int value)
{
    activity->slot_answer[slot] = (u8) value;
}
CLEAN_AS(func_020a1238, Activity_SetSlotAnswer)

/* func_020a1240 */
void Activity_SetSlotEB(Activity *activity, int slot, int value)
{
    activity->slot_eb[slot] = (u8) value;
}
CLEAN_AS(func_020a1240, Activity_SetSlotEB)

/* func_020a1248 */
void Activity_SetSlotE7(Activity *activity, int slot, int value)
{
    activity->slot_e7[slot] = (u8) value;
}
CLEAN_AS(func_020a1248, Activity_SetSlotE7)

/* func_020a1250 */
u8 *Activity_DateTime(Activity *activity)
{
    return activity->date_time;
}
CLEAN_AS(func_020a1250, Activity_DateTime)

/* func_020a1254 */
void Activity_SetFlagDA(Activity *activity, u8 value)
{
    activity->flag_da = value;
}
CLEAN_AS(func_020a1254, Activity_SetFlagDA)

/* func_020a125c */
void Activity_SetFlagD9(Activity *activity, u8 value)
{
    activity->flag_d9 = value;
}
CLEAN_AS(func_020a125c, Activity_SetFlagD9)

/* func_020a1264 */
void Activity_SetFlagE6(Activity *activity, u8 value)
{
    activity->flag_e6 = value;
}
CLEAN_AS(func_020a1264, Activity_SetFlagE6)

/* func_020a126c */
void Activity_SetFlagE5(Activity *activity, u8 value)
{
    activity->flag_e5 = value;
}
CLEAN_AS(func_020a126c, Activity_SetFlagE5)

/* func_020a1274 */
void Activity_SetFlagE4(Activity *activity, u8 value)
{
    activity->flag_e4 = value;
}
CLEAN_AS(func_020a1274, Activity_SetFlagE4)

/* func_020a127c */
void Activity_SetByteD7(Activity *activity, u8 value)
{
    activity->byte_d7 = value;
}
CLEAN_AS(func_020a127c, Activity_SetByteD7)

/* func_020a1284 */
void Activity_SetSlotMask(Activity *activity, u16 mask)
{
    activity->slot_mask = mask;
}
CLEAN_AS(func_020a1284, Activity_SetSlotMask)

/* func_020a242c */
void Activity_SetSlot107(Activity *activity, int slot, char value)
{
    activity->slot_107[slot] = (u8) value;
}
CLEAN_AS(func_020a242c, Activity_SetSlot107)

/* func_020a2438 */
u8 Activity_Slot107(Activity *activity, int slot)
{
    return activity->slot_107[slot];
}
CLEAN_AS(func_020a2438, Activity_Slot107)

/* func_020a2444 */
void Activity_SetBlockSource(Activity *activity, int slot, u8 source)
{
    activity->block_source[slot] = source;
}
CLEAN_AS(func_020a2444, Activity_SetBlockSource)

/* func_020a2450 */
u8 Activity_BlockSource(const Activity *activity, int slot)
{
    return activity->block_source[slot];
}
CLEAN_AS(func_020a2450, Activity_BlockSource)

/* func_020a245c */
u8 Activity_Byte102(Activity *activity)
{
    return activity->byte_102;
}
CLEAN_AS(func_020a245c, Activity_Byte102)
