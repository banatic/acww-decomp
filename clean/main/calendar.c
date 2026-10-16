/* Date and time arithmetic over the clock the ARM7 keeps up to date in the game's memory. */
#include "calendar.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"

/* The last day of each period of the year, as (month << 8) | day, in the game's own tables.
 * What the game uses the two sets of periods for is not known yet. */
extern const u16 data_020d1b04[19];
extern const u16 data_020d1b2c[23];

/* QUIRK: every year divisible by 4 is a leap year, which is right for all of 2000-2099. */
static int is_leap(u32 year)
{
    return (year & 3) == 0;
}

/* The days in each month, the leap year's row first (the game's table at 020d1aec). */
extern const u8 data_020d1aec[2][12];

/* The days before each month, and in the last entry the year's: the common year's row first,
 * then the leap year's. */
extern const u16 data_020d1b5c[2][13];

/* QUIRK: the game looks a month up in its table at [month - 1] without a check, and some of
 * its callers ask about month 0 or 13. Month 0 reads the halfword before the row (in a leap
 * year the end of the common year's row, 365), month 13 the year's own length, and the
 * months past that the bytes after the row; they are read here the same way. */
static int days_before(int leap, int month)
{
    const u16 *row = data_020d1b5c[leap];
    return *(const u16 *) ((uintptr_t) row + 2 * (u32) (month - 1));
}

/* Days from 1 January 2000, given a day of the month. */
static int day_number(const Date *date)
{
    int year = date->year;
    return 365 * year + (year + 3) / 4 + days_before(is_leap(year), date->month) + date->day - 1;
}

/* func_0209dd9c */
BOOL Calendar_IsOnOrAfter(const Date *date, const Date *other)
{
    if (date->year != other->year) {
        return date->year > other->year;
    }
    if (date->month != other->month) {
        return date->month > other->month;
    }
    return date->day >= other->day;
}
CLEAN_AS(func_0209dd9c, Calendar_IsOnOrAfter)

/* func_0209dcdc: the days from `origin` to `date`, negative when `date` is earlier. */
int Calendar_DaysFrom(const Date *date, const Date *origin)
{
    /* The game orders the two dates first and counts from the earlier one up. */
    BOOL later = Calendar_IsOnOrAfter(date, origin);
    int days = later ? day_number(date) - day_number(origin) : day_number(origin) - day_number(date);
    return later ? days : -days;
}
CLEAN_AS(func_0209dcdc, Calendar_DaysFrom)

/* func_0209ddd4: `time` plus `delta`, past midnight starting the day again.
 * QUIRK: the sums are kept in bytes, as in the game, so very large deltas wrap. */
void Calendar_AddTime(Time time, Time delta, Time *sum)
{
    u8 minute = time.minute + delta.minute;
    u8 hour = time.hour + delta.hour + minute / 60;
    sum->minute = minute % 60;
    sum->hour = hour % 24;
}
CLEAN_AS(func_0209ddd4, Calendar_AddTime)

/* func_0209de24.
 * QUIRK: the game reads its table at [month - 1] unchecked, so a month outside 1-12 reads the
 * bytes around it (month 0 of a common year the leap row's December, month 13 of a leap year
 * the common row's January, and so on); it is read here the same way. */
u8 Calendar_DaysInMonth(u32 year, u32 month)
{
    const u8 *row = data_020d1aec[is_leap(year) ? 0 : 1];
    return *(const u8 *) ((uintptr_t) row + (u32) (month - 1));
}
CLEAN_AS(func_0209de24, Calendar_DaysInMonth)

/* func_0209de44: the day of the month that is the `n`th `weekday` (0 = Sunday), or -1 when
 * the month has no such day.
 * BUG: a day that falls on the month's last day is reported as missing. */
int Calendar_NthWeekday(int year, int month, int weekday, int n)
{
    int first = Calendar_Weekday(year, month, 1);
    int day = weekday - first + 1 + (weekday < first ? 7 : 0) + 7 * (n - 1);
    int days = Calendar_DaysInMonth(year, month);
#ifdef BUGFIX
    return day <= days ? day : -1;
#else
    return day < days ? day : -1;
#endif
}
CLEAN_AS(func_0209de44, Calendar_NthWeekday)

/* func_0209de88: the weekday of a date (0 = Sunday), counted from today's. */
int Calendar_Weekday(int year, int month, int day)
{
    Date date = {(u8) day, (u8) month, (u8) year, 0};
    Date today;
    Calendar_Today(&today);
    int offset = Calendar_DaysFrom(&date, &today) % 7;
    return (Calendar_TodayWeekday() + offset + 7) % 7;
}
CLEAN_AS(func_0209de88, Calendar_Weekday)

/* func_0209dcac */
int Calendar_PartOfDay(void)
{
    Time now;
    Calendar_Now(&now);
    if (now.hour < 5) {
        return PART_OF_DAY_NIGHT;
    }
    if (now.hour < 12) {
        return PART_OF_DAY_MORNING;
    }
    if (now.hour < 17) {
        return PART_OF_DAY_AFTERNOON;
    }
    return PART_OF_DAY_EVENING;
}
CLEAN_AS(func_0209dcac, Calendar_PartOfDay)

/* func_0209df64 */
void Calendar_Today(Date *today)
{
    today->day = (u8) data_021dc744.day;
    today->month = (u8) data_021dc744.month;
    today->year = (u8) data_021dc744.year;
    today->unused = 0;
}
CLEAN_AS(func_0209df64, Calendar_Today)

/* func_0209ded0 */
int Calendar_TodayWeekday(void)
{
    return (int) data_021dc744.weekday;
}
CLEAN_AS(func_0209ded0, Calendar_TodayWeekday)

/* func_0209def4 */
void Calendar_Now(Time *now)
{
    now->minute = (u8) data_021dc754.minute;
    now->hour = (u8) data_021dc754.hour;
}
CLEAN_AS(func_0209def4, Calendar_Now)

/* The index of the first period in `ends` that `date` falls in, or 0 past the last. */
static int period(const u16 *ends, int count, const Date *date)
{
    u16 key = (u16) ((date->month << 8) | date->day);
    for (int i = 0; i < count; i++) {
        if (key <= ends[i]) {
            return i;
        }
    }
    return 0;
}

/* func_0209dc10 */
int Calendar_PeriodA(const Date *date)
{
    return period(data_020d1b04, 19, date);
}
CLEAN_AS(func_0209dc10, Calendar_PeriodA)

/* func_0209dc74 */
int Calendar_PeriodB(const Date *date)
{
    return period(data_020d1b2c, 23, date);
}
CLEAN_AS(func_0209dc74, Calendar_PeriodB)

/* func_0209dbe4 */
int Calendar_PeriodAOf(const DateTime *when)
{
    Date date = {when->day, when->month, when->year, 0};
    return Calendar_PeriodA(&date);
}
CLEAN_AS(func_0209dbe4, Calendar_PeriodAOf)

/* func_0209dc48 */
int Calendar_PeriodBOf(const DateTime *when)
{
    Date date = {when->day, when->month, when->year, 0};
    return Calendar_PeriodB(&date);
}
CLEAN_AS(func_0209dc48, Calendar_PeriodBOf)

static_assert(sizeof(Date) == 4 && offsetof(Date, year) == 2, "Date layout");
static_assert(sizeof(RtcDate) == 16 && offsetof(RtcTime, minute) == 4, "clock layout");
