/* Dates and times as the game keeps them. */
#ifndef CLEAN_MAIN_CALENDAR_H
#define CLEAN_MAIN_CALENDAR_H

#include "types.h"

/* A date: years count from 2000 (the clock only knows 2000-2099), months and days from 1. The
 * game builds them in four bytes and clears the last. */
typedef struct Date {
    u8 day;
    u8 month;
    u8 year;
    u8 unused;
} Date;

/* A time of day. */
typedef struct Time {
    u8 minute;
    u8 hour;
} Time;

/* The time with seconds and the date, as Calendar's callers get them from the clock. */
typedef struct DateTime {
    u8 second;
    u8 minute;
    u8 hour;
    u8 day;
    u8 month;
    u8 year;
    u8 unused[2];
} DateTime;

enum PartOfDay {
    PART_OF_DAY_MORNING,   /* 5:00-11:59 */
    PART_OF_DAY_AFTERNOON, /* 12:00-16:59 */
    PART_OF_DAY_EVENING,   /* 17:00-23:59 */
    PART_OF_DAY_NIGHT      /* 0:00-4:59 */
};

BOOL Calendar_IsOnOrAfter(const Date *date, const Date *other);
int Calendar_DaysFrom(const Date *date, const Date *origin);
void Calendar_AddTime(Time time, Time delta, Time *sum);
u8 Calendar_DaysInMonth(u32 year, u32 month);
int Calendar_NthWeekday(int year, int month, int weekday, int n);
int Calendar_Weekday(s8 year, s8 month, s8 day);
int Calendar_PartOfDay(void);
void Calendar_Today(Date *today);
int Calendar_TodayWeekday(void);
void Calendar_Now(Time *now);
int Calendar_PeriodA(const Date *date);
int Calendar_PeriodB(const Date *date);
int Calendar_PeriodAOf(const DateTime *when);
int Calendar_PeriodBOf(const DateTime *when);

#endif
