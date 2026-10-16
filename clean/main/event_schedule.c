/* The town's weekly schedule of events (event_schedule.h). */
#include "event_schedule.h"

#include "calendar.h"
#include "clean.h"
#include "date_time.h"
#include "event_calendar.h"
#include "fox_shop.h"
#include "player_records.h"
#include "process_020dabc0.h"

static_assert(sizeof(EventScheduleDay) == 6, "EventScheduleDay");
static_assert(offsetof(EventSchedule, no_3c_from) == 0x08, "EventSchedule.no_3c_from");
static_assert(offsetof(EventSchedule, fox_day) == 0x10, "EventSchedule.fox_day");
static_assert(offsetof(EventSchedule, today_event) == 0x12, "EventSchedule.today_event");
static_assert(offsetof(EventSchedule, days) == 0x14, "EventSchedule.days");
static_assert(offsetof(EventSchedule, week) == 0x34, "EventSchedule.week");
static_assert(sizeof(EventSchedule) == 0x3c, "EventSchedule");

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern int func_020644cc(int range); /* a random number below `range` */
/* The days of the week from `week` (its Sunday) the calendar has nothing for at noon: for
 * Monday to Friday 1 in `free_days` when free, else 0; their count. */
extern int func_02041140(EventSchedule *schedule, int *free_days, DateTime *week);

extern EventSchedule data_021f39c0;
extern FoxShop data_021f3b30;
extern u16 data_021c7580; /* today's day's `players`, EVENT_SCHEDULE_ALL without one */
extern u32 data_021c7584; /* the hour the schedule was last checked at */

/* The schedule's random events and their weights. */
extern const int data_020ca4ec[EVENT_SCHEDULE_PICKS];
extern const int data_020ca4d0[EVENT_SCHEDULE_PICKS];

/* `value` shifted as an ARM register shift does: by the low byte of `amount`, 0 from 32 up. */
static u32 arm_lsl(u32 value, u32 amount)
{
    amount &= 0xff;
    return amount < 32 ? value << amount : 0;
}

static u32 arm_lsr(u32 value, u32 amount)
{
    amount &= 0xff;
    return amount < 32 ? value >> amount : 0;
}

/* 1 when `date` (day and month, in `from`'s year) is in the 7 days from `from`; never while
 * `from` is 1 January 2000. */
static int in_week_from(const Date *from, EventKey date)
{
    if (from->year == 0 && from->month == 1 && from->day == 1) {
        return 0;
    }
    Date day = {EVENT_KEY_DAY(date), EVENT_KEY_MONTH(date), from->year, 0};
    int days = Calendar_DaysFrom(&day, from);
    return days >= 0 && days < 7;
}

/* func_020408a8: the day's event over and every player marked, unless it is event 0x45. */
void EventSchedule_EndDay(EventScheduleDay *day)
{
    if (day->event == EVENT_CALENDAR_EVENT_45) {
        return;
    }
    day->players = EVENT_SCHEDULE_ALL;
    day->state = EVENT_SCHEDULE_OVER;
}
CLEAN_AS(func_020408a8, EventSchedule_EndDay)

/* func_020408b8: the day cleared, then given `event` on `date`'s day. */
void EventSchedule_SetDay(EventScheduleDay *day, u8 event, const DateTime *date)
{
    EventSchedule_ClearDay(day);
    day->month = date->month;
    day->day = date->day;
    day->event = event;
}
CLEAN_AS(func_020408b8, EventSchedule_SetDay)

/* func_020408d4: no event, on day 1 of month 0. */
void EventSchedule_ClearDay(EventScheduleDay *day)
{
    day->day = 1;
    day->month = 0;
    day->event = EVENT_CALENDAR_NONE;
    day->state = EVENT_SCHEDULE_WAITING;
    day->marked = 0;
    day->players = 0;
}
CLEAN_AS(func_020408d4, EventSchedule_ClearDay)

/* func_020408e8: 1 when the schedule's day `weekday` holds another event than `event` (0x60
 * taken as 0x40), or holds it and the current player took part; 0 for event 0x45 or a weekday
 * outside 1-5. */
int EventSchedule_IsExcluded(int event, u8 weekday)
{
    if (event == EVENT_CALENDAR_EVENT_45) {
        return 0;
    }
    if (event == EVENT_CALENDAR_EVENT_60) {
        event = EVENT_CALENDAR_EVENT_40;
    }
    EventScheduleDay *day = EventSchedule_Day(&data_021f39c0, weekday);
    if (day == NULL) {
        return 0;
    }
    if (event != day->event) {
        return 1;
    }
    return (arm_lsr(day->players, (u32) PlayerRecords_CurrentNumber()) & 1) != 0;
}
CLEAN_AS(func_020408e8, EventSchedule_IsExcluded)

/* func_0204093c: the current player marked as having taken part in the schedule's day with
 * `event`; every player for event 0x44. */
void EventSchedule_MarkTakenPart(int event)
{
    EventSchedule *schedule = &data_021f39c0;
    EventScheduleDay *day = EventSchedule_Day(schedule, EventSchedule_IndexOf(schedule, event));
    if (day == NULL) {
        return;
    }
    if (event == EVENT_CALENDAR_EVENT_44) {
        day->players = EVENT_SCHEDULE_ALL;
    } else {
        day->players = (u8) (day->players | arm_lsl(1, (u32) PlayerRecords_CurrentNumber()));
    }
}
CLEAN_AS(func_0204093c, EventSchedule_MarkTakenPart)

/* func_02040980: the town schedule's day for today, which before 6:00 is still the day before;
 * NULL at the weekend (and on Monday before 6:00).
 * QUIRK: the schedule passed is not used; the town's (data_021f39c0) is. */
EventScheduleDay *EventSchedule_Today(EventSchedule *unused)
{
    (void) unused;
    int weekday = Calendar_TodayWeekday();
    if (weekday == 0) {
        return NULL;
    }
    DateTime now = {0};
    DateTime_Now(&now);
    if (now.hour < EVENT_SCHEDULE_HOUR) {
        weekday--;
    }
    return EventSchedule_Day(&data_021f39c0, weekday);
}
CLEAN_AS(func_02040980, EventSchedule_Today)

/* func_020409c8: the day of `weekday` (1 Monday - 5 Friday), else NULL. */
EventScheduleDay *EventSchedule_Day(EventSchedule *schedule, int weekday)
{
    if (weekday < 1 || weekday > EVENT_SCHEDULE_DAYS) {
        return NULL;
    }
    return &schedule->days[weekday - 1];
}
CLEAN_AS(func_020409c8, EventSchedule_Day)

/* func_020409e8: data_021c7580 set to the players of today's day (EVENT_SCHEDULE_ALL without
 * one). */
void EventSchedule_LoadTodayPlayers(EventSchedule *unused)
{
    (void) unused;
    data_021c7580 = EVENT_SCHEDULE_ALL;
    EventScheduleDay *day = EventSchedule_Today(&data_021f39c0);
    if (day != NULL) {
        data_021c7580 = day->players;
    }
}
CLEAN_AS(func_020409e8, EventSchedule_LoadTodayPlayers)

/* func_02040a10: today's event and weekday noted in the schedule, and its players loaded;
 * nothing without a day for today. */
void EventSchedule_UpdateToday(EventSchedule *schedule)
{
    u8 weekday = (u8) Calendar_TodayWeekday();
    EventScheduleDay *day = EventSchedule_Today(schedule);
    if (day == NULL) {
        return;
    }
    u8 event = day->event;
    if (weekday != schedule->today_weekday || event != schedule->today_event) {
        schedule->today_event = event;
        schedule->today_weekday = weekday;
    }
    EventSchedule_LoadTodayPlayers(schedule);
}
CLEAN_AS(func_02040a10, EventSchedule_UpdateToday)

/* func_02040a48: 1 when `event` is today's event of the schedule and the current player took
 * part in it (data_021c7580); record number 7 only when every player did. */
int EventSchedule_HasTakenPart(int event)
{
    if (event != data_021f39c0.today_event) {
        return 0;
    }
    int player = PlayerRecords_CurrentNumber();
    if (player == EVENT_SCHEDULE_RECORD_7) {
        return data_021c7580 == EVENT_SCHEDULE_ALL;
    }
    return (arm_lsr(data_021c7580, (u32) player) & 1) != 0;
}
CLEAN_AS(func_02040a48, EventSchedule_HasTakenPart)

/* func_02040a90: 1 when `date` is in the 7 days the fox is barred from. */
int EventSchedule_FoxBarred(EventKey date)
{
    return in_week_from(&data_021f39c0.no_fox_from, date);
}
CLEAN_AS(func_02040a90, EventSchedule_FoxBarred)

/* func_02040adc: event 0x3c barred for the 7 days from the week's edge (EventSchedule_WeekEdge:
 * `previous` 1 for the Saturday before this week, else the Sunday after), or no longer barred
 * (`set` 0). */
void EventSchedule_Bar3c(int previous, int set)
{
    Date *from = &data_021f39c0.no_3c_from;
    if (set == 0) {
        from->day = 1;
        from->month = 1;
        from->year = 0;
        from->unused = 0;
        return;
    }
    DateTime edge = {0};
    EventSchedule_WeekEdge(&edge, previous);
    from->day = edge.day;
    from->month = edge.month;
    from->year = edge.year;
}
CLEAN_AS(func_02040adc, EventSchedule_Bar3c)

/* func_02040b20: 1 when `date` is in the 7 days event 0x3c is barred from. */
int EventSchedule_3cBarred(EventKey date)
{
    return in_week_from(&data_021f39c0.no_3c_from, date);
}
CLEAN_AS(func_02040b20, EventSchedule_3cBarred)

/* func_02040b6c: in `out`, the clock's date and time moved to the Saturday before this week
 * (`previous` 1) or to the Sunday after it. */
void EventSchedule_WeekEdge(DateTime *out, int previous)
{
    DateTime_Now(out);
    if (previous == 1) {
        DateTime_SubtractDays(out, Calendar_TodayWeekday() + 1);
    } else {
        DateTime_AddDays(out, 7 - Calendar_TodayWeekday());
    }
}
CLEAN_AS(func_02040b6c, EventSchedule_WeekEdge)

/* func_02040ba0: today's day marked when it holds `event`, one of 0x3e-0x45. */
void EventSchedule_MarkToday(u32 event)
{
    if (event < 0x3e || event >= 0x46) {
        return;
    }
    EventScheduleDay *day = EventSchedule_Today(&data_021f39c0);
    if (day != NULL && event == day->event) {
        day->marked = 1;
    }
}
CLEAN_AS(func_02040ba0, EventSchedule_MarkToday)

/* func_02040bcc: the weekday (1-5) whose day holds `event`, the first one; 0 for none. */
int EventSchedule_IndexOf(EventSchedule *schedule, int event)
{
    EventScheduleDay *day = EventSchedule_Day(schedule, 1);
    for (int i = 0; i < EVENT_SCHEDULE_DAYS; i++, day++) {
        if (event == day->event) {
            return i + 1;
        }
    }
    return 0;
}
CLEAN_AS(func_02040bcc, EventSchedule_IndexOf)

/* func_02040bfc: once an hour (unless the process is held back), today's day follows its
 * event in the calendar: waiting until it is on, then running until it is over. */
void EventSchedule_HourlyCheck(void)
{
    if (Process020dabc0_IsHeldBack() == 1) {
        return;
    }
    DateTime now = {0};
    DateTime_Now(&now);
    if (data_021c7584 == now.hour) {
        return;
    }
    data_021c7584 = now.hour;

    EventScheduleDay *day = EventSchedule_Today(&data_021f39c0);
    if (day == NULL || day->event == EVENT_CALENDAR_NONE) {
        return;
    }
    DateTime copy;
    MI_CpuCopy8(&now, &copy, sizeof(copy));
    int state = EventCalendar_StateOn(day->event, &copy, 0);
    switch (day->state) {
        case EVENT_SCHEDULE_WAITING:
            if (state == EVENT_CALENDAR_ON) {
                day->state = EVENT_SCHEDULE_RUNNING;
            }
            break;
        case EVENT_SCHEDULE_RUNNING:
            if (state == EVENT_CALENDAR_OFF) {
                EventSchedule_EndDay(day);
            }
            break;
    }
}
CLEAN_AS(func_02040bfc, EventSchedule_HourlyCheck)

/* func_02040c80: the town's schedule updated (EventSchedule_Update). */
void EventSchedule_UpdateTown(void)
{
    EventSchedule_Update(&data_021f39c0, 0);
}
CLEAN_AS(func_02040c80, EventSchedule_UpdateTown)

/* The 8 bytes of a DateTime as the game compares them, as one number. */
static u64 date_time_bits(const DateTime *when)
{
    const u8 *bytes = (const u8 *) when;
    u64 bits = 0;
    for (int i = 7; i >= 0; i--) {
        bits = bits << 8 | bytes[i];
    }
    return bits;
}

/* func_02040c90: the schedule drawn again when this week is not the one it was drawn for (or
 * it never was, or `redraw`): the fox, the random events (not last week's) and event 0x45 on
 * the free days. Then the past days' events ended, and the fox's letters sent on its day or
 * the day before, once. */
void EventSchedule_Update(EventSchedule *schedule, int redraw)
{
    DateTime now = {0};
    DateTime week = {0};
    DateTime copy;

    DateTime_Now(&now);
    u32 weekday = (u32) Calendar_TodayWeekday();
    data_021c7584 = now.hour;
    DateTime_StartOfWeek(&now, &week);

    u64 drawn_for = date_time_bits(&schedule->week);
    if (drawn_for == 0 || drawn_for != date_time_bits(&week) || redraw) {
        u8 previous[EVENT_SCHEDULE_DAYS + 1];
        int free_days[EVENT_SCHEDULE_DAYS];
        EventScheduleDay *day = EventSchedule_Day(schedule, 1);
        for (int i = 0; i < EVENT_SCHEDULE_DAYS; i++, day++) {
            previous[i] = day->event;
        }
        previous[EVENT_SCHEDULE_DAYS] = EVENT_CALENDAR_NONE;
        EventSchedule_Clear(schedule);
        MI_CpuCopy8(&week, &copy, sizeof(copy));
        int free_count = func_02041140(schedule, free_days, &copy);
        MI_CpuCopy8(&week, &copy, sizeof(copy));
        EventSchedule_PlaceFox(schedule, free_days, &free_count, &copy);
        MI_CpuCopy8(&week, &copy, sizeof(copy));
        EventSchedule_PlaceRandom(schedule, free_days, &free_count, previous, &copy);
        MI_CpuCopy8(&week, &copy, sizeof(copy));
        EventSchedule_Place45(schedule, free_days, &free_count, &copy);
        MI_CpuCopy8(&week, &schedule->week, sizeof(schedule->week));
    }

    EventSchedule_EndPastDays(schedule);
    u32 fox = (u32) EventSchedule_IndexOf(schedule, EVENT_CALENDAR_FOX);
    if (fox - weekday <= 1) {
        EventScheduleDay *day = EventSchedule_Day(schedule, (int) fox);
        if (day != NULL && day->marked == 0) {
            FoxShop_SendLetters();
            day->marked = 1;
        }
    }
}
CLEAN_AS(func_02040c90, EventSchedule_Update)

/* func_02040da8: today noted (EventSchedule_UpdateToday), then the events of the days from
 * Monday to today ended (EventSchedule_EndDay) that the calendar does not have on now; those of
 * event 0x45 before today are passed to EventSchedule_EndDay too, which leaves them. */
void EventSchedule_EndPastDays(EventSchedule *schedule)
{
    DateTime now = {0};
    DateTime copy;
    EventCalendarEvent today[EVENT_CALENDAR_DAY_EVENTS];

    int weekday = Calendar_TodayWeekday();
    DateTime_Now(&now);
    EventSchedule_UpdateToday(schedule);
    MI_CpuCopy8(&now, &copy, sizeof(copy));
    EventCalendar_ListAll(today, &copy);
    DateTime_Now(&now);
    int last = weekday - 1;
    for (int i = 0; i <= last; i++) {
        EventScheduleDay *day = EventSchedule_Day(schedule, i + 1);
        if (day == NULL || day->event == EVENT_CALENDAR_NONE) {
            continue;
        }
        MI_CpuCopy8(&now, &copy, sizeof(copy));
        if (EventCalendar_StateIn(day->event, &copy, today) == EVENT_CALENDAR_OFF) {
            EventSchedule_EndDay(day);
        } else if (i != last && day->event == EVENT_CALENDAR_EVENT_45) {
            EventSchedule_EndDay(day);
        }
    }
}
CLEAN_AS(func_02040da8, EventSchedule_EndPastDays)

/* func_02040e44: the fox put on its weekday (fox_day) when that day is free and not in the
 * days it is barred from; one free day fewer.
 * BUG: fox_day is not checked before its free day is read: 0 reads the word before
 * `free_days` and 6 or more the words after it (read here the same way); no day of the
 * schedule is found for those, so nothing more is written. */
void EventSchedule_PlaceFox(EventSchedule *schedule, int *free_days, int *free_count, const DateTime *week)
{
    if (*free_count <= 0) {
        return;
    }
    int fox_day = data_021f39c0.fox_day;
    int *free = (int *) ((uintptr_t) free_days + (uintptr_t) ((u32) (fox_day - 1) * sizeof(int)));
    if (*free == 0) {
        return;
    }

    DateTime now = {0};
    DateTime date = {0};
    DateTime_Now(&now);
    MI_CpuCopy8(&now, &date, sizeof(date));
    int ahead = fox_day - Calendar_TodayWeekday();
    if (ahead >= 0) {
        DateTime_AddDays(&date, ahead);
    } else {
        DateTime_SubtractDays(&date, -ahead);
    }
    /* QUIRK: the game leaves the key's hour and weekday bytes as they were on its stack; they
     * are not read. */
    if (EventSchedule_FoxBarred(EVENT_KEY_MAKE(date.month, date.day, 0, 0))) {
        return;
    }
    EventScheduleDay *day = EventSchedule_Day(schedule, fox_day);
    if (day == NULL) {
        return;
    }
    DateTime on = {0};
    DateTime copy;
    *free = 0;
    *free_count -= 1;
    MI_CpuCopy8(week, &on, sizeof(on));
    DateTime_AddDays(&on, fox_day);
    MI_CpuCopy8(&on, &copy, sizeof(copy));
    EventSchedule_SetDay(day, EVENT_CALENDAR_FOX, &copy);
}
CLEAN_AS(func_02040e44, EventSchedule_PlaceFox)

/* func_02040f04: event 0x45 put on up to two free days picked at random. */
void EventSchedule_Place45(EventSchedule *schedule, int *free_days, int *free_count, const DateTime *week)
{
    for (int i = 0; i < EVENT_SCHEDULE_RANDOM; i++) {
        int event = EVENT_CALENDAR_NONE;
        if (*free_count <= 0) {
            continue;
        }
        int index = EventSchedule_PickFreeDay(schedule, free_days, *free_count);
        if (index >= 0) {
            event = EVENT_CALENDAR_EVENT_45;
            free_days[index] = 0;
            *free_count -= 1;
        }
        EventScheduleDay *day = EventSchedule_Day(schedule, index + 1);
        if (day != NULL) {
            DateTime on = {0};
            DateTime copy;
            MI_CpuCopy8(week, &on, sizeof(on));
            DateTime_AddDays(&on, index + 1);
            MI_CpuCopy8(&on, &copy, sizeof(copy));
            EventSchedule_SetDay(day, (u8) event, &copy);
        }
    }
}
CLEAN_AS(func_02040f04, EventSchedule_Place45)

/* func_02040f8c: two free days picked at random, each given an event picked at random that is
 * not in `previous` (last week's five, then the one picked before: the pick is kept in
 * previous[5]). */
void EventSchedule_PlaceRandom(EventSchedule *schedule, int *free_days, int *free_count, u8 *previous, const DateTime *week)
{
    for (int i = 0; i < EVENT_SCHEDULE_RANDOM; i++) {
        int event = EVENT_CALENDAR_NONE;
        if (*free_count > 0) {
            int index = EventSchedule_PickFreeDay(schedule, free_days, *free_count);
            if (index >= 0) {
                event = EventSchedule_PickEvent(schedule, previous);
                free_days[index] = 0;
                *free_count -= 1;
            }
            EventScheduleDay *day = EventSchedule_Day(schedule, index + 1);
            if (day != NULL) {
                DateTime on = {0};
                DateTime copy;
                MI_CpuCopy8(week, &on, sizeof(on));
                DateTime_AddDays(&on, index + 1);
                MI_CpuCopy8(&on, &copy, sizeof(copy));
                EventSchedule_SetDay(day, (u8) event, &copy);
            }
        }
        previous[EVENT_SCHEDULE_DAYS] = (u8) event;
    }
}
CLEAN_AS(func_02040f8c, EventSchedule_PlaceRandom)

/* func_0204101c: every day cleared, and the fox's password ended and a new one picked. */
void EventSchedule_Clear(EventSchedule *schedule)
{
    EventScheduleDay *day = EventSchedule_Day(schedule, 1);
    for (int i = 0; i < EVENT_SCHEDULE_DAYS; i++, day++) {
        EventSchedule_ClearDay(day);
    }
    FoxPassword_End(FoxShop_Password(&data_021f3b30));
    FoxPassword_Pick(FoxShop_Password(&data_021f3b30));
}
CLEAN_AS(func_0204101c, EventSchedule_Clear)

/* func_0204105c: one of the schedule's random events not in `previous`, picked by weight;
 * EVENT_CALENDAR_NONE when none is left. */
int EventSchedule_PickEvent(EventSchedule *unused, const u8 *previous)
{
    int events[EVENT_SCHEDULE_PICKS];
    int weights[EVENT_SCHEDULE_PICKS];
    int count = 0;
    int total = 0;

    for (int i = 0; i < EVENT_SCHEDULE_PICKS; i++) {
        events[i] = EVENT_CALENDAR_NONE;
        weights[i] = 0;
    }
    for (int i = 0; i < EVENT_SCHEDULE_PICKS; i++) {
        if (!EventSchedule_Holds(unused, previous, (u8) data_020ca4ec[i])) {
            events[count] = data_020ca4ec[i];
            weights[count] = data_020ca4d0[i];
            count++;
            total += data_020ca4d0[i];
        }
    }
    if (total > 0) {
        int left = func_020644cc(total);
        for (int i = 0; i < count; i++) {
            left -= weights[i];
            if (left < 0) {
                return events[i];
            }
        }
    }
    return EVENT_CALENDAR_NONE;
}
CLEAN_AS(func_0204105c, EventSchedule_PickEvent)

/* func_020410ec: 1 when `event` is one of the six `events` (none never is). */
int EventSchedule_Holds(EventSchedule *unused, const u8 *events, u8 event)
{
    (void) unused;
    for (int i = 0; i <= EVENT_SCHEDULE_DAYS; i++) {
        if (events[i] != EVENT_CALENDAR_NONE && events[i] == event) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_020410ec, EventSchedule_Holds)

/* func_02041110: the index (0-4) of a free day picked at random of the `free_count`, -1 when
 * the draw passes them all. */
int EventSchedule_PickFreeDay(EventSchedule *unused, int *free_days, int free_count)
{
    (void) unused;
    int left = func_020644cc(free_count);
    for (int i = 0; i < EVENT_SCHEDULE_DAYS; i++) {
        if (free_days[i] == 1) {
            left--;
            if (left < 0) {
                return i;
            }
        }
    }
    return -1;
}
CLEAN_AS(func_02041110, EventSchedule_PickFreeDay)
