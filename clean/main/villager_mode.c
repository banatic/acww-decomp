/* The mode record of a villager (villager_mode.h). */
#include "villager_mode.h"

#include "clean.h"
#include "date_time.h"
#include "lookups.h"
#include "npc_id.h"
#include "villager_state.h"

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
extern NpcId *func_0208150c(const void *villager);                    /* the villager's NpcId, at 0x7a0 */
extern VillagerModeRecord *func_0207f1c8(const void *villager);       /* its mode record, at 0x734 */
extern VillagerModeRecord *func_0209b5ec(VillagerModeRecord *record); /* the record itself */
extern u8 *func_0209b5e8(VillagerModeRecord *record);                 /* the record's object, at 0x24 */
extern DateTime *func_0209bfec(VillagerModeRecord *record);           /* its date `since` */
extern DateTime *func_0209bfe8(VillagerModeRecord *record);           /* its date `counted` */
extern int func_0209c330(const VillagerModeRecord *record);           /* its mode */
extern void func_0209c32c(VillagerModeRecord *record, int mode);      /* sets it */
extern int func_0209c370(const VillagerModeRecord *record);           /* whether the mode is below 12 */
extern int func_0209c380(const VillagerModeRecord *record);           /* whether it is one of the eight kinds */
extern int func_0209c2c0(const VillagerModeRecord *record);           /* bit 0 of its flags */
extern int func_0209c38c(u32 mode);                                   /* whether a mode is one of the eight kinds */
extern u32 func_0209c310(u32 mode);                                   /* its group: 0 for 0-4, 1 for 5-7, 2 for 8-11, else 3 */
/* Mode 8 back to its mode drawn from the scores (func_0209c108), mode 10 once a day has passed
 * since `since` (func_0209c020), mode 11 once the day of the month differs (func_0209c0a0); each
 * gives the new mode (with `since` now and the scores halved) or 12. */
extern int func_0209c108(VillagerModeRecord *record);
extern int func_0209c020(VillagerModeRecord *record, const DateTime *now);
extern int func_0209c0a0(VillagerModeRecord *record, const DateTime *now);
/* A mode of the eight kinds kept when its score is still the highest, else the record back to
 * mode 8 (func_0209c270); gives the mode kept, 8, or 12. */
extern int func_0209c168(VillagerModeRecord *record);
extern void func_0209c270(VillagerModeRecord *record); /* back to mode 8 from now */
/* Whether the record's mode is one of the eight kinds and `since` is at least seven days from
 * `now`. */
extern int func_0209c1c0(const VillagerModeRecord *record, const DateTime *now);
/* A day's draw of the scores from the weights; 0 when no score could change. */
extern int func_0209bf28(VillagerModeRecord *record, const s16 *weights);
/* The counts, scaled by the weights, added into the scores; the counts cleared. */
extern void func_0209bf80(VillagerModeRecord *record, const s16 *weights);
/* `amount` added to the count of `kind`, kept within 0-10. */
extern void func_0209bee8(VillagerModeRecord *record, u32 kind, int amount);
/* The kind `from` scores highest gets a full score (10 times its weight) in `record`. */
extern void func_0209beb0(VillagerModeRecord *record, VillagerModeRecord *from, const s16 *weights);
extern const s16 *func_02080814(const void *villager); /* its weights, NULL for a number without data */
/* The villager's byte 0x7d8 drawn again (below 10 for mode 2, else below 40), and its two items
 * at 0x78e emptied for mode 2 or when `from_2` is set. */
extern void func_0207f414(u8 *villager, int mode, int from_2);
extern VillagerState *func_0207f270(const void *villager); /* its entry of the state table */
extern u8 *func_0209b91c(u8 *object);                      /* the object itself */
extern int func_0209bd44(const u8 *object);                /* whether it holds something */
extern int func_0209bd04(const u8 *object);                /* the group of its type */
extern int func_0209bba0(const u8 *object);                /* the low 5 bits of its byte 0x0b */
extern int func_0209bc40(const u8 *object);                /* its type, byte 0x0a */
extern void func_0209baf4(u8 *object);                     /* empties it */
extern void func_0209bd5c(u8 *object);                     /* type 22, no item */
extern void func_0209bd30(u8 *object, u8 type, const u16 *item, u8 low_bits);
extern const DayWindow *func_0208222c(u32 kind);                            /* Lookups_DayWindow */
extern int func_0209dffc(const DateTime *when);                             /* 1 when it is not a valid date and time */
extern int func_0209e3ac(const DateTime *a, const DateTime *b, int fields); /* DateTime_Compare */
extern int func_0209e350(const DateTime *from, const DateTime *to);         /* DateTime_MinutesBetween */
extern void func_0209e29c(DateTime *when, int days);                        /* DateTime_AddDays */

static int has_villager(const u8 *villager)
{
    return NpcId_IsValid(func_0208150c(villager));
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
    VillagerModeRecord *record = func_0207f1c8(villager);
    u8 *object = func_0209b5e8(record);
    u8 *held = func_0209b91c(object);
    if (func_0209bd44(held) == 0 || func_0209bd04(held) != VILLAGER_MODE_OBJECT_GROUP ||
        func_0209bba0(held) != VILLAGER_MODE_OBJECT_DONE) {
        return;
    }
    if (func_0209bc40(held) == VILLAGER_MODE_OBJECT_TYPE_4) {
        VillagerMode_StepCounter7D7(villager);
    }
    func_0209baf4(object);
    func_0209c270(func_0209b5ec(record));
}
CLEAN_AS(func_0207d71c, VillagerMode_FinishObject)

/* func_0207d788: the record's update with the time `now`. Mode 11 takes a new mode once the day
 * changed, and then `now` becomes the town's latest time, and the time a villager last left too
 * when that is set (not all zero). Mode 10 takes one a day after the villager moved in. Any
 * other mode goes through VillagerMode_UpdateDaily. A new mode redraws the villager's byte
 * 0x7d8 (func_0207f414). Gives the new mode, or 12. */
int VillagerMode_Update(u8 *villager, DateTime *latest, DateTime *last_left, const DateTime *now)
{
    NpcId *npc = func_0208150c(villager);
    VillagerModeRecord *record = func_0209b5ec(func_0207f1c8(villager));
    int result = VILLAGER_MODE_UNCHANGED;
    int from_2 = func_0209c2c0(record);
    if (!NpcId_IsValid(npc) || func_0209c370(record) == 0) {
        return result;
    }
    switch (func_0209c330(record)) {
        case VILLAGER_MODE_11:
            result = func_0209c0a0(record, now);
            if (result != VILLAGER_MODE_UNCHANGED) {
                func_0207f414(villager, result, from_2);
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
            result = func_0209c020(record, now);
            if (result != VILLAGER_MODE_UNCHANGED) {
                func_0207f414(villager, result, from_2);
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
    NpcId *npc = func_0208150c(villager);
    VillagerModeRecord *record = func_0209b5ec(func_0207f1c8(villager));
    int result = VILLAGER_MODE_UNCHANGED;
    int before = func_0209c330(record);
    if (!NpcId_IsValid(npc) || func_0209c370(record) == 0) {
        return result;
    }
    int from_2 = func_0209c2c0(record);
    if (func_0209c330(record) == VILLAGER_MODE_NONE_YET) {
        if (VillagerMode_IsWakeTimePast(villager, now)) {
            result = func_0209c108(record);
        }
    } else {
        VillagerMode_CatchUpScores(villager, now);
        result = func_0209c168(record);
    }
    if (result == VILLAGER_MODE_UNCHANGED) {
        return result;
    }
    if (func_0209c38c((u32) before) && before == result) {
        return result;
    }
    func_0209baf4(func_0209b5e8(func_0207f1c8(villager)));
    u8 *object = VillagerState_Object(func_0207f270(villager));
    func_0209bd5c(object);
    if (func_0209c310((u32) result) == 0) {
        u16 item = VILLAGER_MODE_NO_ITEM;
        func_0209bd30(object, (u8) result, &item, 0);
    }
    if (func_0209c38c((u32) result)) {
        func_0207f414(villager, result, from_2);
    }
    return result;
}
CLEAN_AS(func_0207d840, VillagerMode_UpdateDaily)

/* func_0207d91c: the record's `counted` set to `now` when it is not a valid date and time or
 * lies after `now` (the clock was set back). Only for a record in use. */
void VillagerMode_KeepCountedDate(u8 *villager, const DateTime *now)
{
    VillagerModeRecord *record = func_0209b5ec(func_0207f1c8(villager));
    if (!has_villager(villager) || func_0209c370(record) == 0) {
        return;
    }
    DateTime *counted = func_0209bfe8(record);
    if (func_0209dffc(counted) != 0 || func_0209e3ac(now, counted, VILLAGER_MODE_TO_SECOND) == -1) {
        MI_CpuCopy8(now, counted, sizeof(DateTime));
    }
}
CLEAN_AS(func_0207d91c, VillagerMode_KeepCountedDate)

/* func_0207d978: the same for the record's `since`. */
void VillagerMode_KeepSinceDate(u8 *villager, const DateTime *now)
{
    VillagerModeRecord *record = func_0209b5ec(func_0207f1c8(villager));
    if (!has_villager(villager) || func_0209c370(record) == 0) {
        return;
    }
    DateTime *since = func_0209bfec(record);
    if (func_0209dffc(since) != 0 || func_0209e3ac(now, since, VILLAGER_MODE_TO_SECOND) == -1) {
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
    VillagerModeRecord *record = func_0209b5ec(func_0207f1c8(villager));
    if (!has_villager(villager) || func_0209c370(record) == 0 || func_0209c380(record) == 0) {
        return;
    }
    DateTime *counted = func_0209bfe8(record);
    const s16 *weights = func_02080814(villager);
    if (func_0209dffc(counted) != 0 || weights == NULL) {
        return;
    }
    int days = whole_days(func_0209e350(counted, now));
    if (days <= 0) {
        return;
    }
    if (func_0209c1c0(record, now)) {
        DateTime from = {0};
        int draws = days;
        MI_CpuCopy8(func_0209bfec(record), &from, sizeof(DateTime));
        if (whole_days(func_0209e350(&from, counted)) < VILLAGER_MODE_SETTLE_DAYS) {
            func_0209e29c(&from, VILLAGER_MODE_SETTLE_OFFSET);
            draws = whole_days(func_0209e350(&from, now));
        }
        while (draws > 0 && func_0209bf28(record, weights) != 0) {
            draws--;
        }
        func_0209bf80(record, weights);
    }
    func_0209e29c(counted, days);
}
CLEAN_AS(func_0207d9d4, VillagerMode_CatchUpScores)

/* func_0207dac8: `amount` added to the villager's count of events of `kind` (0-10). */
void VillagerMode_AddCount(u8 *villager, int kind, int amount)
{
    if (has_villager(villager)) {
        func_0209bee8(func_0209b5ec(func_0207f1c8(villager)), (u32) kind, amount);
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
    const s16 *weights = func_02080814(villager);
    if (weights == NULL) {
        return;
    }
    VillagerModeRecord *record = func_0209b5ec(func_0207f1c8(villager));
    func_0209beb0(record, func_0209b5ec(func_0207f1c8(other)), weights);
}
CLEAN_AS(func_0207daf4, VillagerMode_LearnFrom)

/* func_0207db48: whether `now` (to the minute) is after the villager's wake time following
 * `since`: the end of its personality's night (Lookups_DayWindow) on the day of `since`, or on
 * the next day when `since` is past that hour.
 * QUIRK: within the hour of the wake time, the next day is taken only when `since` is at the
 * very minute of it; a later minute of that hour keeps the same day, already passed. */
int VillagerMode_IsWakeTimePast(u8 *villager, const DateTime *now)
{
    NpcId *npc = func_0208150c(villager);
    VillagerModeRecord *record = func_0209b5ec(func_0207f1c8(villager));
    if (!NpcId_IsValid(npc) || func_0209c370(record) == 0) {
        return 0;
    }
    const DayWindow *night = func_0208222c((u32) NpcId_Personality(npc));
    const DateTime *since = func_0209bfec(record);
    if (func_0209dffc(since) != 0) {
        return 0;
    }
    DateTime wake = {0};
    MI_CpuCopy8(since, &wake, sizeof(DateTime));
    wake.hour = night->end_hour;
    wake.minute = night->end_minute;
    if (since->hour > night->end_hour || (night->end_hour == since->hour && night->end_minute == since->minute)) {
        func_0209e29c(&wake, 1);
    }
    return func_0209e3ac(now, &wake, VILLAGER_MODE_TO_MINUTE) == 1;
}
CLEAN_AS(func_0207db48, VillagerMode_IsWakeTimePast)

/* func_0207dbe8: the villager just moved in: mode 10 from `now`, its object emptied. */
void VillagerMode_SetArrived(u8 *villager, const DateTime *now)
{
    if (!has_villager(villager)) {
        return;
    }
    VillagerModeRecord *record = func_0209b5ec(func_0207f1c8(villager));
    func_0209c32c(record, VILLAGER_MODE_ARRIVED);
    MI_CpuCopy8(now, func_0209bfec(record), sizeof(DateTime));
    func_0209baf4(func_0209b5e8(func_0207f1c8(villager)));
}
CLEAN_AS(func_0207dbe8, VillagerMode_SetArrived)

/* func_0207dc30: the villager is about to leave: mode 9 from `now`, its object emptied. The flag
 * of mode 2 is set when it leaves mode 2, or mode 8 with the flag already set. */
void VillagerMode_SetLeaving(u8 *villager, const DateTime *now)
{
    if (!has_villager(villager)) {
        return;
    }
    VillagerModeRecord *record = func_0209b5ec(func_0207f1c8(villager));
    if (func_0209c330(record) == 2 || (func_0209c330(record) == VILLAGER_MODE_NONE_YET && func_0209c2c0(record) != 0)) {
        record->flags |= VILLAGER_MODE_FROM_2;
    }
    func_0209c32c(record, VILLAGER_MODE_LEAVING);
    MI_CpuCopy8(now, func_0209bfec(record), sizeof(DateTime));
    func_0209baf4(func_0209b5e8(func_0207f1c8(villager)));
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
