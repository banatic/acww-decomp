/* The town's weekly schedule of events (data_021f39c0, at 0x17218 of the state block): an event
 * for each weekday from Monday (1) to Friday (5), drawn again at the start of each week
 * (EventSchedule_Update) on the days the calendar (event_calendar.h) has nothing for: the fox
 * (EVENT_CALENDAR_FOX) on the day set at 0x10, then two events picked at random by weight from
 * seven (data_020ca4ec, weights data_020ca4d0) that were not held the week before, then up to
 * two of event 0x45. The schedule's day for "today" runs from 6:00 to 6:00 the next day.
 *
 * A day's event waits until the calendar has it on, runs, and is over once the calendar says it
 * is (EventSchedule_HourlyCheck, EventSchedule_EndPastDays); each player who took part has a bit
 * in the day's `players` (0xff for all). */
#ifndef CLEAN_MAIN_EVENT_SCHEDULE_H
#define CLEAN_MAIN_EVENT_SCHEDULE_H

#include "calendar.h"
#include "event_calendar.h"
#include "types.h"

#define EVENT_SCHEDULE_DAYS 5   /* Monday to Friday */
#define EVENT_SCHEDULE_PICKS 7  /* the events of data_020ca4ec */
#define EVENT_SCHEDULE_RANDOM 2 /* the days given a random event, and those given event 0x45 */
#define EVENT_SCHEDULE_HOUR 6   /* before it, the schedule's today is still the day before */
#define EVENT_SCHEDULE_ALL 0xff /* EventScheduleDay.players: every player */

/* The record number whose part is told only by EVENT_SCHEDULE_ALL (EventSchedule_HasTakenPart). */
#define EVENT_SCHEDULE_RECORD_7 7

/* EventScheduleDay.state */
enum EventScheduleState {
    EVENT_SCHEDULE_WAITING = 0,
    EVENT_SCHEDULE_RUNNING = 1,
    EVENT_SCHEDULE_OVER = 2,
};

typedef struct EventScheduleDay {
    u8 day; /* the date it is for */
    u8 month;
    u8 event;   /* 0x02: EVENT_CALENDAR_NONE for none */
    u8 state;   /* 0x03: enum EventScheduleState */
    u8 marked;  /* 0x04: the fox's letters went out, or EventSchedule_MarkToday (0x3e-0x45) */
    u8 players; /* 0x05: a bit for each player who took part */
} EventScheduleDay;

typedef struct EventSchedule {
    u8 unk_00[8];
    Date no_3c_from;  /* 0x08: event 0x3c is not held in the 7 days from it (1 Jan 2000: none) */
    Date no_fox_from; /* 0x0c: nor is the fox */
    u8 fox_day;       /* 0x10: the fox's weekday (1-5), set by overlay 71 */
    u8 unk_11;
    u8 today_event;                             /* 0x12 */
    u8 today_weekday;                           /* 0x13 */
    EventScheduleDay days[EVENT_SCHEDULE_DAYS]; /* 0x14 */
    u8 unk_32[2];
    DateTime week; /* 0x34: midnight of the Sunday of the week drawn for */
} EventSchedule;

void EventSchedule_EndDay(EventScheduleDay *day);
void EventSchedule_SetDay(EventScheduleDay *day, u8 event, const DateTime *date);
void EventSchedule_ClearDay(EventScheduleDay *day);
int EventSchedule_IsExcluded(int event, u8 weekday);
void EventSchedule_MarkTakenPart(int event);
EventScheduleDay *EventSchedule_Today(EventSchedule *unused);
EventScheduleDay *EventSchedule_Day(EventSchedule *schedule, int weekday);
void EventSchedule_LoadTodayPlayers(EventSchedule *unused);
void EventSchedule_UpdateToday(EventSchedule *schedule);
int EventSchedule_HasTakenPart(int event);
int EventSchedule_FoxBarred(EventKey date);
void EventSchedule_Bar3c(int previous, int set);
int EventSchedule_3cBarred(EventKey date);
void EventSchedule_WeekEdge(DateTime *out, int previous);
void EventSchedule_MarkToday(u32 event);
int EventSchedule_IndexOf(EventSchedule *schedule, int event);
void EventSchedule_HourlyCheck(void);
void EventSchedule_UpdateTown(void);
void EventSchedule_Update(EventSchedule *schedule, int redraw);
void EventSchedule_EndPastDays(EventSchedule *schedule);
void EventSchedule_PlaceFox(EventSchedule *schedule, int *free_days, int *free_count, const DateTime *week);
void EventSchedule_Place45(EventSchedule *schedule, int *free_days, int *free_count, const DateTime *week);
void EventSchedule_PlaceRandom(EventSchedule *schedule, int *free_days, int *free_count, u8 *previous, const DateTime *week);
void EventSchedule_Clear(EventSchedule *schedule);
int EventSchedule_PickEvent(EventSchedule *unused, const u8 *previous);
int EventSchedule_Holds(EventSchedule *unused, const u8 *events, u8 event);
int EventSchedule_PickFreeDay(EventSchedule *unused, int *free_days, int free_count);
int EventSchedule_CountFreeDays(EventSchedule *unused, int *free_days, DateTime *week);
void EventSchedule_FinishStart(EventSchedule *schedule);
void EventSchedule_Construct(EventSchedule *schedule);
void EventSchedule_Reset(EventSchedule *schedule);
void EventSchedule_Destruct(EventSchedule *schedule);
void EventSchedule_ClearWeek(EventSchedule *schedule);

#endif
