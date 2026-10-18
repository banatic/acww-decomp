/* The game's clock (clock.h). */
#include "clock.h"

#include "clean.h"
#include "date_time.h"
#include "town_day.h"

/* The SDK's RTC: starting it, and reading its date and time. The reader at 0211e7c0 is named
 * RTC_SetDateTime in the symbols; the game calls it to read both. */
extern void RTC_Init(void);
extern int RTC_SetDateTime(RtcDate *date, RtcTime *time);

static_assert(sizeof(RtcClock) == 28 && offsetof(RtcClock, time) == 16, "clock layout");
static_assert(sizeof(ClockOffset) == 8 && offsetof(ClockOffset, seconds) == 4, "clock offset layout");

/* A DateTime's eight bytes as one little-endian number, the year above the month and so on
 * down to the second; the two unused bytes are its top. */
static u64 datetime_order(const DateTime *when)
{
    return (u64) when->second | (u64) when->minute << 8 | (u64) when->hour << 16 | (u64) when->day << 24 |
           (u64) when->month << 32 | (u64) when->year << 40 | (u64) when->unused[0] << 48 | (u64) when->unused[1] << 56;
}

/* func_0209db50: the seconds part of the offset that takes the RTC's time to `when`: its
 * second less the RTC's, in 16 bits. `offset` is not read. */
int ClockOffset_SecondsTo(ClockOffset *offset, const DateTime *when)
{
    (void) offset;
    DateTime now;
    Clock_ReadRtcDateTime(&now);
    return (s16) (when->second - now.second);
}
CLEAN_AS(func_0209db50, ClockOffset_SecondsTo)

/* func_0209db78: the minutes from the RTC's time to `when`, negative when `when` is earlier
 * (seconds left out). `offset` is not read.
 * QUIRK: the two are ordered as eight-byte numbers, so `when`'s unused bytes count above its
 * year (the RTC's are 0). */
int ClockOffset_MinutesTo(ClockOffset *offset, const DateTime *when)
{
    (void) offset;
    DateTime now;
    Clock_ReadRtcDateTime(&now);
    if (datetime_order(&now) < datetime_order(when)) {
        return DateTime_MinutesBetween(&now, when);
    }
    return -DateTime_MinutesBetween(when, &now);
}
CLEAN_AS(func_0209db78, ClockOffset_MinutesTo)

/* func_0209dbb4 */
void ClockOffset_Clear(ClockOffset *offset)
{
    offset->minutes = 0;
    offset->seconds = 0;
}
CLEAN_AS(func_0209dbb4, ClockOffset_Clear)

/* func_0209dbbc: the minute, day, hour and second in one word, a byte each from the lowest
 * (the game seeds a random number generator with it). */
u32 Clock_Seed(void)
{
    return data_021dc754.minute | data_021dc744.day << 8 | data_021dc754.hour << 16 | data_021dc754.second << 24;
}
CLEAN_AS(func_0209dbbc, Clock_Seed)

/* CARDi_GetTargetMode (the symbols' name for it): the clock's second. */
int Clock_Second(void)
{
    return (int) data_021dc754.second;
}
CLEAN_AS(CARDi_GetTargetMode, Clock_Second)

/* func_0209dee8: the clock's year (0-99). */
int Clock_Year(void)
{
    return (int) data_021dc744.year;
}
CLEAN_AS(func_0209dee8, Clock_Year)

/* func_0209df04: the RTC's date and time, without the town's offset. */
void Clock_ReadRtcDateTime(DateTime *now)
{
    RtcDate date;
    RtcTime time;
    Clock_ReadRtc(&date, &time);
    *now = (DateTime){
        .second = (u8) time.second,
        .minute = (u8) time.minute,
        .hour = (u8) time.hour,
        .day = (u8) date.day,
        .month = (u8) date.month,
        .year = (u8) date.year,
    };
}
CLEAN_AS(func_0209df04, Clock_ReadRtcDateTime)

/* func_0209df38: the clock's date and time, the unused bytes cleared. */
void Clock_GetDateTime(DateTime *now)
{
    *now = (DateTime){
        .second = (u8) data_021dc754.second,
        .minute = (u8) data_021dc754.minute,
        .hour = (u8) data_021dc754.hour,
        .day = (u8) data_021dc744.day,
        .month = (u8) data_021dc744.month,
        .year = (u8) data_021dc744.year,
    };
}
CLEAN_AS(func_0209df38, Clock_GetDateTime)

/* func_0209df7c: four bytes, the weekday, hour, day and month, which its callers read as one
 * little-endian word to compare with ranges of month, day and hour. */
void Clock_GetMonthDayHour(u8 *key)
{
    key[0] = (u8) data_021dc744.weekday;
    key[1] = (u8) data_021dc754.hour;
    key[2] = (u8) data_021dc744.day;
    key[3] = (u8) data_021dc744.month;
}
CLEAN_AS(func_0209df7c, Clock_GetMonthDayHour)

/* func_0209df94 */
void Clock_GetDayMonth(u8 *day_month)
{
    day_month[0] = (u8) data_021dc744.day;
    day_month[1] = (u8) data_021dc744.month;
}
CLEAN_AS(func_0209df94, Clock_GetDayMonth)

/* func_0209dfa4: the clock read again; then, unless `skip_check` is set, func_020469f4. */
void Clock_Refresh(const void *skip_check)
{
    Clock_Read((RtcClock *) &data_021dc744);
    if (skip_check == NULL) {
        TownDay_OnClock();
    }
}
CLEAN_AS(func_0209dfa4, Clock_Refresh)

/* func_0209dfc0: the RTC started and the clock read. */
void Clock_Init(void)
{
    RTC_Init();
    Clock_Read((RtcClock *) &data_021dc744);
}
CLEAN_AS(func_0209dfc0, Clock_Init)

/* func_0209e49c: the RTC's date and time into `clock`, then moved by the town's offset (the
 * minutes first, then the seconds) with the weekday worked out again for the date reached. */
void Clock_Read(RtcClock *clock)
{
    RtcDate date;
    RtcTime time;
    Clock_ReadRtc(&date, &time);
    clock->date = date;
    clock->time = time;

    int minutes = data_021f3b74.minutes;
    int seconds = data_021f3b74.seconds;
    DateTime when = {
        .second = (u8) time.second,
        .minute = (u8) time.minute,
        .hour = (u8) time.hour,
        .day = (u8) date.day,
        .month = (u8) date.month,
        .year = (u8) date.year,
    };
    if (minutes < 0) {
        DateTime_SubtractMinutes(&when, -minutes);
    } else {
        DateTime_AddMinutes(&when, minutes);
    }
    /* QUIRK: the negated seconds are kept in 16 bits, so -32768 stays negative. */
    if (seconds < 0) {
        DateTime_SubtractSeconds(&when, (s16) -seconds);
    } else {
        DateTime_AddSeconds(&when, seconds);
    }

    date.year = when.year;
    date.month = when.month;
    date.day = when.day;
    time.hour = when.hour;
    time.minute = when.minute;
    time.second = when.second;
    date.weekday = (u32) Calendar_Weekday(when.year, when.month, when.day);
    clock->date = date;
    clock->time = time;
}
CLEAN_AS(func_0209e49c, Clock_Read)

/* func_0209e5b4: the RTC's date and time.
 * QUIRK: on 1 January 2000 (the date of a clock that was reset), the weekday is set to 6,
 * Saturday, which that day was. */
void Clock_ReadRtc(RtcDate *date, RtcTime *time)
{
    RTC_SetDateTime(date, time);
    if (date->year == 0 && date->month == 1 && date->day == 1) {
        date->weekday = 6;
    }
}
CLEAN_AS(func_0209e5b4, Clock_ReadRtc)
