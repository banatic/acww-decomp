/* Fish drawn from the creature tables (creature_draw.h). */
#include "creature_draw.h"

#include "clean.h"
#include "creature_weight.h"
#include "date_time.h"

#define CREATURE_DRAW_FISH_FIRST 0x12e8
#define CREATURE_DRAW_FISH_LAST 0x131f
#define CREATURE_DRAW_KINDS 0x38
#define CREATURE_DRAW_ENTRY_SIZE 3
/* The hours a draw without hours of its own looks at. */
#define CREATURE_DRAW_FIRST_HOUR 0
#define CREATURE_DRAW_LAST_HOUR 23

/* The weights of the five bands (26, 23, 20, 17, 14), and the copy a draw zeroes as bands give
 * nothing. */
extern const u8 data_020c8950[CREATURE_DRAW_BANDS];
extern u8 data_021c1d18[CREATURE_DRAW_BANDS];
/* The time slots and the places a draw found fish of its band in. */
extern u8 data_021c1ce8[CREATURE_DRAW_TIME_SLOTS];
extern u8 data_021c1ce4[CREATURE_DRAW_PLACES];

/* A place drawn by `count` weights, -1 when they are all 0. */
extern int func_0202d6e4(const u8 *weights, int count);
/* A random number below `bound`. */
extern int func_020644cc(int bound);
/* The SDK's fill and copy. */
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

static int creature_is_fish(u16 item)
{
    return item >= CREATURE_DRAW_FISH_FIRST && item <= CREATURE_DRAW_FISH_LAST;
}

/* 1 shifted left by `shift` as the ARM shifts by a register: 0 from 32 on (by its low byte). */
static u32 creature_bit(int shift)
{
    u32 amount = (u32) shift & 0xff;
    return amount >= 32 ? 0 : 1u << amount;
}

/* Whether a list entry is a fish (a kind below 0x38) of a weight that is not 0. */
static int creature_entry_counts(const u8 *entry)
{
    return entry[0] < CREATURE_DRAW_KINDS && entry[2] != 0;
}

/* func_0202c9c0: the group of a place (an entry's second number): 0 for 12, 1 for 1, 2 and 4,
 * 2 for the others. */
int CreatureDraw_PlaceGroup(int place)
{
    switch (place) {
        case 12:
            return 0;
        case 1:
        case 2:
        case 4:
            return 1;
        default:
            return 2;
    }
}
CLEAN_AS(func_0202c9c0, CreatureDraw_PlaceGroup)

/* func_0202c9e8: whether the fish `*item` is in a list of the month's period (the day picks the
 * half of August and September) at any time of day of the hours first to last, with a weight
 * that is not 0. 0 for an item that is no fish. */
int CreatureDraw_FishAvailable(u16 *item, int first_hour, int last_hour, int month, u8 day)
{
    if (!creature_is_fish(*item)) {
        return 0;
    }
    CreatureTablePeriod *period = CreatureTable_Lists((unsigned int) month, (unsigned int) CreatureTable_IsSecondHalf(day));
    if (period == NULL || *period == NULL) {
        return 0;
    }
    int kind = (u8) (*item - CREATURE_DRAW_FISH_FIRST);
    int previous = CREATURE_DRAW_TIME_SLOTS;
    for (int hour = first_hour; hour <= last_hour; hour++) {
        int slot = CreatureTable_TimeSlot((u8) hour);
        if (slot == previous) {
            continue;
        }
        const CreatureTableList *lists = (*period)[slot];
        if (lists != NULL) {
            for (int place = 0; place < CREATURE_DRAW_PLACES; place++) {
                const u8 *entry = lists[place].entries;
                if (entry == NULL) {
                    continue;
                }
                for (int i = 0; i < lists[place].count; i++, entry += CREATURE_DRAW_ENTRY_SIZE) {
                    if (entry[0] < CREATURE_DRAW_KINDS && entry[0] == kind && entry[2] != 0) {
                        return 1;
                    }
                }
            }
        }
        previous = slot;
    }
    return 0;
}
CLEAN_AS(func_0202c9e8, CreatureDraw_FishAvailable)

/* func_0202cac4: a fish of now's time of day and date into `*item`: the five bands tried in a
 * random order (CreatureDraw_FishOfSlot) until `*item` is a fish. `*item` is left as it was
 * when none is found. */
void CreatureDraw_FishNow(u16 *item)
{
    DateTime now = {0};
    int left = CREATURE_DRAW_BANDS;
    DateTime_Now(&now);
    u8 month = now.month;
    u8 day = now.day;
    CreatureTablePeriod *period = CreatureTable_Lists(month, (unsigned int) CreatureTable_IsSecondHalf(day));
    if (period == NULL || *period == NULL) {
        return;
    }
    unsigned int slot = (unsigned int) CreatureTable_TimeSlot(now.hour);
    if (slot >= CREATURE_DRAW_TIME_SLOTS) {
        return;
    }
    CreatureTableList *const *lists = *period + slot;
    u8 tried[CREATURE_DRAW_BANDS];
    int second;
    MI_CpuFill8(tried, 0, (u32) left);
    while (left > 0) {
        int pick = func_020644cc(left);
        for (int band = 0; band < CREATURE_DRAW_BANDS; band++) {
            if (tried[band] != 0) {
                continue;
            }
            if (pick == 0) {
                CreatureDraw_FishOfSlot(item, &second, band, lists);
                tried[band] = 1;
                break;
            }
            pick--;
        }
        if (creature_is_fish(*item)) {
            break;
        }
        left--;
    }
}
CLEAN_AS(func_0202cac4, CreatureDraw_FishNow)

/* func_0202cb70: a fish of the period's lists at any hour: bands drawn by the weights of
 * data_020c8950 (copied to data_021c1d18, a band that gives nothing then weighing 0), at most
 * five draws; the band into `*band`, the fish's second number and time slot into `*second` and
 * `*time_slot`. Whether one was found. */
int CreatureDraw_FishByWeights(u16 *item, int *band, int *second, int *time_slot, void *period)
{
    MI_CpuCopy8(data_020c8950, data_021c1d18, CREATURE_DRAW_BANDS);
    for (int draw = 0; draw < CREATURE_DRAW_BANDS; draw++) {
        int drawn = func_0202d6e4(data_021c1d18, CREATURE_DRAW_BANDS);
        if (drawn < 0 || drawn >= CREATURE_DRAW_BANDS) {
            break;
        }
        if (CreatureDraw_FishOfBand(item, second, time_slot, drawn, period) == 1) {
            *band = drawn;
            return 1;
        }
        data_021c1d18[drawn] = 0;
    }
    return 0;
}
CLEAN_AS(func_0202cb70, CreatureDraw_FishByWeights)

/* func_0202cbdc: CreatureDraw_FishOfBandsHours at any hour. */
int CreatureDraw_FishOfBands(u16 *item, int first, int last, int month, unsigned char day)
{
    return CreatureDraw_FishOfBandsHours(item, first, last, month, day, CREATURE_DRAW_FIRST_HOUR, CREATURE_DRAW_LAST_HOUR);
}
CLEAN_AS(func_0202cbdc, CreatureDraw_FishOfBands)

/* func_0202cbfc: a fish of the bands first to last of the month's period (the day picks the
 * half of August and September) at the hours first_hour to last_hour into `*item`, the bands
 * tried in a random order; whether one was found. The bands are kept as bits of a byte, of
 * which only bands 0 to 4 are tried. */
int CreatureDraw_FishOfBandsHours(u16 *item, int first, int last, int month, u8 day, u8 first_hour, u8 last_hour)
{
    CreatureTablePeriod *period = CreatureTable_Lists((unsigned int) month, (unsigned int) CreatureTable_IsSecondHalf(day));
    if (period == NULL) {
        return 0;
    }
    u8 bands = 0;
    int left = last - first + 1;
    int second = 0;
    int time_slot = 0;
    for (int band = first; band <= last; band++) {
        bands = (u8) (bands | creature_bit(band));
    }
    for (; left > 0; left--) {
        int pick = func_020644cc(left);
        for (int band = 0; band < CREATURE_DRAW_BANDS; band++) {
            if (((bands >> band) & 1) == 0) {
                continue;
            }
            if (pick == 0) {
                if (CreatureDraw_FishOfBandHours(item, &second, &time_slot, band, period, first_hour, last_hour) != 0) {
                    return 1;
                }
                bands = (u8) (bands & ~(1u << band));
                break;
            }
            pick--;
        }
    }
    return 0;
}
CLEAN_AS(func_0202cbfc, CreatureDraw_FishOfBandsHours)

/* func_0202cca4: CreatureDraw_FishOfBandHours at any hour. */
int CreatureDraw_FishOfBand(u16 *item, int *second, int *time_slot, int band, void *period)
{
    return CreatureDraw_FishOfBandHours(item, second, time_slot, band, (CreatureTablePeriod *) period,
                                        CREATURE_DRAW_FIRST_HOUR, CREATURE_DRAW_LAST_HOUR);
}
CLEAN_AS(func_0202cca4, CreatureDraw_FishOfBand)

/* func_0202ccc0: a fish of the band at a time of day of the hours first_hour to last_hour: the
 * time slots whose lists hold fish of the band are marked in data_021c1ce8 (cleared first; an
 * hour of the slot just looked at is skipped), one of them is drawn and a fish of it drawn
 * (CreatureDraw_FishOfSlot), the slot then into `*time_slot`. What that draw says, 0 when no
 * slot has fish of the band. */
int CreatureDraw_FishOfBandHours(u16 *item, int *second, int *time_slot, int band, CreatureTablePeriod *period, u8 first_hour,
                                 u8 last_hour)
{
    CreatureTableList *const *slots = *period;
    int result = 0;
    if (slots == NULL) {
        return 0;
    }
    int previous = CREATURE_DRAW_TIME_SLOTS;
    int found = 0;
    MI_CpuFill8(data_021c1ce8, 0, CREATURE_DRAW_TIME_SLOTS);
    for (int hour = first_hour; hour <= last_hour; hour++) {
        int slot = CreatureTable_TimeSlot((u8) hour);
        if (data_021c1ce8[slot] == 0 && slot != previous) {
            if (CreatureDraw_CountInSlot(band, &slots[slot]) > 0) {
                data_021c1ce8[slot] = 1;
                found++;
            }
            previous = slot;
        }
    }
    if (found > 0) {
        int pick = func_020644cc(found);
        for (int slot = 0; slot < CREATURE_DRAW_TIME_SLOTS; slot++) {
            if (data_021c1ce8[slot] == 1) {
                if (pick == 0) {
                    result = CreatureDraw_FishOfSlot(item, second, band, &slots[slot]);
                    *time_slot = slot;
                    break;
                }
                pick--;
            }
        }
    }
    return result;
}
CLEAN_AS(func_0202ccc0, CreatureDraw_FishOfBandHours)

/* func_0202cd78: a fish of the band in one of the two places of a time slot's lists: the
 * places with fish of the band are marked in data_021c1ce4 (cleared first), one of them is
 * drawn and a fish of it drawn (CreatureDraw_FishOfList). What that draw says, 0 when no place
 * has fish of the band or the slot has no lists. */
int CreatureDraw_FishOfSlot(u16 *item, int *second, int band, CreatureTableList *const *slot)
{
    const CreatureTableList *lists = *slot;
    int result = 0;
    if (lists == NULL) {
        return 0;
    }
    int found = 0;
    MI_CpuFill8(data_021c1ce4, 0, CREATURE_DRAW_PLACES);
    for (int place = 0; place < CREATURE_DRAW_PLACES; place++) {
        if (CreatureDraw_CountInList(band, &lists[place]) > 0) {
            data_021c1ce4[place] = 1;
            found++;
        }
    }
    if (found > 0) {
        int pick = func_020644cc(found);
        for (int place = 0; place < CREATURE_DRAW_PLACES; place++) {
            if (data_021c1ce4[place] == 1) {
                if (pick == 0) {
                    result = CreatureDraw_FishOfList(item, second, band, &lists[place]);
                    break;
                }
                pick--;
            }
        }
    }
    return result;
}
CLEAN_AS(func_0202cd78, CreatureDraw_FishOfSlot)

/* func_0202cdf8: the fish of the band in a time slot's two lists (0 without lists). */
int CreatureDraw_CountInSlot(int band, CreatureTableList *const *slot)
{
    const CreatureTableList *lists = *slot;
    int count = 0;
    if (lists != NULL) {
        for (int place = 0; place < CREATURE_DRAW_PLACES; place++) {
            count += CreatureDraw_CountInList(band, &lists[place]);
        }
    }
    return count;
}
CLEAN_AS(func_0202cdf8, CreatureDraw_CountInSlot)

/* func_0202ce24: one of the list's fish of the band drawn at random: its item into `*item` and
 * its second number into `*second`; whether there was one. */
int CreatureDraw_FishOfList(u16 *item, int *second, int band, const CreatureTableList *list)
{
    const u8 *entry = list->entries;
    if (entry == NULL || list->count == 0) {
        return 0;
    }
    int count = CreatureDraw_CountInList(band, list);
    if (count <= 0) {
        return 0;
    }
    int pick = func_020644cc(count);
    for (int i = 0; i < list->count; i++, entry += CREATURE_DRAW_ENTRY_SIZE) {
        if (entry[2] == 0 || entry[0] >= CREATURE_DRAW_KINDS || band != CreatureWeight_BandA(entry[2])) {
            continue;
        }
        if (pick == 0) {
            *item = (u16) (CREATURE_DRAW_FISH_FIRST + entry[0]);
            *second = entry[1];
            return 1;
        }
        pick--;
    }
    return 0;
}
CLEAN_AS(func_0202ce24, CreatureDraw_FishOfList)

/* func_0202ceac: how many of the list's entries are fish of the band (by their weights). */
int CreatureDraw_CountInList(int band, const CreatureTableList *list)
{
    const u8 *entry = list->entries;
    int count = 0;
    if (entry == NULL || list->count == 0) {
        return 0;
    }
    for (int i = 0; i < list->count; i++, entry += CREATURE_DRAW_ENTRY_SIZE) {
        if (creature_entry_counts(entry) && CreatureWeight_BandA(entry[2]) == band) {
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_0202ceac, CreatureDraw_CountInList)
