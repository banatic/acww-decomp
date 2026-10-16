/* The game's clock: the RTC's date and time moved by an offset the town keeps, read into
 * data_021dc744 (the date) and data_021dc754 (the time) when the game starts and as it asks.
 *
 * The offset (ClockOffset, in the state block) is the town's time less the RTC's: a town
 * whose clock was set to another time keeps that difference, in minutes and seconds. */
#ifndef CLEAN_MAIN_CLOCK_H
#define CLEAN_MAIN_CLOCK_H

#include "calendar.h"
#include "types.h"

/* The clock as one object: data_021dc744 followed by data_021dc754. */
typedef struct RtcClock {
    RtcDate date;
    RtcTime time;
} RtcClock;

/* The town's time less the RTC's (data_021f3b74, at 0x173cc of the state block). */
typedef struct ClockOffset {
    s32 minutes;
    s16 seconds;
    u8 unused[2];
} ClockOffset;

extern ClockOffset data_021f3b74;

int ClockOffset_SecondsTo(ClockOffset *offset, const DateTime *when);
int ClockOffset_MinutesTo(ClockOffset *offset, const DateTime *when);
void ClockOffset_Clear(ClockOffset *offset);
u32 Clock_Seed(void);
int Clock_Second(void);
int Clock_Year(void);
void Clock_ReadRtcDateTime(DateTime *now);
void Clock_GetDateTime(DateTime *now);
void Clock_GetMonthDayHour(u8 *key);
void Clock_GetDayMonth(u8 *day_month);
void Clock_Refresh(const void *skip_check);
void Clock_Init(void);
void Clock_Read(RtcClock *clock);
void Clock_ReadRtc(RtcDate *date, RtcTime *time);

#endif
