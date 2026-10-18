/* A villager's mode record (villager_mode_record.h). */
#include "villager_mode_record.h"

#include "clean.h"
#include "date_time.h"
#include "main_random.h"
#include "message_reader.h"

#define VILLAGER_MODE_RECORD_MINUTES_PER_DAY (24 * 60)
/* The fields func_0209e3ac compares: all six of a DateTime. */
#define VILLAGER_MODE_RECORD_ALL_FIELDS 0x3f
#define VILLAGER_MODE_RECORD_WEEK 7
/* The kind VillagerModeRecord_LoadKindText shows for a mode that is not a kind. */
#define VILLAGER_MODE_RECORD_TEXT_OTHER 7
/* A full score: ten times the weight. */
#define VILLAGER_MODE_RECORD_FULL_SCORE 10
#define VILLAGER_MODE_RECORD_DRAW_RANGE 10
#define VILLAGER_MODE_RECORD_FIXED_SHIFT 12
#define VILLAGER_MODE_RECORD_GROUPS 3
#define VILLAGER_MODE_RECORD_MODE_2 2

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void __register_global_object(void *object, void *destruct, void *record);
extern void func_020051b0(void *item); /* an item code's destructor: nothing */

/* The item of each kind, built on the first call, with its guard and the records of its eight
 * registrations for destruction. */
extern u32 data_021dc50c;
extern u16 data_021dc570[VILLAGER_MODE_KINDS];
extern u8 data_021dc510[12], data_021dc51c[12], data_021dc528[12], data_021dc534[12], data_021dc540[12], data_021dc54c[12],
    data_021dc558[12], data_021dc564[12];
/* What each count is multiplied by on its way into the score (3, 3, 5, 5, 3, 3, 2, 1). */
extern const u8 data_020d1a38[VILLAGER_MODE_KINDS];
/* The first mode of groups 0-2. */
extern const u8 data_020d1a20[VILLAGER_MODE_RECORD_GROUPS];
extern const char data_020e35cc[]; /* "st_boom" */

/* The item each kind is shown with (none for kinds 3, 4, 6 and 7). */
static const u16 villager_mode_record_kind_items[VILLAGER_MODE_KINDS] = {
    0x1376, 0x1374, 0x1369, 0xfff1, 0xfff1, 0x1378, 0xfff1, 0xfff1,
};

/* func_0209bd98: the item kind `kind` is shown with; none (0xfff1) for a mode that is not a kind.
 * QUIRK: the items are a function-local static table, built and registered for destruction
 * (func_020051b0, which does nothing) one item at a time on the first call. */
void VillagerModeRecord_KindItem(u16 *out, int kind)
{
    u8 *const records[VILLAGER_MODE_KINDS] = {
        data_021dc510, data_021dc51c, data_021dc528, data_021dc534, data_021dc540, data_021dc54c, data_021dc558, data_021dc564,
    };
    if ((data_021dc50c & 1) == 0) {
        for (int i = 0; i < VILLAGER_MODE_KINDS; i++) {
            data_021dc570[i] = villager_mode_record_kind_items[i];
            __register_global_object(&data_021dc570[i], (void *) func_020051b0, records[i]);
        }
        data_021dc50c |= 1;
    }
    if (VillagerModeRecord_IsKindMode((u32) kind)) {
        *out = data_021dc570[kind];
    } else {
        *out = 0xfff1;
    }
}
CLEAN_AS(func_0209bd98, VillagerModeRecord_KindItem)

/* func_0209beb0: the kind `from` scores highest (one of them at random) gets a full score in
 * `record`: ten times its weight (4.12 fixed point), as a byte, added to its score. */
void VillagerModeRecord_LearnTop(VillagerModeRecord *record, const VillagerModeRecord *from, const s16 *weights)
{
    int kind = VillagerModeRecord_DrawTopKind(from->scores);
    if (VillagerModeRecord_IsKindMode((u32) kind)) {
        int full = (weights[kind] * VILLAGER_MODE_RECORD_FULL_SCORE) >> VILLAGER_MODE_RECORD_FIXED_SHIFT;
        VillagerModeRecord_RaiseScore(record->scores, kind, (u8) full);
    }
}
CLEAN_AS(func_0209beb0, VillagerModeRecord_LearnTop)

/* func_0209bee8: `amount` added to the count of `kind`, kept within 0-10. */
void VillagerModeRecord_AddCount(VillagerModeRecord *record, u32 kind, int amount)
{
    if (!VillagerModeRecord_IsKindMode(kind)) {
        return;
    }
    int count = amount + VillagerModeRecord_KindByte(record->counts, (u8) kind);
    if (count < 0) {
        count = 0;
    } else if (count > VILLAGER_MODE_RECORD_COUNT_MAX) {
        count = VILLAGER_MODE_RECORD_COUNT_MAX;
    }
    VillagerModeRecord_SetKindByte((char *) record->counts, (int) kind, (u8) count);
}
CLEAN_AS(func_0209bee8, VillagerModeRecord_AddCount)

/* func_0209bf28: a day's draw of the scores: each score below 255 gets its weight times a
 * random number below 10 (4.12 fixed point, as a byte). Whether any score was below 255. */
int VillagerModeRecord_DrawScores(VillagerModeRecord *record, const s16 *weights)
{
    int any = 0;
    for (int kind = 0; kind < VILLAGER_MODE_KINDS; kind++) {
        if (VillagerModeRecord_KindByte(record->scores, (u8) kind) >= VILLAGER_MODE_RECORD_SCORE_MAX) {
            continue;
        }
        int draw = (int) MainRandom_Below(VILLAGER_MODE_RECORD_DRAW_RANGE);
        if (draw > 0) {
            VillagerModeRecord_RaiseScore(record->scores, kind,
                                          (u8) ((weights[kind] * draw) >> VILLAGER_MODE_RECORD_FIXED_SHIFT));
        }
        any = 1;
    }
    return any;
}
CLEAN_AS(func_0209bf28, VillagerModeRecord_DrawScores)

/* func_0209bf80: each count, times the kind's weight and multiplier (4.12 fixed point, as a
 * byte), added to the kind's score; then the counts cleared. */
void VillagerModeRecord_AddCountsToScores(VillagerModeRecord *record, const s16 *weights)
{
    for (int kind = 0; kind < VILLAGER_MODE_KINDS; kind++) {
        int count = VillagerModeRecord_KindByte(record->counts, (u8) kind);
        int multiplier = data_020d1a38[kind];
        if (multiplier != 0 && count != 0) {
            int gain = (weights[kind] * multiplier * count) >> VILLAGER_MODE_RECORD_FIXED_SHIFT;
            VillagerModeRecord_RaiseScore(record->scores, kind, (u8) gain);
        }
    }
    VillagerModeRecord_ClearKindBytes(record->counts);
}
CLEAN_AS(func_0209bf80, VillagerModeRecord_AddCountsToScores)

/* func_0209bfe8 */
DateTime *VillagerModeRecord_Counted(VillagerModeRecord *record)
{
    return &record->counted;
}
CLEAN_AS(func_0209bfe8, VillagerModeRecord_Counted)

/* func_0209bfec: the date the mode was set, at the start of the record. */
DateTime *VillagerModeRecord_Since(VillagerModeRecord *record)
{
    return &record->since;
}
CLEAN_AS(func_0209bfec, VillagerModeRecord_Since)

/* func_0209bff0: `text` loaded with the message of kind `mode` from the archive "st_boom"
 * (message 7 for a mode that is not a kind). */
int VillagerModeRecord_LoadKindText(void *text, int mode)
{
    u8 message = (u8) (VillagerModeRecord_IsKindMode((u32) mode) ? mode : VILLAGER_MODE_RECORD_TEXT_OTHER);
    return MessageReader_LoadMessage((int) (uintptr_t) text, &message, (int) (uintptr_t) data_020e35cc);
}
CLEAN_AS(func_0209bff0, VillagerModeRecord_LoadKindText)

/* The move to kind `kind` drawn from the scores: the mode set, the kind's score cleared and all
 * the scores halved, bit 0 of the flags cleared, and both dates set to now. */
static void villager_mode_record_take_kind(VillagerModeRecord *record, int kind)
{
    VillagerModeRecord_SetMode(record, kind);
    VillagerModeRecord_HalveScores(record->scores, (u8) kind);
    record->flags &= (u8) ~VILLAGER_MODE_FROM_2;
    DateTime_Now(&record->since);
    MI_CpuCopy8(&record->since, &record->counted, sizeof(DateTime));
}

/* func_0209c020: a record in mode 10 (just moved in) takes the kind it scores highest once
 * `now` is after the date it was set and a day or more from it (at once when `now` is NULL).
 * The new mode, or 12 when nothing changed. */
int VillagerModeRecord_LeaveArrived(VillagerModeRecord *record, const DateTime *now)
{
    if (record->mode != VILLAGER_MODE_ARRIVED) {
        return VILLAGER_MODE_UNCHANGED;
    }
    if (now != NULL && (DateTime_Compare(now, &record->since, VILLAGER_MODE_RECORD_ALL_FIELDS) != 1 ||
                        DateTime_DaysBetween(&record->since, now) < 1)) {
        return VILLAGER_MODE_UNCHANGED;
    }
    int kind = VillagerModeRecord_DrawTopKind(record->scores);
    if (!VillagerModeRecord_IsKindMode((u32) kind)) {
        return VILLAGER_MODE_UNCHANGED;
    }
    villager_mode_record_take_kind(record, kind);
    return kind;
}
CLEAN_AS(func_0209c020, VillagerModeRecord_LeaveArrived)

/* func_0209c0a0: a record in mode 11 takes the kind it scores highest once the day of the month
 * of `now` differs from the day it was set. The new mode, or 12. */
int VillagerModeRecord_LeaveMode11(VillagerModeRecord *record, const DateTime *now)
{
    if (record->mode != VILLAGER_MODE_11 || now->day == record->since.day) {
        return VILLAGER_MODE_UNCHANGED;
    }
    int kind = VillagerModeRecord_DrawTopKind(record->scores);
    if (!VillagerModeRecord_IsKindMode((u32) kind)) {
        return VILLAGER_MODE_UNCHANGED;
    }
    villager_mode_record_take_kind(record, kind);
    return kind;
}
CLEAN_AS(func_0209c0a0, VillagerModeRecord_LeaveMode11)

/* func_0209c108: a record in mode 8 (none yet) takes the kind it scores highest. The new mode,
 * or 12. */
int VillagerModeRecord_LeaveNoneYet(VillagerModeRecord *record)
{
    if (record->mode != VILLAGER_MODE_NONE_YET) {
        return VILLAGER_MODE_UNCHANGED;
    }
    int kind = VillagerModeRecord_DrawTopKind(record->scores);
    if (!VillagerModeRecord_IsKindMode((u32) kind)) {
        return VILLAGER_MODE_UNCHANGED;
    }
    villager_mode_record_take_kind(record, kind);
    return kind;
}
CLEAN_AS(func_0209c108, VillagerModeRecord_LeaveNoneYet)

/* func_0209c168: a record whose mode is a kind, once a highest score has reached 255: the mode
 * kept when it is that kind (its score cleared, the scores halved; the mode given), else the
 * record back to mode 8 (8 given). 12 when nothing changed. */
int VillagerModeRecord_KeepKind(VillagerModeRecord *record)
{
    if (!VillagerModeRecord_IsKindMode(record->mode)) {
        return VILLAGER_MODE_UNCHANGED;
    }
    int kind = VillagerModeRecord_DrawTopKind(record->scores);
    if (!VillagerModeRecord_IsKindMode((u32) kind) ||
        VillagerModeRecord_KindByte(record->scores, (u8) kind) != VILLAGER_MODE_RECORD_SCORE_MAX) {
        return VILLAGER_MODE_UNCHANGED;
    }
    if (record->mode != kind) {
        VillagerModeRecord_EnterNoneYet(record);
        return VILLAGER_MODE_NONE_YET;
    }
    VillagerModeRecord_HalveScores(record->scores, record->mode);
    return record->mode;
}
CLEAN_AS(func_0209c168, VillagerModeRecord_KeepKind)

/* func_0209c1c0: VillagerModeRecord_IsKindDaysOld for seven days. */
int VillagerModeRecord_IsKindAWeekOld(VillagerModeRecord *record, const DateTime *now)
{
    return VillagerModeRecord_IsKindDaysOld(record, now, VILLAGER_MODE_RECORD_WEEK);
}
CLEAN_AS(func_0209c1c0, VillagerModeRecord_IsKindAWeekOld)

/* func_0209c1cc: whether the record has a valid date, its mode is a kind, and `now` is `days`
 * whole days or more from that date (either way). */
int VillagerModeRecord_IsKindDaysOld(VillagerModeRecord *record, const DateTime *now, u32 days)
{
    if (DateTime_IsInvalid(&record->since) != 0 || VillagerModeRecord_IsKind(record) == 0) {
        return 0;
    }
    int minutes = DateTime_MinutesBetween(&record->since, now);
    if (minutes < 0) {
        minutes = -minutes;
    }
    /* The whole days, compared as unsigned. */
    return (u32) (minutes / VILLAGER_MODE_RECORD_MINUTES_PER_DAY) >= days;
}
CLEAN_AS(func_0209c1cc, VillagerModeRecord_IsKindDaysOld)

/* func_0209c214: the record to mode 11 from now; bit 0 of the flags set when it leaves mode 2
 * or the bit was set, else cleared. */
void VillagerModeRecord_EnterMode11(VillagerModeRecord *record)
{
    if (VillagerModeRecord_Mode(record) == VILLAGER_MODE_RECORD_MODE_2 || VillagerModeRecord_IsFrom2(record) != 0) {
        record->flags |= VILLAGER_MODE_FROM_2;
    } else {
        record->flags &= (u8) ~VILLAGER_MODE_FROM_2;
    }
    VillagerModeRecord_SetMode(record, VILLAGER_MODE_11);
    DateTime_Now(&record->since);
    MI_CpuCopy8(&record->since, &record->counted, sizeof(DateTime));
}
CLEAN_AS(func_0209c214, VillagerModeRecord_EnterMode11)

/* func_0209c270: the record to mode 8 (none yet) from now; bit 0 of the flags set when it leaves
 * mode 2, else cleared. */
void VillagerModeRecord_EnterNoneYet(VillagerModeRecord *record)
{
    if (VillagerModeRecord_Mode(record) == VILLAGER_MODE_RECORD_MODE_2) {
        record->flags |= VILLAGER_MODE_FROM_2;
    } else {
        record->flags &= (u8) ~VILLAGER_MODE_FROM_2;
    }
    VillagerModeRecord_SetMode(record, VILLAGER_MODE_NONE_YET);
    DateTime_Now(&record->since);
    MI_CpuCopy8(&record->since, &record->counted, sizeof(DateTime));
}
CLEAN_AS(func_0209c270, VillagerModeRecord_EnterNoneYet)

/* func_0209c2c0: bit 0 of the flags. */
int VillagerModeRecord_IsFrom2(VillagerModeRecord *record)
{
    return (record->flags & VILLAGER_MODE_FROM_2) != 0;
}
CLEAN_AS(func_0209c2c0, VillagerModeRecord_IsFrom2)

/* func_0209c2d4: the group of `mode` written to `*group`, and the mode's place within it (-1 for
 * group 3). */
int VillagerModeRecord_PlaceInGroup(u8 *group, u8 mode)
{
    *group = (u8) VillagerModeRecord_GroupOfMode(mode);
    if (*group >= VILLAGER_MODE_RECORD_GROUPS) {
        return -1;
    }
    return mode - data_020d1a20[*group];
}
CLEAN_AS(func_0209c2d4, VillagerModeRecord_PlaceInGroup)

/* func_0209c304 */
u32 VillagerModeRecord_Group(VillagerModeRecord *record)
{
    return VillagerModeRecord_GroupOfMode(record->mode);
}
CLEAN_AS(func_0209c304, VillagerModeRecord_Group)

/* func_0209c310: 0 for modes 0-4, 1 for 5-7, 2 for 8-11, 3 for the others. */
u32 VillagerModeRecord_GroupOfMode(u32 mode)
{
    if (mode < 5) {
        return 0;
    }
    if (mode < 8) {
        return 1;
    }
    if (mode < 12) {
        return 2;
    }
    return 3;
}
CLEAN_AS(func_0209c310, VillagerModeRecord_GroupOfMode)

/* func_0209c32c */
void VillagerModeRecord_SetMode(VillagerModeRecord *record, int mode)
{
    record->mode = (u8) mode;
}
CLEAN_AS(func_0209c32c, VillagerModeRecord_SetMode)

/* func_0209c330 */
int VillagerModeRecord_Mode(VillagerModeRecord *record)
{
    return record->mode;
}
CLEAN_AS(func_0209c330, VillagerModeRecord_Mode)

/* The mode an emptied record (VillagerModeRecord_Init) starts with: kind 7. */
#define VILLAGER_MODE_RECORD_INIT_MODE 7

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* func_0209c334: a new mode drawn for the record: its scores copied from `scores`, its mode one
 * of the highest of them (VillagerModeRecord_DrawTopKind), then, when `halve` is set, that
 * kind's score cleared and every score halved; both dates set to now. */
void VillagerModeRecord_Redraw(VillagerModeRecord *record, const u8 *scores, int halve)
{
    VillagerModeRecord_CopyKindBytes(record->scores, scores);
    record->mode = (u8) VillagerModeRecord_DrawTopKind(record->scores);
    if (halve) {
        VillagerModeRecord_HalveScores(record->scores, record->mode);
    }
    DateTime_Now(&record->since);
    DateTime_Now(&record->counted);
}
CLEAN_AS(func_0209c334, VillagerModeRecord_Redraw)

/* func_0209c370: whether the record is in use (its mode below VILLAGER_MODE_UNCHANGED). */
unsigned int VillagerModeRecord_IsInUse(VillagerModeRecord *record)
{
    return record->mode < VILLAGER_MODE_UNCHANGED;
}
CLEAN_AS(func_0209c370, VillagerModeRecord_IsInUse)

/* func_0209c380: whether the record's mode is one of the eight kinds. */
int VillagerModeRecord_IsKind(VillagerModeRecord *record)
{
    return VillagerModeRecord_IsKindMode(record->mode);
}
CLEAN_AS(func_0209c380, VillagerModeRecord_IsKind)

/* func_0209c38c: whether `mode` is one of the eight kinds. */
int VillagerModeRecord_IsKindMode(unsigned int mode)
{
    return mode < VILLAGER_MODE_KINDS;
}
CLEAN_AS(func_0209c38c, VillagerModeRecord_IsKindMode)

/* func_0209c398: the record emptied: all zero but its mode, which is kind 7, with its scores and
 * counts cleared once more and its dates zeroed. */
void VillagerModeRecord_Init(VillagerModeRecord *record)
{
    MI_CpuFill8(record, 0, sizeof(VillagerModeRecord));
    record->mode = VILLAGER_MODE_RECORD_INIT_MODE;
    VillagerModeRecord_ClearKindBytes(record->scores);
    VillagerModeRecord_ClearKindBytes(record->counts);
    record->since = (DateTime){0};
    record->counted = (DateTime){0};
}
CLEAN_AS(func_0209c398, VillagerModeRecord_Init)

/* func_0209c3c8: the record's destructor (its counts and scores need nothing). */
VillagerModeRecord *VillagerModeRecord_Destruct(VillagerModeRecord *record)
{
    VillagerModeRecord_DestructKindBytes(record->counts);
    VillagerModeRecord_DestructKindBytes(record->scores);
    return record;
}
CLEAN_AS(func_0209c3c8, VillagerModeRecord_Destruct)

/* func_0209c3e4: the record's constructor: dates zeroed, scores and counts constructed (cleared),
 * then emptied (VillagerModeRecord_Init). */
VillagerModeRecord *VillagerModeRecord_Construct(VillagerModeRecord *record)
{
    record->since = (DateTime){0};
    record->counted = (DateTime){0};
    VillagerModeRecord_ConstructKindBytes(record->scores);
    VillagerModeRecord_ConstructKindBytes(record->counts);
    VillagerModeRecord_Init(record);
    return record;
}
CLEAN_AS(func_0209c3e4, VillagerModeRecord_Construct)

/* func_0209c410: the byte of kind `kind` in eight bytes of a kind each; 0 for an index that is
 * not a kind. */
int VillagerModeRecord_KindByte(unsigned char *bytes, unsigned char kind)
{
    if (VillagerModeRecord_IsKindMode(kind)) {
        return bytes[kind];
    }
    return 0;
}
CLEAN_AS(func_0209c410, VillagerModeRecord_KindByte)

/* func_0209c42c: the byte of kind `kind` set; nothing for an index that is not a kind. */
void VillagerModeRecord_SetKindByte(char *bytes, int kind, char value)
{
    if (VillagerModeRecord_IsKindMode((unsigned int) kind)) {
        bytes[kind] = value;
    }
}
CLEAN_AS(func_0209c42c, VillagerModeRecord_SetKindByte)

/* func_0209c448: the score of kind `kind` raised by `delta`, up to VILLAGER_MODE_RECORD_SCORE_MAX.
 * QUIRK: only the top is clamped: a negative sum is stored as its low byte. */
void VillagerModeRecord_RaiseScore(unsigned char *scores, int kind, int delta)
{
    if (VillagerModeRecord_IsKindMode((unsigned int) kind)) {
        int score = (int) ((u32) scores[kind] + (u32) delta);
        if (score >= VILLAGER_MODE_RECORD_SCORE_MAX) {
            score = VILLAGER_MODE_RECORD_SCORE_MAX;
        }
        scores[kind] = (u8) score;
    }
}
CLEAN_AS(func_0209c448, VillagerModeRecord_RaiseScore)

/* func_0209c470: the score of kind `kind` cleared, then every score halved. */
void VillagerModeRecord_HalveScores(void *scores, unsigned char kind)
{
    VillagerModeRecord_SetKindByte(scores, kind, 0);
    for (int i = 0; i < VILLAGER_MODE_KINDS; i++) {
        u8 score = (u8) VillagerModeRecord_KindByte(scores, (u8) i);
        VillagerModeRecord_SetKindByte(scores, (u8) i, (char) (score >> 1));
    }
}
CLEAN_AS(func_0209c470, VillagerModeRecord_HalveScores)

/* func_0209c4a8: the kind of a highest score, picked at random (func_020644cc) among the kinds
 * that share it. */
int VillagerModeRecord_DrawTopKind(const unsigned char *scores)
{
    int top = -1;
    unsigned int tied = 0; /* bit k: kind k has the top score */
    int count = 0;

    for (int kind = 0; kind < VILLAGER_MODE_KINDS; kind++) {
        if (scores[kind] > top) {
            top = scores[kind];
            tied = 1u << kind;
            count = 1;
        } else if (scores[kind] == top) {
            tied |= 1u << kind;
            count++;
        }
    }

    u8 result = VILLAGER_MODE_KINDS;
    if (count > 0) {
        u32 pick = MainRandom_Below(count);
        for (int kind = 0; kind < VILLAGER_MODE_KINDS; kind++) {
            if (tied & (1u << kind)) {
                if (pick == 0) {
                    result = (u8) kind;
                    break;
                }
                pick--;
            }
        }
    }
    return result;
}
CLEAN_AS(func_0209c4a8, VillagerModeRecord_DrawTopKind)

/* func_0209c51c: eight bytes of a kind each copied from `from` to `to`. */
void VillagerModeRecord_CopyKindBytes(unsigned char *to, const unsigned char *from)
{
    MI_CpuCopy8(from, to, VILLAGER_MODE_KINDS);
}
CLEAN_AS(func_0209c51c, VillagerModeRecord_CopyKindBytes)

/* func_0209c52c: eight bytes of a kind each cleared. */
void VillagerModeRecord_ClearKindBytes(void *bytes)
{
    MI_CpuFill8(bytes, 0, VILLAGER_MODE_KINDS);
}
CLEAN_AS(func_0209c52c, VillagerModeRecord_ClearKindBytes)

/* func_0209c538: their destructor: nothing. */
void VillagerModeRecord_DestructKindBytes(void *bytes)
{
    (void) bytes;
}
CLEAN_AS(func_0209c538, VillagerModeRecord_DestructKindBytes)

/* func_0209c53c: their constructor: cleared. */
int VillagerModeRecord_ConstructKindBytes(unsigned char *bytes)
{
    VillagerModeRecord_ClearKindBytes(bytes);
    return (int) (uintptr_t) bytes;
}
CLEAN_AS(func_0209c53c, VillagerModeRecord_ConstructKindBytes)
