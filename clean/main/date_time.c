/* Arithmetic on a date with its time of day: moving it by an amount of each unit, carrying
 * into or borrowing from the next larger one, and comparing two of them.
 *
 * Years are kept in two digits (2000-2099), so they wrap at 100 (DateTime_AddYears). */
#include "date_time.h"

#include <stddef.h>

#include "clean.h"

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* func_0209e040: `when` moved back by `amount`, a count of each unit in DateTime's fields. */
void DateTime_Subtract(DateTime *when, const DateTime *amount)
{
    DateTime_SubtractSeconds(when, amount->second);
    DateTime_SubtractMinutes(when, amount->minute);
    DateTime_SubtractHours(when, amount->hour);
    DateTime_SubtractDays(when, amount->day);
    DateTime_SubtractMonths(when, amount->month);
    DateTime_SubtractYears(when, amount->year);
}
CLEAN_AS(func_0209e040, DateTime_Subtract)

/* `value` less `amount` in a unit of `size` (60 seconds, 60 minutes, 24 hours): the units
 * borrowed from the next larger one, and in `value` what is left. REQUIRES: amount >= 0. */
static int borrow(int *value, int amount, int size)
{
    int left = *value - amount;
    int borrowed = 0;
    if (left < 0) {
        borrowed = (size - 1 - left) / size;
        left += size * borrowed;
    }
    *value = left;
    return borrowed;
}

/* func_0209e080 */
void DateTime_SubtractSeconds(DateTime *when, int seconds)
{
    int second = when->second;
    int minutes = borrow(&second, seconds, 60);
    if (minutes != 0) {
        DateTime_SubtractMinutes(when, minutes);
    }
    when->second = (u8) second;
}
CLEAN_AS(func_0209e080, DateTime_SubtractSeconds)

/* func_0209e0c0 */
void DateTime_SubtractMinutes(DateTime *when, int minutes)
{
    int minute = when->minute;
    int hours = borrow(&minute, minutes, 60);
    if (hours != 0) {
        DateTime_SubtractHours(when, hours);
    }
    when->minute = (u8) minute;
}
CLEAN_AS(func_0209e0c0, DateTime_SubtractMinutes)

/* func_0209e100 */
void DateTime_SubtractHours(DateTime *when, int hours)
{
    int hour = when->hour;
    int days = borrow(&hour, hours, 24);
    if (days != 0) {
        DateTime_SubtractDays(when, days);
    }
    when->hour = (u8) hour;
}
CLEAN_AS(func_0209e100, DateTime_SubtractHours)

/* The length of the month before `when`'s.
 * QUIRK: before January the game takes December of the same year, not the year before; both
 * have 31 days. */
static int days_in_previous_month(const DateTime *when)
{
    return Calendar_DaysInMonth(when->year, when->month == 1 ? 12 : (u8) (when->month - 1));
}

/* func_0209e140 */
void DateTime_SubtractDays(DateTime *when, int days)
{
    int day = when->day - days;
    while (day <= 0) {
        day += days_in_previous_month(when);
        DateTime_SubtractMonths(when, 1);
    }
    when->day = (u8) day;
}
CLEAN_AS(func_0209e140, DateTime_SubtractDays)

/* func_0209e1ac. Months count from 1, so the borrow is taken below 1. */
void DateTime_SubtractMonths(DateTime *when, int months)
{
    int month = when->month - months;
    if (month < 1) {
        int years = (12 - month) / 12;
        month += 12 * years;
        DateTime_SubtractYears(when, years);
    }
    when->month = (u8) month;
}
CLEAN_AS(func_0209e1ac, DateTime_SubtractMonths)

/* func_0209e1f0. REQUIRES: years <= 100. */
void DateTime_SubtractYears(DateTime *when, int years)
{
    int year = when->year - years;
    if (year < 0) {
        year += 100;
    }
    when->year = (u8) year;
}
CLEAN_AS(func_0209e1f0, DateTime_SubtractYears)

/* func_0209e200 */
void DateTime_AddSeconds(DateTime *when, int seconds)
{
    int second = when->second + seconds;
    if (second >= 60) {
        DateTime_AddMinutes(when, second / 60);
        second %= 60;
    }
    when->second = (u8) second;
}
CLEAN_AS(func_0209e200, DateTime_AddSeconds)

/* func_0209e234 */
void DateTime_AddMinutes(DateTime *when, int minutes)
{
    int minute = when->minute + minutes;
    if (minute >= 60) {
        DateTime_AddHours(when, minute / 60);
        minute %= 60;
    }
    when->minute = (u8) minute;
}
CLEAN_AS(func_0209e234, DateTime_AddMinutes)

/* func_0209e268 */
void DateTime_AddHours(DateTime *when, int hours)
{
    int hour = when->hour + hours;
    if (hour >= 24) {
        DateTime_AddDays(when, hour / 24);
        hour %= 24;
    }
    when->hour = (u8) hour;
}
CLEAN_AS(func_0209e268, DateTime_AddHours)

/* func_0209e29c */
void DateTime_AddDays(DateTime *when, int days)
{
    int day = when->day + days;
    int length = Calendar_DaysInMonth(when->year, when->month);
    while (day > length) {
        day -= length;
        DateTime_AddMonths(when, 1);
        length = Calendar_DaysInMonth(when->year, when->month);
    }
    when->day = (u8) day;
}
CLEAN_AS(func_0209e29c, DateTime_AddDays)

/* func_0209e2d0.
 * BUG: months count from 1, but the carry is taken as if from 0: a sum that is a multiple of
 * 12 above 12 (December plus 12 months, for one) carries a year too many and leaves month 0.
 * Adding one month at a time, as DateTime_AddDays does, never meets it. */
void DateTime_AddMonths(DateTime *when, int months)
{
    int month = when->month + months;
#ifdef BUGFIX
    if (month > 12) {
        DateTime_AddYears(when, (month - 1) / 12);
        month = (month - 1) % 12 + 1;
    }
#else
    if (month > 12) {
        DateTime_AddYears(when, month / 12);
        month %= 12;
    }
#endif
    when->month = (u8) month;
}
CLEAN_AS(func_0209e2d0, DateTime_AddMonths)

/* func_0209e304. REQUIRES: years <= 100. */
void DateTime_AddYears(DateTime *when, int years)
{
    int year = when->year + years;
    if (year > 99) {
        year -= 100;
    }
    when->year = (u8) year;
}
CLEAN_AS(func_0209e304, DateTime_AddYears)

/* func_0209e314: midnight at the start of `when`'s week (Sunday) in `start`, which may be
 * `when` itself. Nothing happens without `start`. */
void DateTime_StartOfWeek(const DateTime *when, DateTime *start)
{
    if (start == NULL) {
        return;
    }
    int weekday = Calendar_Weekday((s8) when->year, (s8) when->month, (s8) when->day);
    if (start != when) {
        MI_CpuCopy8(when, start, sizeof(DateTime));
    }
    DateTime_SubtractDays(start, weekday);
    start->hour = 0;
    start->minute = 0;
    start->second = 0;
}
CLEAN_AS(func_0209e314, DateTime_StartOfWeek)

/* func_0209e350: the minutes from `from` to `to`, leaving out the seconds. */
int DateTime_MinutesBetween(const DateTime *from, const DateTime *to)
{
    int days = DateTime_DaysBetween(from, to);
    return days * 24 * 60 + (to->hour - from->hour) * 60 - from->minute + to->minute;
}
CLEAN_AS(func_0209e350, DateTime_MinutesBetween)

/* func_0209e380: the days from `from`'s date to `to`'s. */
int DateTime_DaysBetween(const DateTime *from, const DateTime *to)
{
    Date to_date = {to->day, to->month, to->year, 0};
    Date from_date = {from->day, from->month, from->year, 0};
    return Calendar_DaysFrom(&to_date, &from_date);
}
CLEAN_AS(func_0209e380, DateTime_DaysBetween)

/* func_0209e3ac: -1, 0 or 1 as `a` is before, at or after `b`, looking only at `fields`
 * (enum DateTimeField), from the year down. */
int DateTime_Compare(const DateTime *a, const DateTime *b, int fields)
{
    /* the fields in memory order, the second first: bit n of `fields` is field n */
    const u8 *pa = &a->second;
    const u8 *pb = &b->second;
    for (int field = 5; field >= 0; field--) {
        if (fields & (1 << field)) {
            if (pa[field] < pb[field]) {
                return -1;
            }
            if (pa[field] > pb[field]) {
                return 1;
            }
        }
    }
    return 0;
}
CLEAN_AS(func_0209e3ac, DateTime_Compare)

/* func_0209e474: the clock's date and time. */
void DateTime_Now(DateTime *now)
{
    now->year = (u8) data_021dc744.year;
    now->month = (u8) data_021dc744.month;
    now->day = (u8) data_021dc744.day;
    now->hour = (u8) data_021dc754.hour;
    now->minute = (u8) data_021dc754.minute;
    now->second = (u8) data_021dc754.second;
}
CLEAN_AS(func_0209e474, DateTime_Now)

/* func_0209dfd8: `when` set to `date` at `hour`:`minute`:`second`; its unused bytes are left
 * as they were. */
void DateTime_Set(DateTime *when, const Date *date, u8 hour, u8 minute, u8 second)
{
    when->year = date->year;
    when->month = date->month;
    when->day = date->day;
    when->hour = hour;
    when->minute = minute;
    when->second = second;
}
CLEAN_AS(func_0209dfd8, DateTime_Set)

/* func_0209dffc: 0 when every field of `when` is in its range (seconds and minutes below 60,
 * hours below 24, a day of 1-31, a month of 1-12, a year of 0-99), else 1. The day is not
 * checked against its month's length. */
int DateTime_IsInvalid(const DateTime *when)
{
    BOOL valid = when->second < 60 && when->minute < 60 && when->hour < 24 && when->day >= 1 && when->day <= 31 &&
                 when->month >= 1 && when->month <= 12 && when->year <= 99;
    return valid ? 0 : 1;
}
CLEAN_AS(func_0209dffc, DateTime_IsInvalid)
