/* Small table lookups. */
#include "lookups.h"
#include "clean.h"

#include <assert.h>

/* For each kind, the night hours 1:30-8:00, 2:00-6:30, 4:30-10:00, 1:00-5:00, 2:30-7:00 and
 * 3:30-9:00. The kind is the byte at 14 in the records func_020036e8 reads. */
extern const DayWindow data_020cd4ac[6];
/* The last day of each star sign, in enum StarSign order. */
extern const MonthDay data_020cd494[12];
/* Where each of the five groups starts in a flat numbering of 32 (0, 2, 14, 16, 20). */
extern const u8 data_020cd424[5];
/* Three bytes for each of the 38 items of kind 0xd. */
extern const u8 data_020cd550[38][3];

#define ITEM_KIND(code) ((code) >> 12)
#define ITEM_INDEX(code) ((code) & 0xfff)
#define ITEM_KIND_D 0xd

/* func_0208222c. QUIRK: a kind past the table reads the first entry. */
const DayWindow *Lookups_DayWindow(u32 kind)
{
    if (kind >= 6) {
        kind = 0;
    }
    return &data_020cd4ac[kind];
}
CLEAN_AS(func_0208222c, Lookups_DayWindow)

/* func_02082264 */
u32 Lookups_StarSignOf(const MonthDay *birthday)
{
    return Lookups_StarSign(birthday->month, birthday->day);
}
CLEAN_AS(func_02082264, Lookups_StarSignOf)

/* func_02082274: the star sign (enum StarSign) of a day of the year. Days after the last
 * sign's end fall through the table to Capricorn, which is where they belong. */
u32 Lookups_StarSign(u32 month, u32 day)
{
    for (u32 i = 0; i < 12; i++) {
        const MonthDay *end = &data_020cd494[i];
        if (month < end->month || (month == end->month && day <= end->day)) {
            return i;
        }
    }
    return STAR_SIGN_CAPRICORN;
}
CLEAN_AS(func_02082274, Lookups_StarSign)

/* func_020822b0: a group (pair[0], 0-4) and a number in it (pair[1]) as one index in 0-31;
 * anything else is 0.
 * QUIRK: groups 0-2 number from 1 and groups 3 and 4 from 0; only group 4 checks its range. */
u8 Lookups_SlotIndex(const u8 *pair)
{
    u8 group = pair[0];
    u8 number = pair[1];
    switch (group) {
        case 0:
        case 1:
        case 2:
            return (u8) (data_020cd424[group] + number - 1);
        case 3:
            return (u8) (data_020cd424[group] + number);
        case 4:
            return number < 12 ? (u8) (data_020cd424[group] + number) : 0;
        default:
            return 0;
    }
}
CLEAN_AS(func_020822b0, Lookups_SlotIndex)

/* func_020824d0: the record of an item of kind 0xd, or null for other items and indexes past
 * the table. */
const u8 *Lookups_KindDRecord(const ItemCode *item)
{
    u32 index = ITEM_INDEX(*item);
    if (ITEM_KIND(*item) != ITEM_KIND_D || index >= 38) {
        return NULL;
    }
    return data_020cd550[index];
}
CLEAN_AS(func_020824d0, Lookups_KindDRecord)

/* func_02082374: the first byte of the item's record, signed, or 0 when it has none. */
int Lookups_KindDFirst(const ItemCode *item)
{
    if (ITEM_KIND(*item) != ITEM_KIND_D) {
        return 0;
    }
    const u8 *record = Lookups_KindDRecord(item);
    return record != NULL ? (s8) record[0] : 0;
}
CLEAN_AS(func_02082374, Lookups_KindDFirst)

static_assert(sizeof(DayWindow) == 4 && sizeof(MonthDay) == 2, "table layouts");
