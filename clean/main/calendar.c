/* Date and time arithmetic over the clock the ARM7 keeps up to date in the game's memory. */
#include "calendar.h"

#include <assert.h>
#include <stddef.h>

/* The last day of each period of the year, as (month << 8) | day, in the game's own tables.
 * What the game uses the two sets of periods for is not known yet. */
extern const u16 data_020d1b04[19];
extern const u16 data_020d1b2c[23];

/* QUIRK: every year divisible by 4 is a leap year, which is right for all of 2000-2099. */
static int is_leap(u32 year)
{
    return (year & 3) == 0;
}

static const u8 days_in_month[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

/* The days before each month, and in the last entry the year's (the game's table at
 * 020d1b5c). */
static const u16 days_before_month[2][13] = {
    {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365},
    {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366},
};

/* QUIRK: the game looks a month up in its table at [month - 1] without a check, and some of
 * its callers ask about month 0. Month 0 then reads the entry before the row: in a leap year
 * the end of the common year's row (365), otherwise the zero halfword before the table.
 * Month 13 reads the year's own length. REQUIRES: month 0-13. */
static int days_before(int leap, int month)
{
    if (month == 0) {
        return leap ? days_before_month[0][12] : 0;
    }
    return days_before_month[leap][month - 1];
}

/* Days from 1 January 2000. REQUIRES: a day of the month; month 0-13 (days_before). */
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

/* func_0209dcdc: the days from `origin` to `date`, negative when `date` is earlier. */
int Calendar_DaysFrom(const Date *date, const Date *origin)
{
    return day_number(date) - day_number(origin);
}

/* func_0209ddd4: `time` plus `delta`, past midnight starting the day again.
 * QUIRK: the sums are kept in bytes, as in the game, so very large deltas wrap. */
void Calendar_AddTime(Time time, Time delta, Time *sum)
{
    u8 minute = time.minute + delta.minute;
    u8 hour = time.hour + delta.hour + minute / 60;
    sum->minute = minute % 60;
    sum->hour = hour % 24;
}

/* func_0209de24.
 * QUIRK: as with days_before, the game reads its table at [month - 1] unchecked, and its leap
 * year row (at 020d1aec) comes before the common year's (020d1af8). Month 0 of a leap year
 * reads the zero byte before the table and of a common year the leap row's December; month 13
 * of a leap year reads the common row's January and of a common year the first byte of the
 * next table (the periods' first entry, 0x0104). REQUIRES: month 0-13. */
u8 Calendar_DaysInMonth(u32 year, u32 month)
{
    int leap = is_leap(year);
    if (month == 0) {
        return leap ? 0 : days_in_month[1][11];
    }
    if (month == 13) {
        return leap ? days_in_month[0][0] : (u8) data_020d1b04[0];
    }
    return days_in_month[leap][month - 1];
}

/* func_0209de44: the day of the month that is the `n`th `weekday` (0 = Sunday), or -1 when
 * the month has no such day.
 * BUG: a day that falls on the month's last day is reported as missing. */
int Calendar_NthWeekday(int year, int month, int weekday, int n)
{
    int first = Calendar_Weekday(year, month, 1);
    int day = weekday - first + 1 + (weekday < first ? 7 : 0) + 7 * (n - 1);
    return day < Calendar_DaysInMonth(year, month) ? day : -1;
}

/* func_0209de88: the weekday of a date (0 = Sunday), counted from today's. */
int Calendar_Weekday(s8 year, s8 month, s8 day)
{
    Date date = {(u8) day, (u8) month, (u8) year, 0};
    Date today;
    Calendar_Today(&today);
    int offset = Calendar_DaysFrom(&date, &today) % 7;
    return (Calendar_TodayWeekday() + offset + 7) % 7;
}

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

/* func_0209df64 */
void Calendar_Today(Date *today)
{
    today->day = (u8) data_021dc744.day;
    today->month = (u8) data_021dc744.month;
    today->year = (u8) data_021dc744.year;
    today->unused = 0;
}

/* func_0209ded0 */
int Calendar_TodayWeekday(void)
{
    return (int) data_021dc744.weekday;
}

/* func_0209def4 */
void Calendar_Now(Time *now)
{
    now->minute = (u8) data_021dc754.minute;
    now->hour = (u8) data_021dc754.hour;
}

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

/* func_0209dc74 */
int Calendar_PeriodB(const Date *date)
{
    return period(data_020d1b2c, 23, date);
}

/* func_0209dbe4 */
int Calendar_PeriodAOf(const DateTime *when)
{
    Date date = {when->day, when->month, when->year, 0};
    return Calendar_PeriodA(&date);
}

/* func_0209dc48 */
int Calendar_PeriodBOf(const DateTime *when)
{
    Date date = {when->day, when->month, when->year, 0};
    return Calendar_PeriodB(&date);
}

static_assert(sizeof(Date) == 4 && offsetof(Date, year) == 2, "Date layout");
static_assert(sizeof(RtcDate) == 16 && offsetof(RtcTime, minute) == 4, "clock layout");
