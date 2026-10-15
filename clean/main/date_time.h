/* Arithmetic on a date with its time of day (DateTime, calendar.h). */
#ifndef CLEAN_MAIN_DATE_TIME_H
#define CLEAN_MAIN_DATE_TIME_H

#include "calendar.h"

/* The fields DateTime_Compare looks at. */
enum DateTimeField {
    DATE_TIME_SECOND = 1 << 0,
    DATE_TIME_MINUTE = 1 << 1,
    DATE_TIME_HOUR = 1 << 2,
    DATE_TIME_DAY = 1 << 3,
    DATE_TIME_MONTH = 1 << 4,
    DATE_TIME_YEAR = 1 << 5
};

void DateTime_Subtract(DateTime *when, const DateTime *amount);
void DateTime_SubtractSeconds(DateTime *when, int seconds);
void DateTime_SubtractMinutes(DateTime *when, int minutes);
void DateTime_SubtractHours(DateTime *when, int hours);
void DateTime_SubtractDays(DateTime *when, int days);
void DateTime_SubtractMonths(DateTime *when, int months);
void DateTime_SubtractYears(DateTime *when, int years);
void DateTime_AddSeconds(DateTime *when, int seconds);
void DateTime_AddMinutes(DateTime *when, int minutes);
void DateTime_AddHours(DateTime *when, int hours);
void DateTime_AddDays(DateTime *when, int days);
void DateTime_AddMonths(DateTime *when, int months);
void DateTime_AddYears(DateTime *when, int years);
void DateTime_StartOfWeek(const DateTime *when, DateTime *start);
int DateTime_MinutesBetween(const DateTime *from, const DateTime *to);
int DateTime_DaysBetween(const DateTime *from, const DateTime *to);
int DateTime_Compare(const DateTime *a, const DateTime *b, int fields);
void DateTime_Now(DateTime *now);

#endif
