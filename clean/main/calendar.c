/* Date and time arithmetic over the clock the ARM7 keeps up to date in the game's memory. */
#include "calendar.h"

#include <assert.h>
#include <stddef.h>

/* The clock, refreshed from the RTC: NitroSDK's RTCDate and RTCTime. */
typedef struct RtcDate {
    u32 year;
    u32 month;
    u32 day;
    u32 weekday; /* 0 = Sunday */
} RtcDate;

typedef struct RtcTime {
    u32 hour;
    u32 minute;
    u32 second;
} RtcTime;

extern RtcDate data_021dc744;
extern RtcTime data_021dc754;

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

static const u16 days_before_month[2][12] = {
    {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334},
    {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335},
};

/* Days from 1 January 2000. REQUIRES: a valid date. */
static int day_number(const Date *date)
{
    int year = date->year;
    return 365 * year + (year + 3) / 4 + days_before_month[is_leap(year)][date->month - 1] + date->day - 1;
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

/* func_0209de24. REQUIRES: month 1-12. */
u8 Calendar_DaysInMonth(u32 year, u32 month)
{
    return days_in_month[is_leap(year)][month - 1];
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
