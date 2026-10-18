/* Insects drawn from the insect tables (insect_draw.h). */
#include "insect_draw.h"

#include "acre_map.h"
#include "acre_record.h"
#include "clean.h"
#include "creature_weight.h"
#include "date_time.h"
#include "insect_tables.h"
#include "main_random.h"

#define INSECT_DRAW_FIRST 0x12b0
#define INSECT_DRAW_LAST 0x12e7
#define INSECT_DRAW_KINDS 0x38
#define INSECT_DRAW_ENTRY_SIZE 2
/* The hours a draw without hours of its own looks at. */
#define INSECT_DRAW_FIRST_HOUR 0
#define INSECT_DRAW_LAST_HOUR 23

/* The weights of the five bands (26, 23, 20, 17, 14), and the copy a draw zeroes as bands give
 * nothing. */
extern const u8 data_020c8948[INSECT_DRAW_BANDS];
extern u8 data_021c1d10[INSECT_DRAW_BANDS];
/* The time slots a draw found insects of its band in. */
extern u8 data_021c1d20[INSECT_DRAW_TIME_SLOTS];
/* The places InsectDraw_MissingPlaces names when the town lacks them: 7, 13, 1, 2. */
extern const u8 data_020c893c[INSECT_DRAW_MISSING_MAX];

/* The SDK's fill and copy. */
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

static int insect_is_insect(u16 item)
{
    return item >= INSECT_DRAW_FIRST && item <= INSECT_DRAW_LAST;
}

/* The lists of a month (1 to 12). */
static const InsectDrawList *insect_lists(int month)
{
    return InsectTables_MonthLists(month - 1);
}

/* 1 shifted left by `shift` as the ARM shifts by a register: 0 from 32 on (by its low byte). */
static u32 insect_bit(int shift)
{
    u32 amount = (u32) shift & 0xff;
    return amount >= 32 ? 0 : 1u << amount;
}

/* func_0202cef4: whether the insect `*item` is in a list of the month at any time of day of the
 * hours first to last, with a weight that is not 0. 0 for an item that is no insect.
 * BUG: every list is read for as many entries as the first time slot's list has (the count of
 * the month's list 0), not its own. */
int InsectDraw_Available(u16 *item, int first_hour, int last_hour, int month)
{
    if (!insect_is_insect(*item)) {
        return 0;
    }
    const InsectDrawList *lists = insect_lists(month);
    if (lists == NULL) {
        return 0;
    }
    int kind = (u8) (*item - INSECT_DRAW_FIRST);
    int previous = INSECT_DRAW_TIME_SLOTS;
    for (int hour = first_hour; hour <= last_hour; hour++) {
        int slot = InsectTables_TimeSlot((u8) hour);
        if (slot == previous) {
            continue;
        }
        const u8 *entry = lists[slot].entries;
        if (entry != NULL) {
            int before = 0;
#ifdef BUGFIX
            int count = lists[slot].count;
#else
            int count = lists[0].count;
#endif
            for (int i = 0; i < count; i++, entry += INSECT_DRAW_ENTRY_SIZE) {
                if (entry[0] == kind && entry[1] - before > 0) {
                    return 1;
                }
                before = entry[1];
            }
        }
        previous = slot;
    }
    return 0;
}
CLEAN_AS(func_0202cef4, InsectDraw_Available)

/* func_0202cfa8: an insect of now's time of day and month into `*item`, leaving out the places
 * the town lacks: the five bands tried in a random order (InsectDraw_OfList) until `*item` is
 * an insect. `*item` is left as it was when none is found. */
void InsectDraw_Now(u16 *item)
{
    DateTime now = {0};
    int left = INSECT_DRAW_BANDS;
    int place = 0;
    DateTime_Now(&now);
    int slot = InsectTables_TimeSlot(now.hour);
    const InsectDrawList *lists = insect_lists(now.month);
    if (lists == NULL || slot < 0 || slot >= INSECT_DRAW_TIME_SLOTS) {
        return;
    }
    int missing_count = 0;
    int missing[INSECT_DRAW_MISSING_MAX];
    u8 tried[INSECT_DRAW_BANDS];
    const InsectDrawList *list = &lists[slot];
    MI_CpuFill8(tried, 0, (u32) left);
    InsectDraw_MissingPlaces(missing, &missing_count);
    while (left > 0) {
        int pick = MainRandom_Below(left);
        for (int band = 0; band < INSECT_DRAW_BANDS; band++) {
            if (tried[band] != 0) {
                continue;
            }
            if (pick == 0) {
                InsectDraw_OfList(item, &place, band, list->entries, list->count, missing, missing_count);
                tried[band] = 1;
                break;
            }
            pick--;
        }
        if (insect_is_insect(*item)) {
            break;
        }
        left--;
    }
}
CLEAN_AS(func_0202cfa8, InsectDraw_Now)

/* func_0202d060: an insect of the month of `*when` at any hour, leaving out the places the town
 * lacks: bands drawn by the weights of data_020c8948 (copied to data_021c1d10, a band that
 * gives nothing then weighing 0), at most five draws; the band into `*band`, the insect's place
 * and time slot into `*place` and `*time_slot`. Whether one was found. */
int InsectDraw_ByWeights(u16 *item, int *band, int *place, int *time_slot, DateTime *when)
{
    const InsectDrawList *lists = insect_lists(when->month);
    if (lists == NULL) {
        return 0;
    }
    int missing_count = 0;
    int missing[INSECT_DRAW_MISSING_MAX];
    MI_CpuCopy8(data_020c8948, data_021c1d10, INSECT_DRAW_BANDS);
    InsectDraw_MissingPlaces(missing, &missing_count);
    for (int draw = 0; draw < INSECT_DRAW_BANDS; draw++) {
        int drawn = InsectDraw_PickByWeights(data_021c1d10, INSECT_DRAW_BANDS);
        if (drawn < 0 || drawn >= INSECT_DRAW_BANDS) {
            break;
        }
        if (InsectDraw_OfBandAnyHour(item, place, time_slot, drawn, lists, missing, missing_count) == 1) {
            *band = drawn;
            return 1;
        }
        data_021c1d10[drawn] = 0;
    }
    return 0;
}
CLEAN_AS(func_0202d060, InsectDraw_ByWeights)

/* func_0202d0ec: an insect of the bands first to last of the month at the hours first_hour to
 * last_hour into `*item`, the bands tried in a random order, no place left out; whether one was
 * found. The bands are kept as bits of a byte, of which only bands 0 to 4 are tried.
 * REQUIRES: first and last within 0 to 4 (as the game passes them); the count of tries is
 * last - first + 1 whatever the bands. */
int InsectDraw_OfBandsHours(u16 *item, int first, int last, u8 first_hour, u8 last_hour, u8 month)
{
    const InsectDrawList *lists = insect_lists(month);
    if (lists == NULL) {
        return 0;
    }
    u8 bands = 0;
    int left = last - first + 1;
    int place = 0;
    int time_slot = 0;
    for (int band = first; band <= last; band++) {
        bands = (u8) (bands | insect_bit(band));
    }
    for (; left > 0; left--) {
        int pick = MainRandom_Below(left);
        for (int band = 0; band < INSECT_DRAW_BANDS; band++) {
            if (((bands >> band) & 1) == 0) {
                continue;
            }
            if (pick == 0) {
                if (InsectDraw_OfBand(item, &place, &time_slot, band, lists, NULL, 0, first_hour, last_hour) != 0) {
                    return 1;
                }
                bands = (u8) (bands & ~insect_bit(band));
                break;
            }
            pick--;
        }
    }
    return 0;
}
CLEAN_AS(func_0202d0ec, InsectDraw_OfBandsHours)

/* func_0202d190: InsectDraw_OfBandsHours at any hour. */
int InsectDraw_OfBands(u16 *item, int first, int last, int month)
{
    return InsectDraw_OfBandsHours(item, first, last, INSECT_DRAW_FIRST_HOUR, INSECT_DRAW_LAST_HOUR, (u8) month);
}
CLEAN_AS(func_0202d190, InsectDraw_OfBands)

/* func_0202d1a8: InsectDraw_OfBand at any hour. */
int InsectDraw_OfBandAnyHour(u16 *item, int *place, int *time_slot, int band, const InsectDrawList *lists, const int *missing,
                             int missing_count)
{
    return InsectDraw_OfBand(item, place, time_slot, band, lists, missing, missing_count, INSECT_DRAW_FIRST_HOUR,
                             INSECT_DRAW_LAST_HOUR);
}
CLEAN_AS(func_0202d1a8, InsectDraw_OfBandAnyHour)

/* func_0202d1cc: an insect of the band in the month's lists at the hours first_hour to
 * last_hour: the time slots whose list holds insects of the band (outside the missing places)
 * are marked in data_021c1d20, one of them is picked at random and an insect of its list drawn
 * (InsectDraw_OfList); its time slot goes into `*time_slot`. Whether one was found. */
int InsectDraw_OfBand(u16 *item, int *place, int *time_slot, int band, const InsectDrawList *lists, const int *missing,
                      int missing_count, u8 first_hour, u8 last_hour)
{
    if (lists == NULL) {
        return 0;
    }
    int found = 0;
    int previous = INSECT_DRAW_TIME_SLOTS;
    MI_CpuFill8(data_021c1d20, 0, INSECT_DRAW_TIME_SLOTS);
    for (int hour = first_hour; hour <= last_hour; hour++) {
        int slot = InsectTables_TimeSlot((u8) hour);
        if (data_021c1d20[slot] != 0 || slot == previous) {
            continue;
        }
        if (InsectDraw_CountInList(band, lists[slot].entries, lists[slot].count, missing, missing_count) > 0) {
            data_021c1d20[slot] = 1;
            found++;
        }
        previous = slot;
    }
    if (found <= 0) {
        return 0;
    }
    int pick = MainRandom_Below(found);
    for (int slot = 0; slot < INSECT_DRAW_TIME_SLOTS; slot++) {
        if (data_021c1d20[slot] == 0) {
            continue;
        }
        if (pick == 0) {
            int result = InsectDraw_OfList(item, place, band, lists[slot].entries, lists[slot].count, missing, missing_count);
            *time_slot = slot;
            return result;
        }
        pick--;
    }
    return 0;
}
CLEAN_AS(func_0202d1cc, InsectDraw_OfBand)

/* func_0202d2a0: one of the list's insects of the band whose place is not missing, picked at
 * random, into `*item` (0x12b0 + its kind; 0x12b0 for a kind of 0x38 or more) and its place into
 * `*place`. Whether one was found. */
int InsectDraw_OfList(u16 *item, int *place, int band, const u8 *entries, int count, const int *missing, int missing_count)
{
    if (count <= 0 || entries == NULL) {
        return 0;
    }
    int matches = InsectDraw_CountInList(band, entries, count, missing, missing_count);
    if (matches <= 0) {
        return 0;
    }
    int pick = MainRandom_Below(matches);
    int before = 0;
    for (int i = 0; i < count; i++, entries += INSECT_DRAW_ENTRY_SIZE) {
        int weight = entries[1] - before;
        if (weight > 0 && band == CreatureWeight_BandB((u8) weight)) {
            int where = InsectTables_Place(entries[0]);
            if (InsectDraw_IsListed(where, missing, missing_count) == 0) {
                if (pick == 0) {
                    *item = (u16) (entries[0] < INSECT_DRAW_KINDS ? INSECT_DRAW_FIRST + entries[0] : INSECT_DRAW_FIRST);
                    *place = where;
                    return 1;
                }
                pick--;
            }
        }
        before = entries[1];
    }
    return 0;
}
CLEAN_AS(func_0202d2a0, InsectDraw_OfList)

/* func_0202d34c: how many of the list's entries are of the band and live in a place not
 * missing. QUIRK: a list whose running total does not grow at some entry (a weight of 0)
 * counts as none at all. */
int InsectDraw_CountInList(int band, const u8 *entries, int count, const int *missing, int missing_count)
{
    int matches = 0;
    if (entries == NULL || count <= 0) {
        return 0;
    }
    int before = 0;
    for (int i = 0; i < count; i++, entries += INSECT_DRAW_ENTRY_SIZE) {
        int weight = entries[1] - before;
        if (weight <= 0) {
            return 0;
        }
        if (band == CreatureWeight_BandB((u8) weight) &&
            InsectDraw_IsListed(InsectTables_Place(entries[0]), missing, missing_count) == 0) {
            matches++;
        }
        before = entries[1];
    }
    return matches;
}
CLEAN_AS(func_0202d34c, InsectDraw_CountInList)

/* func_0202d3b0: whether `place` is one of the `count` places of the list (none without a
 * list). */
int InsectDraw_IsListed(int place, const int *list, int count)
{
    if (list == NULL) {
        return 0;
    }
    for (int i = 0; i < count; i++) {
        if (list[i] == place) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_0202d3b0, InsectDraw_IsListed)

#ifdef BUGFIX
/* The codes of layer 0 that show a place is in the town: 0xc8 to 0xcf for the second place
 * (13), and the codes of the second set for the third (1). */
static int insect_is_code_c8(u16 code)
{
    return code >= 0xc8 && code <= 0xcf;
}

static int insect_is_second_set(u16 code)
{
    return code <= 0x11 || (code >= 0x12 && code <= 0x19) || code == 0x1a || code == 0x1c || code == 0x1d ||
           (code >= 0x8a && code <= 0xa5);
}
#endif

/* Both bits a scan can set; it stops once it has them. */
#define INSECT_DRAW_FOUND_ALL 6

/* func_0202d3d4: the places the town lacks (of 7, 13, 1, 2) into `places`, their number into
 * `*count`. Each inner acre of the town (all but the border) is looked at: its first layer's
 * 16 x 16 codes were meant to show places 13 and 1 (bits 1 and 2), the others always counting
 * as missing.
 * BUG: a code found sets its bit only when the bit is set already, so no bit is ever set: all
 * four places are always named, after every inner acre's codes are asked for. */
void InsectDraw_MissingPlaces(int *places, int *count)
{
    const AcreMap *town = (const AcreMap *) (uintptr_t) AcreMap_Town();
    u8 found = 0;
    *count = 0;
    if (town != NULL) {
        int wide = town->acres_wide;
        int high = town->acres_high;
        for (int z = 1; z < high - 1 && found != INSECT_DRAW_FOUND_ALL; z++) {
            for (int x = 1; x < wide - 1 && found != INSECT_DRAW_FOUND_ALL; x++) {
                if ((u32) x >= (u32) town->acres_wide || (u32) z >= (u32) town->acres_high || town->acres == NULL) {
                    continue;
                }
                AcreRecord *acre =
                    (AcreRecord *) (void *) (town->acres + ((u32) x + (u32) z * (u32) town->acres_wide) * ACRE_MAP_ACRE_SIZE);
                u16 *codes = AcreRecord_Tile(acre, 0, 0, 0);
                if (codes == NULL) {
                    continue;
                }
#ifdef BUGFIX
                for (int i = 0; i < ACRE_RECORD_TILES && found != INSECT_DRAW_FOUND_ALL; i++) {
                    if (insect_is_code_c8(codes[i])) {
                        found |= 2;
                    } else if (insect_is_second_set(codes[i])) {
                        found |= 4;
                    }
                }
#endif
            }
        }
    }
    for (int i = 0; i < INSECT_DRAW_MISSING_MAX; i++) {
        if (((found >> i) & 1) == 0) {
            *places++ = data_020c893c[i];
            *count = *count + 1;
        }
    }
}
CLEAN_AS(func_0202d3d4, InsectDraw_MissingPlaces)

/* func_0202d6e4: one of `count` places picked by their weights (place j when the random number
 * below the total falls in its share), -1 when the weights add up to 0.
 * QUIRK: the total and the running sum are bytes: weights adding up past 255 wrap. */
int InsectDraw_PickByWeights(const u8 *weights, int count)
{
    u8 total = 0;
    for (int i = 0; i < count; i++) {
        total = (u8) (total + weights[i]);
    }
    if (total == 0) {
        return -1;
    }
    u8 target = (u8) MainRandom_Below(total);
    u8 sum = 0;
    for (int j = 0; j < count; j++) {
        sum = (u8) (sum + weights[j]);
        if (target < sum) {
            return j;
        }
    }
    return -1;
}
CLEAN_AS(func_0202d6e4, InsectDraw_PickByWeights)
