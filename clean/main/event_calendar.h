/* The town's calendar of events: a table of 99 events (data_020dac08), each with a rule for the
 * date and hour it starts and one for when it ends, and the events of today kept in a list
 * (data_021c74d4, at most seven) for the date in data_021c74d0.
 *
 * Dates and hours are compared as one word, an EventKey: the month in bits 24-31, the day in
 * bits 16-23, the hour in bits 8-15 and, in a key made from a date, its weekday (0 = Sunday)
 * in bits 0-7. An event is listed for a date when its start's date is on or before it and its
 * end's date on or after it, and no event already listed for that date with a kind as low or
 * lower overlaps it (EventCalendar_IsBlocked).
 *
 * A rule (EventRule) gives the date in one of eight ways (its kind, bits 13-15 of its flags):
 *
 *   0  a month from bits 11-12 (EventCalendar_RuleMonth), the day from EventCalendar_RuleDay
 *   1  the current player's birthday
 *   2  the birthday of the villager the event's number names
 *   3  the date's month if it is one of 1-5 or 10-12, else January; the day from RuleDay
 *   4  the date's month if it is one of 6-9, else June; the day from RuleDay
 *   5  the n-th (bits 8-10) weekday (bits 1-3) of the month in bits 4-7
 *   6  the day of the town's weekly schedule (event_schedule.h) that holds the event, or for
 *      events 0x61 and 0x62 fixed dates around the new year
 *   7  none
 *
 * and moves it by `days` when bit 0 is set. A date past its month's last day runs on into the
 * next month.
 *
 * EventCalendar_State tells how an event stands at a date and time (EventCalendarState); the
 * process of vtable data_020dabc0 keeps today's list fresh and the schedule's states with it. */
#ifndef CLEAN_MAIN_EVENT_CALENDAR_H
#define CLEAN_MAIN_EVENT_CALENDAR_H

#include "calendar.h"
#include "types.h"

#define EVENT_CALENDAR_EVENTS 99    /* entries of data_020dac08 */
#define EVENT_CALENDAR_DAY_EVENTS 7 /* the most events listed for one date */

/* An event number for none. */
#define EVENT_CALENDAR_NONE 0x63

/* Event numbers with code of their own. 0x3d is the fox's (fox_shop.h): its letters go out
 * the day before its day of the schedule (EventSchedule_Update). */
#define EVENT_CALENDAR_EVENT_0B 0x0b
#define EVENT_CALENDAR_EVENT_16 0x16
#define EVENT_CALENDAR_EVENT_18 0x18
#define EVENT_CALENDAR_EVENT_19 0x19
#define EVENT_CALENDAR_EVENT_29 0x29
#define EVENT_CALENDAR_EVENT_2A 0x2a
#define EVENT_CALENDAR_EVENT_3C 0x3c
#define EVENT_CALENDAR_FOX 0x3d
#define EVENT_CALENDAR_EVENT_40 0x40
#define EVENT_CALENDAR_EVENT_44 0x44
#define EVENT_CALENDAR_EVENT_45 0x45
#define EVENT_CALENDAR_EVENT_48 0x48
#define EVENT_CALENDAR_EVENT_60 0x60 /* looked up in the schedule as 0x40 */
#define EVENT_CALENDAR_EVENT_61 0x61
#define EVENT_CALENDAR_EVENT_62 0x62

/* Event kinds (EventCalendarEntry.kind). An event of kind 5 is listed whatever else is; a
 * listed event blocks those of its kind or higher that overlap it. Kind 2 and above wait for
 * the paired town (paired_town.h), kind 3 also for the statistics record (wfc_stats.h); kind 4
 * is held only on a day of the schedule that has it. */
#define EVENT_CALENDAR_KIND_4 4
#define EVENT_CALENDAR_KIND_FREE 5

/* A date, an hour and a weekday packed as the calendar compares them. */
typedef u32 EventKey;

#define EVENT_KEY_MONTH(key) ((u8) ((key) >> 24))
#define EVENT_KEY_DAY(key) ((u8) ((key) >> 16))
#define EVENT_KEY_HOUR(key) ((u8) ((key) >> 8))
#define EVENT_KEY_WEEKDAY(key) ((u8) (key))
#define EVENT_KEY_DATE_MASK 0xffff0000u /* the month and the day */
#define EVENT_KEY_MAKE(month, day, hour, weekday)                                                                             \
    ((EventKey) (u8) (month) << 24 | (EventKey) (u8) (day) << 16 | (EventKey) (u8) (hour) << 8 | (EventKey) (u8) (weekday))

/* The bytes of an EventKey in memory. */
#define EVENT_KEY_BYTE_WEEKDAY 0
#define EVENT_KEY_BYTE_HOUR 1
#define EVENT_KEY_BYTE_DAY 2
#define EVENT_KEY_BYTE_MONTH 3

/* EventRule.flags */
#define EVENT_RULE_MOVE 0x0001 /* move the date by EventRule.days */
#define EVENT_RULE_WEEKDAY(flags) (((flags) >> 1) & 7)
#define EVENT_RULE_MONTH(flags) (((flags) >> 4) & 0xf)
#define EVENT_RULE_WEEK(flags) (((flags) >> 8) & 7)
#define EVENT_RULE_MONTH_MODE(flags) (((flags) >> 11) & 3)
#define EVENT_RULE_KIND(flags) (((flags) >> 13) & 7)

enum EventRuleKind {
    EVENT_RULE_COMPUTED = 0,
    EVENT_RULE_PLAYER_BIRTHDAY = 1,
    EVENT_RULE_VILLAGER_BIRTHDAY = 2,
    EVENT_RULE_MONTHS_1_5_10_12 = 3,
    EVENT_RULE_MONTHS_6_9 = 4,
    EVENT_RULE_NTH_WEEKDAY = 5,
    EVENT_RULE_SCHEDULE = 6,
    EVENT_RULE_NONE = 7,
};

/* How the day of a rule is found (EVENT_RULE_WEEK, EventCalendar_RuleDay). */
enum EventRuleWeek {
    EVENT_RULE_DAY_FIXED = 0, /* EventRule.days is the day */
    EVENT_RULE_DAY_LAST = 6,  /* the month's last day on the date's weekday */
    EVENT_RULE_DAY_NEXT = 7   /* the rule's weekday on or after the date */
    /* 1-5: the n-th of the rule's weekday */
};

/* How the month of a rule of kind 0 is found (EVENT_RULE_MONTH_MODE, EventCalendar_RuleMonth). */
enum EventRuleMonthMode {
    EVENT_RULE_MONTH_FIXED = 0,  /* EVENT_RULE_MONTH */
    EVENT_RULE_MONTH_AHEAD = 1,  /* the date's month, or that of the date moved by `days` */
    EVENT_RULE_MONTH_PARITY = 2, /* the date's month or the next, odd (rule month 1) or even */
};

typedef struct EventRule {
    u32 flags; /* EVENT_RULE_* */
    s32 days;  /* 0x04: the day (EVENT_RULE_DAY_FIXED) or the days to move the date by */
    s32 hour;  /* 0x08 */
} EventRule;

/* An entry of data_020dac08. */
typedef struct EventCalendarEntry {
    u16 id;
    u16 kind;        /* 0x02 */
    EventRule start; /* 0x04 */
    EventRule end;   /* 0x10 */
} EventCalendarEntry;

/* An event listed for a date (the record villager_town.h calls VillagerTownEvent). */
typedef struct EventCalendarEvent {
    u16 id;
    u16 kind;       /* 0x02 */
    EventKey start; /* 0x04 */
    EventKey end;   /* 0x08 */
} EventCalendarEvent;

/* EventCalendar_State */
enum EventCalendarState {
    EVENT_CALENDAR_OFF = 0,    /* not on that date, or over */
    EVENT_CALENDAR_LATER = 1,  /* on that date but not started yet */
    EVENT_CALENDAR_ON = 2,     /* running */
    EVENT_CALENDAR_ENDING = 3, /* running, with 5 minutes or less to go */
};

void EventCalendar_TodaySpan(EventKey *start, EventKey *end, int event);
int EventCalendar_ListAtNoon(EventCalendarEvent *out, int max, const DateTime *when);
EventCalendarEvent *EventCalendar_Today(void);
int EventCalendar_State(int event, const DateTime *when, int use_list);
int EventCalendar_StateOn(int event, const DateTime *when, int use_list);
int EventCalendar_StateIn(int event, const DateTime *when, EventCalendarEvent *list);
EventCalendarEvent *EventCalendar_Find(u16 event, EventCalendarEvent *list);
int EventCalendar_DaysSinceStart(int event);
void EventCalendar_RefreshIfStale(int unused);
void EventCalendar_Refresh(int today_only);
int EventCalendar_ListAll(EventCalendarEvent *out, const DateTime *when);
int EventCalendar_ListOpen(EventCalendarEvent *out, const DateTime *when, int today_only);
int EventCalendar_List(EventCalendarEvent *out, const DateTime *when, int include_taken, int today_only);
int EventCalendar_SpanOn(EventCalendarEvent *event, const EventCalendarEntry *entry, int year, EventKey date);
void EventCalendar_SetDayHours(EventCalendarEvent *event, EventKey date);
int EventCalendar_IsBlocked(const EventCalendarEntry *entry, EventKey date, const EventCalendarEvent *event,
                            const EventCalendarEvent *listed, int count, int include_taken, int today_only);
void EventCalendar_ClearList(EventCalendarEvent *list, int count);
int EventCalendar_EndKey(const EventRule *rule, int year, EventKey date, int event);
int EventCalendar_StartKey(const EventRule *rule, int year, EventKey date, int event);
EventKey EventCalendar_RuleKey(const EventRule *rule, int year, EventKey date, int event);
EventKey EventCalendar_ScheduleKey(const EventRule *rule, int event, EventKey date);
void EventCalendar_VillagerBirthdayKey(const EventRule *rule, EventKey *key, int villager);
int EventCalendar_VillagerCounts(u8 *villager, int moving);
void EventCalendar_PlayerBirthdayKey(const EventRule *rule, EventKey *key);
u8 EventCalendar_RuleDay(const EventRule *rule, int year, EventKey date, int month, int event);
int EventCalendar_RuleMonth(const EventRule *rule, int year, EventKey date, int event);
void EventCalendar_DateDestruct(void *date);
void EventCalendar_DateConstruct(Date *date);

#endif
