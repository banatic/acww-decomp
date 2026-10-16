/* The day the town was started (town_start_day.h). */
#include "town_start_day.h"

#include "clean.h"
#include "date_time.h"

static_assert(sizeof(TownStartDay) == 4, "a town start day");

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

#define EXPIRY_HOUR 6 /* the day stops counting at this hour of the next day */

/* func_0209fa30 */
int TownStartDay_IsSet(TownStartDay *start)
{
    return start->set != 0;
}
CLEAN_AS(func_0209fa30, TownStartDay_IsSet)

/* func_0209fa40: the day forgotten once the clock is at 6:00 of the next day or later, or when
 * the clock is before the day itself (it was set back). Only the hour and the date count. */
void TownStartDay_Expire(TownStartDay *start)
{
    if (TownStartDay_IsSet(start) == 0) {
        return;
    }
    const int fields = DATE_TIME_HOUR | DATE_TIME_DAY | DATE_TIME_MONTH | DATE_TIME_YEAR;
    DateTime now = {0};
    DateTime_Now(&now);

    DateTime limit = {0};
    limit.year = start->year;
    limit.month = start->month;
    limit.day = start->day;
    limit.hour = 0;
    if (DateTime_Compare(&limit, &now, fields) == 1) {
        start->set = 0;
        return;
    }
    limit.hour = EXPIRY_HOUR;
    DateTime_AddDays(&limit, 1);
    if (DateTime_Compare(&limit, &now, fields) != 1) {
        start->set = 0;
    }
}
CLEAN_AS(func_0209fa40, TownStartDay_Expire)

/* func_0209faac: the day set to `date`, or to today when `date` is NULL; 1. */
int TownStartDay_Set(TownStartDay *start, const Date *date)
{
    Date today;
    if (date == NULL) {
        Calendar_Today(&today);
        date = &today;
    }
    MI_CpuCopy8(date, start, sizeof(TownStartDay));
    start->set = 1;
    return 1;
}
CLEAN_AS(func_0209faac, TownStartDay_Set)

/* func_0209fad4: no day: 1 January 2000, not set. */
void TownStartDay_Init(TownStartDay *start)
{
    start->day = 1;
    start->month = 1;
    start->year = 0;
    start->set = 0;
}
CLEAN_AS(func_0209fad4, TownStartDay_Init)

/* func_0209fae4: the destructor; nothing to do. */
void TownStartDay_Destruct(TownStartDay *start)
{
    (void) start;
}
CLEAN_AS(func_0209fae4, TownStartDay_Destruct)

/* func_0209fae8: the constructor (__sinit_020c64e8); nothing to do. */
void TownStartDay_Construct(TownStartDay *start)
{
    (void) start;
}
CLEAN_AS(func_0209fae8, TownStartDay_Construct)
