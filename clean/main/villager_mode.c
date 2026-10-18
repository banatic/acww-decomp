/* The mode record of a villager (villager_mode.h). */
#include "villager_mode.h"

#include "clean.h"
#include "date_time.h"
#include "lookups.h"
#include "npc_id.h"
#include "villager_state.h"
#include "item_object.h"
#include "town_villager.h"
#include "villager_data.h"
#include "villager_furniture.h"
#include "villager_mode_record.h"
#include "villager_object.h"
#include "villager_status.h"

static_assert(sizeof(DateTime) == 8, "DateTime");
static_assert(offsetof(VillagerModeRecord, counted) == 0x08, "counted");
static_assert(offsetof(VillagerModeRecord, mode) == 0x10, "mode");
static_assert(offsetof(VillagerModeRecord, scores) == 0x11, "scores");
static_assert(offsetof(VillagerModeRecord, counts) == 0x19, "counts");
static_assert(offsetof(VillagerModeRecord, flags) == 0x21, "flags");

#define VILLAGER_MODE_COUNTER_7D7 0x7d7
#define VILLAGER_MODE_COUNTER_7D7_WRAP 6
#define VILLAGER_MODE_MINUTES_PER_DAY (24 * 60)
#define VILLAGER_MODE_TO_MINUTE (DATE_TIME_YEAR | DATE_TIME_MONTH | DATE_TIME_DAY | DATE_TIME_HOUR | DATE_TIME_MINUTE)
#define VILLAGER_MODE_TO_SECOND (VILLAGER_MODE_TO_MINUTE | DATE_TIME_SECOND)
/* VillagerMode_CatchUpScores: a mode set less than this many days before the counted day lets
 * the scores be drawn only from six days after it was set. */
#define VILLAGER_MODE_SETTLE_DAYS 7
#define VILLAGER_MODE_SETTLE_OFFSET 6
/* The object VillagerMode_FinishObject is done with: a type of group 0, at step 3 (the low 5
 * bits of its byte 0x0b); type 4 also steps the villager's number at 0x7d7. */
#define VILLAGER_MODE_OBJECT_GROUP 0
#define VILLAGER_MODE_OBJECT_DONE 3
#define VILLAGER_MODE_OBJECT_TYPE_4 4
/* The item an object of a group 0 type is set up with: none. */
#define VILLAGER_MODE_NO_ITEM 0xfff1

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

static int has_villager(const u8 *villager)
{
    return NpcId_IsValid(TownVillager_NpcId((u8 *) villager));
}

/* The whole days in a span of minutes, either way. The minutes between two valid dates are far
 * from overflowing when negated. */
static int whole_days(int minutes)
{
    if (minutes < 0) {
        minutes = -minutes;
    }
    return minutes / VILLAGER_MODE_MINUTES_PER_DAY;
}

/* func_0207d71c: when the villager's object holds a group 0 type at step 3, it is emptied and
 * the record goes back to mode 8; a type 4 also steps the villager's number at 0x7d7. */
void VillagerMode_FinishObject(u8 *villager)
{
    if (!has_villager(villager)) {
        return;
    }
    VillagerModeRecord *record = VillagerStatus_ModeRecord(villager);
    u8 *object = (u8 *) VillagerObject_OfRecord((VillagerRecord *) record);
    u8 *held = VillagerObject_Base((VillagerObject *) (void *) object);
    if (ItemObject_IsInUse((ItemObject *) (void *) held) == 0 ||
        ItemObject_Group((ItemObject *) (void *) held) != VILLAGER_MODE_OBJECT_GROUP ||
        ItemObject_Low5((ItemObject *) (void *) held) != VILLAGER_MODE_OBJECT_DONE) {
        return;
    }
    if (ItemObject_Type((ItemObject *) (void *) held) == VILLAGER_MODE_OBJECT_TYPE_4) {
        VillagerMode_StepCounter7D7(villager);
    }
    VillagerObject_Clear((VillagerObject *) (void *) object);
    VillagerModeRecord_EnterNoneYet(VillagerObject_RecordMode((VillagerRecord *) record));
}
CLEAN_AS(func_0207d71c, VillagerMode_FinishObject)

/* func_0207d788: the record's update with the time `now`. Mode 11 takes a new mode once the day
 * changed, and then `now` becomes the town's latest time, and the time a villager last left too
 * when that is set (not all zero). Mode 10 takes one a day after the villager moved in. Any
 * other mode goes through VillagerMode_UpdateDaily. A new mode redraws the villager's byte
 * 0x7d8 (func_0207f414). Gives the new mode, or 12. */
int VillagerMode_Update(u8 *villager, DateTime *latest, DateTime *last_left, const DateTime *now)
{
    NpcId *npc = TownVillager_NpcId(villager);
    VillagerModeRecord *record = VillagerObject_RecordMode((VillagerRecord *) VillagerStatus_ModeRecord(villager));
    int result = VILLAGER_MODE_UNCHANGED;
    int from_2 = VillagerModeRecord_IsFrom2(record);
    if (!NpcId_IsValid(npc) || VillagerModeRecord_IsInUse(record) == 0) {
        return result;
    }
    switch (VillagerModeRecord_Mode(record)) {
        case VILLAGER_MODE_11:
            result = VillagerModeRecord_LeaveMode11(record, now);
            if (result != VILLAGER_MODE_UNCHANGED) {
                VillagerFurniture_ResetForMode(villager, result, from_2);
                MI_CpuCopy8(now, latest, sizeof(DateTime));
                const u8 *left = (const u8 *) last_left;
                int set = 0;
                for (u32 i = 0; i < sizeof(DateTime); i++) {
                    set |= left[i];
                }
                if (set) {
                    MI_CpuCopy8(now, last_left, sizeof(DateTime));
                }
            }
            break;
        case VILLAGER_MODE_ARRIVED:
            result = VillagerModeRecord_LeaveArrived(record, now);
            if (result != VILLAGER_MODE_UNCHANGED) {
                VillagerFurniture_ResetForMode(villager, result, from_2);
            }
            break;
        default:
            result = VillagerMode_UpdateDaily(villager, now);
            break;
    }
    return result;
}
CLEAN_AS(func_0207d788, VillagerMode_Update)

/* func_0207d840: a mode 8 record takes a mode drawn from its scores once the villager's wake
 * time after `since` has passed; any other mode first has its scores caught up to `now` and is
 * kept while its score is still the highest, else goes back to mode 8. When the mode changed
 * (and is not the same kind again), the villager's object is emptied and its state entry's
 * object set up afresh: with the new mode as its type and no item when that is one of kinds 0-4.
 * A new kind (0-7) redraws the villager's byte 0x7d8 (func_0207f414). Gives the new mode, or 12. */
int VillagerMode_UpdateDaily(u8 *villager, const DateTime *now)
{
    NpcId *npc = TownVillager_NpcId(villager);
    VillagerModeRecord *record = VillagerObject_RecordMode((VillagerRecord *) VillagerStatus_ModeRecord(villager));
    int result = VILLAGER_MODE_UNCHANGED;
    int before = VillagerModeRecord_Mode(record);
    if (!NpcId_IsValid(npc) || VillagerModeRecord_IsInUse(record) == 0) {
        return result;
    }
    int from_2 = VillagerModeRecord_IsFrom2(record);
    if (VillagerModeRecord_Mode(record) == VILLAGER_MODE_NONE_YET) {
        if (VillagerMode_IsWakeTimePast(villager, now)) {
            result = VillagerModeRecord_LeaveNoneYet(record);
        }
    } else {
        VillagerMode_CatchUpScores(villager, now);
        result = VillagerModeRecord_KeepKind(record);
    }
    if (result == VILLAGER_MODE_UNCHANGED) {
        return result;
    }
    if (VillagerModeRecord_IsKindMode((u32) before) && before == result) {
        return result;
    }
    VillagerObject_Clear(VillagerObject_OfRecord((VillagerRecord *) VillagerStatus_ModeRecord(villager)));
    u8 *object = VillagerState_Object(VillagerStatus_StateEntry(villager));
    ItemObject_Clear((ItemObject *) (void *) object);
    if (VillagerModeRecord_GroupOfMode((u32) result) == 0) {
        u16 item = VILLAGER_MODE_NO_ITEM;
        ItemObject_Set((ItemObject *) (void *) object, (u8) result, &item, 0);
    }
    if (VillagerModeRecord_IsKindMode((u32) result)) {
        VillagerFurniture_ResetForMode(villager, result, from_2);
    }
    return result;
}
CLEAN_AS(func_0207d840, VillagerMode_UpdateDaily)

/* func_0207d91c: the record's `counted` set to `now` when it is not a valid date and time or
 * lies after `now` (the clock was set back). Only for a record in use. */
void VillagerMode_KeepCountedDate(u8 *villager, const DateTime *now)
{
    VillagerModeRecord *record = VillagerObject_RecordMode((VillagerRecord *) VillagerStatus_ModeRecord(villager));
    if (!has_villager(villager) || VillagerModeRecord_IsInUse(record) == 0) {
        return;
    }
    DateTime *counted = VillagerModeRecord_Counted(record);
    if (DateTime_IsInvalid(counted) != 0 || DateTime_Compare(now, counted, VILLAGER_MODE_TO_SECOND) == -1) {
        MI_CpuCopy8(now, counted, sizeof(DateTime));
    }
}
CLEAN_AS(func_0207d91c, VillagerMode_KeepCountedDate)

/* func_0207d978: the same for the record's `since`. */
void VillagerMode_KeepSinceDate(u8 *villager, const DateTime *now)
{
    VillagerModeRecord *record = VillagerObject_RecordMode((VillagerRecord *) VillagerStatus_ModeRecord(villager));
    if (!has_villager(villager) || VillagerModeRecord_IsInUse(record) == 0) {
        return;
    }
    DateTime *since = VillagerModeRecord_Since(record);
    if (DateTime_IsInvalid(since) != 0 || DateTime_Compare(now, since, VILLAGER_MODE_TO_SECOND) == -1) {
        MI_CpuCopy8(now, since, sizeof(DateTime));
    }
}
CLEAN_AS(func_0207d978, VillagerMode_KeepSinceDate)

/* func_0207d9d4: for a record in one of the eight kinds with a valid `counted` and a villager
 * with weights, the whole days from `counted` to `now` are taken into the scores. When the mode
 * was set at least seven days before `now`, the scores are drawn once a day (stopping early
 * when nothing could change), from the day six days after `since` when `since` is less than
 * seven days before `counted`, and the counts are then added in. `counted` moves on by the days
 * either way. */
void VillagerMode_CatchUpScores(u8 *villager, const DateTime *now)
{
    VillagerModeRecord *record = VillagerObject_RecordMode((VillagerRecord *) VillagerStatus_ModeRecord(villager));
    if (!has_villager(villager) || VillagerModeRecord_IsInUse(record) == 0 || VillagerModeRecord_IsKind(record) == 0) {
        return;
    }
    DateTime *counted = VillagerModeRecord_Counted(record);
    const s16 *weights = VillagerData_ModeWeights(villager);
    if (DateTime_IsInvalid(counted) != 0 || weights == NULL) {
        return;
    }
    int days = whole_days(DateTime_MinutesBetween(counted, now));
    if (days <= 0) {
        return;
    }
    if (VillagerModeRecord_IsKindAWeekOld(record, now)) {
        DateTime from = {0};
        int draws = days;
        MI_CpuCopy8(VillagerModeRecord_Since(record), &from, sizeof(DateTime));
        if (whole_days(DateTime_MinutesBetween(&from, counted)) < VILLAGER_MODE_SETTLE_DAYS) {
            DateTime_AddDays(&from, VILLAGER_MODE_SETTLE_OFFSET);
            draws = whole_days(DateTime_MinutesBetween(&from, now));
        }
        while (draws > 0 && VillagerModeRecord_DrawScores(record, weights) != 0) {
            draws--;
        }
        VillagerModeRecord_AddCountsToScores(record, weights);
    }
    DateTime_AddDays(counted, days);
}
CLEAN_AS(func_0207d9d4, VillagerMode_CatchUpScores)

/* func_0207dac8: `amount` added to the villager's count of events of `kind` (0-10). */
void VillagerMode_AddCount(u8 *villager, int kind, int amount)
{
    if (has_villager(villager)) {
        VillagerModeRecord_AddCount(VillagerObject_RecordMode((VillagerRecord *) VillagerStatus_ModeRecord(villager)),
                                    (u32) kind, amount);
    }
}
CLEAN_AS(func_0207dac8, VillagerMode_AddCount)

/* func_0207daf4: the villager takes on the kind `other` scores highest, with a full score.
 * Nothing unless both are villagers and the first has weights. */
void VillagerMode_LearnFrom(u8 *villager, u8 *other)
{
    if (!has_villager(villager) || !has_villager(other)) {
        return;
    }
    const s16 *weights = VillagerData_ModeWeights(villager);
    if (weights == NULL) {
        return;
    }
    VillagerModeRecord *record = VillagerObject_RecordMode((VillagerRecord *) VillagerStatus_ModeRecord(villager));
    VillagerModeRecord_LearnTop(record, VillagerObject_RecordMode((VillagerRecord *) VillagerStatus_ModeRecord(other)),
                                weights);
}
CLEAN_AS(func_0207daf4, VillagerMode_LearnFrom)

/* func_0207db48: whether `now` (to the minute) is after the villager's wake time following
 * `since`: the end of its personality's night (Lookups_DayWindow) on the day of `since`, or on
 * the next day when `since` is past that hour.
 * QUIRK: within the hour of the wake time, the next day is taken only when `since` is at the
 * very minute of it; a later minute of that hour keeps the same day, already passed. */
int VillagerMode_IsWakeTimePast(u8 *villager, const DateTime *now)
{
    NpcId *npc = TownVillager_NpcId(villager);
    VillagerModeRecord *record = VillagerObject_RecordMode((VillagerRecord *) VillagerStatus_ModeRecord(villager));
    if (!NpcId_IsValid(npc) || VillagerModeRecord_IsInUse(record) == 0) {
        return 0;
    }
    const DayWindow *night = Lookups_DayWindow((u32) NpcId_Personality(npc));
    const DateTime *since = VillagerModeRecord_Since(record);
    if (DateTime_IsInvalid(since) != 0) {
        return 0;
    }
    DateTime wake = {0};
    MI_CpuCopy8(since, &wake, sizeof(DateTime));
    wake.hour = night->end_hour;
    wake.minute = night->end_minute;
    if (since->hour > night->end_hour || (night->end_hour == since->hour && night->end_minute == since->minute)) {
        DateTime_AddDays(&wake, 1);
    }
    return DateTime_Compare(now, &wake, VILLAGER_MODE_TO_MINUTE) == 1;
}
CLEAN_AS(func_0207db48, VillagerMode_IsWakeTimePast)

/* func_0207dbe8: the villager just moved in: mode 10 from `now`, its object emptied. */
void VillagerMode_SetArrived(u8 *villager, const DateTime *now)
{
    if (!has_villager(villager)) {
        return;
    }
    VillagerModeRecord *record = VillagerObject_RecordMode((VillagerRecord *) VillagerStatus_ModeRecord(villager));
    VillagerModeRecord_SetMode(record, VILLAGER_MODE_ARRIVED);
    MI_CpuCopy8(now, VillagerModeRecord_Since(record), sizeof(DateTime));
    VillagerObject_Clear(VillagerObject_OfRecord((VillagerRecord *) VillagerStatus_ModeRecord(villager)));
}
CLEAN_AS(func_0207dbe8, VillagerMode_SetArrived)

/* func_0207dc30: the villager is about to leave: mode 9 from `now`, its object emptied. The flag
 * of mode 2 is set when it leaves mode 2, or mode 8 with the flag already set. */
void VillagerMode_SetLeaving(u8 *villager, const DateTime *now)
{
    if (!has_villager(villager)) {
        return;
    }
    VillagerModeRecord *record = VillagerObject_RecordMode((VillagerRecord *) VillagerStatus_ModeRecord(villager));
    if (VillagerModeRecord_Mode(record) == 2 ||
        (VillagerModeRecord_Mode(record) == VILLAGER_MODE_NONE_YET && VillagerModeRecord_IsFrom2(record) != 0)) {
        record->flags |= VILLAGER_MODE_FROM_2;
    }
    VillagerModeRecord_SetMode(record, VILLAGER_MODE_LEAVING);
    MI_CpuCopy8(now, VillagerModeRecord_Since(record), sizeof(DateTime));
    VillagerObject_Clear(VillagerObject_OfRecord((VillagerRecord *) VillagerStatus_ModeRecord(villager)));
}
CLEAN_AS(func_0207dc30, VillagerMode_SetLeaving)

/* func_0207dcf4: the villager's number at 0x7d7 steps on, 5 back to 0. */
void VillagerMode_StepCounter7D7(u8 *villager)
{
    u8 *counter = villager + VILLAGER_MODE_COUNTER_7D7;
    *counter += 1;
    if (*counter >= VILLAGER_MODE_COUNTER_7D7_WRAP) {
        *counter = 0;
    }
}
CLEAN_AS(func_0207dcf4, VillagerMode_StepCounter7D7)

/* func_0207dd10: the villager's number at 0x7d7. */
u8 VillagerMode_Counter7D7(u8 *villager)
{
    return villager[VILLAGER_MODE_COUNTER_7D7];
}
CLEAN_AS(func_0207dd10, VillagerMode_Counter7D7)
