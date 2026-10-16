/* The town's calendar of events (event_calendar.h). */
#include "event_calendar.h"

#include "calendar.h"
#include "clean.h"
#include "date_time.h"
#include "event_schedule.h"
#include "lookups.h"
#include "npc_id.h"
#include "paired_town.h"
#include "player_record.h"
#include "player_records.h"
#include "process_020dabc0.h"
#include "town_villager.h"
#include "villager_data.h"
#include "villager_move.h"
#include "villager_roster.h"
#include "villager_status.h"
#include "villager_town.h"
#include "wfc_stats.h"

static_assert(sizeof(EventRule) == 0xc, "EventRule");
static_assert(sizeof(EventCalendarEntry) == 0x1c, "EventCalendarEntry");
static_assert(sizeof(EventCalendarEvent) == 0xc, "EventCalendarEvent");
static_assert(offsetof(EventCalendarEntry, end) == 0x10, "EventCalendarEntry.end");

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

extern const EventCalendarEntry data_020dac08[EVENT_CALENDAR_EVENTS];
extern Date data_021c74d0;                                          /* the date of today's list */
extern EventCalendarEvent data_021c74d4[EVENT_CALENDAR_DAY_EVENTS]; /* today's list */
extern EventSchedule data_021f39c0;
extern VillagerTown data_021e5a2c;
extern u8 data_021f3278[]; /* the town's statistics record (WfcStats) */

/* The event number of villager 0's birthday; villager n's is this plus n. */
#define EVENT_CALENDAR_VILLAGER_EVENT_FIRST 0x4b

/* The hours events 0x16, 0x18 and 0x19 run between on their day. */
#define EVENT_CALENDAR_DAY_START_HOUR 6
#define EVENT_CALENDAR_DAY_END_HOUR 24

/* The hour a date is checked at by EventCalendar_ListAtNoon. */
#define EVENT_CALENDAR_NOON 12

/* The minutes before its end an event is EVENT_CALENDAR_ENDING. */
#define EVENT_CALENDAR_ENDING_MINUTES 5

/* Byte `index` (EVENT_KEY_BYTE_*) of a key in memory. */
static u8 *key_byte(EventKey *key, int index)
{
    return (u8 *) key + index;
}

/* The weekday of the first day of `date`'s month, from `date`'s day and weekday. */
static int first_weekday(EventKey date)
{
    int weekday = EVENT_KEY_WEEKDAY(date) - (EVENT_KEY_DAY(date) - 1) % 7;
    if (weekday < 0) {
        weekday += 7;
    }
    return weekday;
}

/* The day of the `week`-th `weekday` of a month whose first day is on `first`. */
static u8 nth_weekday(int first, u32 weekday, int week)
{
    int day = (u32) first <= weekday ? (int) weekday - first + 1 : (int) weekday - first + 8;
    return (u8) (day + 7 * (week - 1));
}

/* func_0203fb80: the start and end of `event` in today's list; 1 and 1 when it is not there. */
void EventCalendar_TodaySpan(EventKey *start, EventKey *end, int event)
{
    EventCalendarEvent *found = EventCalendar_Find((u16) event, data_021c74d4);
    if (found != NULL) {
        *start = found->start;
        *end = found->end;
    } else {
        *start = 1;
        *end = 1;
    }
}
CLEAN_AS(func_0203fb80, EventCalendar_TodaySpan)

/* func_0203fbb0: the events (at most `max`, in `out`) running at noon of `when`'s date, kind 5
 * left out: started before noon and ending after it. Events the current player took part in
 * count. REQUIRES: max >= 1 (with 0 the list is filled with no limit). */
int EventCalendar_ListAtNoon(EventCalendarEvent *out, int max, const DateTime *when)
{
    int year = when->year;
    int month = when->month;
    int day = when->day;
    EventKey noon = EVENT_KEY_MAKE(month, day, EVENT_CALENDAR_NOON, Calendar_Weekday(year, month, day));
    int count = 0;

    EventCalendar_ClearList(out, max);
    const EventCalendarEntry *entry = data_020dac08;
    for (int i = 0; i < EVENT_CALENDAR_EVENTS; i++, entry++) {
        EventCalendarEvent event;
        if (entry->kind == EVENT_CALENDAR_KIND_FREE) {
            continue;
        }
        if (!EventCalendar_SpanOn(&event, entry, year, noon)) {
            continue;
        }
        if (event.start >= noon || event.end <= noon) {
            continue;
        }
        if (EventCalendar_IsBlocked(entry, noon, &event, out, count, 1, 0)) {
            continue;
        }
        EventCalendar_SetDayHours(&event, noon);
        out[count] = event;
        count++;
        if (count == max) {
            break;
        }
    }
    return count;
}
CLEAN_AS(func_0203fbb0, EventCalendar_ListAtNoon)

/* func_0203fc70: today's list. */
EventCalendarEvent *EventCalendar_Today(void)
{
    return data_021c74d4;
}
CLEAN_AS(func_0203fc70, EventCalendar_Today)

/* func_0203fc78: how `event` stands at `when` (enum EventCalendarState), EVENT_CALENDAR_LATER
 * told as EVENT_CALENDAR_OFF, and EVENT_CALENDAR_OFF when the current player took part in
 * today's event of the schedule and it is `event`. `use_list`: EventCalendar_StateOn. */
int EventCalendar_State(int event, const DateTime *when, int use_list)
{
    if (EventSchedule_HasTakenPart(event)) {
        return EVENT_CALENDAR_OFF;
    }
    DateTime copy;
    MI_CpuCopy8(when, &copy, sizeof(copy));
    int state = EventCalendar_StateOn(event, &copy, use_list);
    if (state == EVENT_CALENDAR_LATER) {
        state = EVENT_CALENDAR_OFF;
    }
    return state;
}
CLEAN_AS(func_0203fc78, EventCalendar_State)

/* func_0203fcb4: how `event` stands at `when`: from today's list when `when` is on its date
 * (EVENT_CALENDAR_OFF instead while the process is held back, unless `use_list`), else from a
 * list made for `when`'s date that leaves out the events the current player took part in. */
int EventCalendar_StateOn(int event, const DateTime *when, int use_list)
{
    DateTime copy;
    if (when->year == data_021c74d0.year && when->month == data_021c74d0.month && when->day == data_021c74d0.day) {
        if (use_list == 0 && Process020dabc0_IsHeldBack() != 0) {
            return EVENT_CALENDAR_OFF;
        }
        MI_CpuCopy8(when, &copy, sizeof(copy));
        return EventCalendar_StateIn(event, &copy, data_021c74d4);
    }
    EventCalendarEvent list[EVENT_CALENDAR_DAY_EVENTS];
    MI_CpuCopy8(when, &copy, sizeof(copy));
    EventCalendar_ListOpen(list, &copy, 0);
    MI_CpuCopy8(when, &copy, sizeof(copy));
    return EventCalendar_StateIn(event, &copy, list);
}
CLEAN_AS(func_0203fcb4, EventCalendar_StateOn)

/* func_0203fd38: how `event` of `list` stands at `when`: EVENT_CALENDAR_OFF when it is not in
 * the list, LATER before its start (date and hour), then ON until 5 minutes before its end
 * (taken in `when`'s year), ENDING to its end and OFF after. */
int EventCalendar_StateIn(int event, const DateTime *when, EventCalendarEvent *list)
{
    EventCalendarEvent *found = EventCalendar_Find((u16) event, list);
    if (found == NULL) {
        return EVENT_CALENDAR_OFF;
    }
    if (found->start > EVENT_KEY_MAKE(when->month, when->day, when->hour, 0)) {
        return EVENT_CALENDAR_LATER;
    }
    DateTime end = {0};
    end.year = when->year;
    end.month = EVENT_KEY_MONTH(found->end);
    end.day = EVENT_KEY_DAY(found->end);
    end.hour = EVENT_KEY_HOUR(found->end);
    int left = DateTime_MinutesBetween(when, &end);
    if (left <= 0) {
        return EVENT_CALENDAR_OFF;
    }
    return left <= EVENT_CALENDAR_ENDING_MINUTES ? EVENT_CALENDAR_ENDING : EVENT_CALENDAR_ON;
}
CLEAN_AS(func_0203fd38, EventCalendar_StateIn)

/* func_0203fda0: `event` in a list of EVENT_CALENDAR_DAY_EVENTS, NULL when it is not there. */
EventCalendarEvent *EventCalendar_Find(u16 event, EventCalendarEvent *list)
{
    for (int i = 0; i < EVENT_CALENDAR_DAY_EVENTS; i++) {
        if (list[i].id == event) {
            return &list[i];
        }
    }
    return NULL;
}
CLEAN_AS(func_0203fda0, EventCalendar_Find)

/* func_0203fdc4: the days from the start of `event` (in today's list, its date taken in this
 * year) to today; -1 when it is not in the list. */
int EventCalendar_DaysSinceStart(int event)
{
    EventCalendarEvent *found = EventCalendar_Find((u16) event, data_021c74d4);
    if (found == NULL) {
        return -1;
    }
    DateTime now = {0};
    DateTime_Now(&now);
    now.hour = 0;
    now.minute = 0;
    now.second = 0;
    DateTime start = {0};
    start.year = now.year;
    start.month = EVENT_KEY_MONTH(found->start);
    start.day = EVENT_KEY_DAY(found->start);
    return DateTime_DaysBetween(&start, &now);
}
CLEAN_AS(func_0203fdc4, EventCalendar_DaysSinceStart)

/* func_0203fe1c: today's list made again when the date has changed since it was made. */
void EventCalendar_RefreshIfStale(int unused)
{
    (void) unused;
    DateTime now = {0};
    DateTime_Now(&now);
    if (now.year == data_021c74d0.year && now.month == data_021c74d0.month && now.day == data_021c74d0.day) {
        return;
    }
    EventCalendar_Refresh(0);
}
CLEAN_AS(func_0203fe1c, EventCalendar_RefreshIfStale)

/* func_0203fe58: today's list made for the clock's date and time, leaving out the events the
 * current player took part in. `today_only`: EventCalendar_IsBlocked. */
void EventCalendar_Refresh(int today_only)
{
    DateTime now = {0};
    DateTime copy;
    DateTime_Now(&now);
    MI_CpuCopy8(&now, &copy, sizeof(copy));
    EventCalendar_ListOpen(data_021c74d4, &copy, today_only);
    data_021c74d0.year = now.year;
    data_021c74d0.month = now.month;
    data_021c74d0.day = now.day;
}
CLEAN_AS(func_0203fe58, EventCalendar_Refresh)

/* func_0203fea0: the events of `when`'s date, those the current player took part in included. */
int EventCalendar_ListAll(EventCalendarEvent *out, const DateTime *when)
{
    DateTime copy;
    MI_CpuCopy8(when, &copy, sizeof(copy));
    return EventCalendar_List(out, &copy, 1, 0);
}
CLEAN_AS(func_0203fea0, EventCalendar_ListAll)

/* func_0203fec4: the events of `when`'s date, those the current player took part in left out. */
int EventCalendar_ListOpen(EventCalendarEvent *out, const DateTime *when, int today_only)
{
    DateTime copy;
    MI_CpuCopy8(when, &copy, sizeof(copy));
    return EventCalendar_List(out, &copy, 0, today_only);
}
CLEAN_AS(func_0203fec4, EventCalendar_ListOpen)

/* func_0203feec: the events of `when`'s date in `out` (EVENT_CALENDAR_DAY_EVENTS, the rest
 * cleared), in the table's order; their count. `include_taken` and `today_only`:
 * EventCalendar_IsBlocked. */
int EventCalendar_List(EventCalendarEvent *out, const DateTime *when, int include_taken, int today_only)
{
    int year = when->year;
    int month = when->month;
    int day = when->day;
    EventKey date = EVENT_KEY_MAKE(month, day, when->hour, Calendar_Weekday(year, month, day));
    int count = 0;

    EventCalendar_ClearList(out, EVENT_CALENDAR_DAY_EVENTS);
    const EventCalendarEntry *entry = data_020dac08;
    for (int i = 0; i < EVENT_CALENDAR_EVENTS; i++, entry++) {
        EventCalendarEvent event;
        if (!EventCalendar_SpanOn(&event, entry, year, date)) {
            continue;
        }
        if (EventCalendar_IsBlocked(entry, date, &event, out, count, include_taken, today_only)) {
            continue;
        }
        EventCalendar_SetDayHours(&event, date);
        out[count] = event;
        count++;
        if (count == EVENT_CALENDAR_DAY_EVENTS) {
            break;
        }
    }
    return count;
}
CLEAN_AS(func_0203feec, EventCalendar_List)

/* func_0203ff98: `entry` as an event of `year` in `event`, 1 when its dates take in `date`'s
 * (the start's on or before it, the end's on or after). The end is worked out only when the
 * start has a date on or before `date`'s. */
int EventCalendar_SpanOn(EventCalendarEvent *event, const EventCalendarEntry *entry, int year, EventKey date)
{
    u32 day = date & EVENT_KEY_DATE_MASK;
    int id = entry->id;
    event->id = (u16) id;
    event->kind = entry->kind;
    event->start = (EventKey) EventCalendar_StartKey(&entry->start, year, date, id);
    if (event->start == 0 || (event->start & EVENT_KEY_DATE_MASK) > day) {
        return 0;
    }
    event->end = (EventKey) EventCalendar_EndKey(&entry->end, year, date, id);
    return event->end != 0 && (event->end & EVENT_KEY_DATE_MASK) >= day;
}
CLEAN_AS(func_0203ff98, EventCalendar_SpanOn)

/* func_02040010: events 0x16, 0x18 and 0x19 run from 6:00 to 24:00 of `date`'s day. */
void EventCalendar_SetDayHours(EventCalendarEvent *event, EventKey date)
{
    if (event->id != EVENT_CALENDAR_EVENT_16 && event->id != EVENT_CALENDAR_EVENT_18 && event->id != EVENT_CALENDAR_EVENT_19) {
        return;
    }
    u8 day = EVENT_KEY_DAY(date);
    *key_byte(&event->start, EVENT_KEY_BYTE_DAY) = day;
    *key_byte(&event->start, EVENT_KEY_BYTE_HOUR) = EVENT_CALENDAR_DAY_START_HOUR;
    *key_byte(&event->end, EVENT_KEY_BYTE_DAY) = day;
    *key_byte(&event->end, EVENT_KEY_BYTE_HOUR) = EVENT_CALENDAR_DAY_END_HOUR;
}
CLEAN_AS(func_02040010, EventCalendar_SetDayHours)

/* func_02040034: 1 when `event` (made from `entry`) is not to be listed for `date` after the
 * `count` events of `listed`:
 * - never for kind 5;
 * - when the current player took part in it today (unless `include_taken`);
 * - kind 4: when the schedule's day of `date`'s weekday does not have it for the player (with
 *   `today_only`), or neither that day nor the one before do; or for the paired town;
 * - else when it overlaps (hours and dates, weekdays left out) a listed event of its kind or a
 *   lower one, other than kind 5; for kind 2 and above when the paired town has a visit in
 *   the last week, for kind 3 and above when the statistics record is in use; for event 0x3c
 *   and the fox, in the 7 days the schedule bars them. */
int EventCalendar_IsBlocked(const EventCalendarEntry *entry, EventKey date, const EventCalendarEvent *event,
                            const EventCalendarEvent *listed, int count, int include_taken, int today_only)
{
    int kind = entry->kind;
    if (kind == EVENT_CALENDAR_KIND_FREE) {
        return 0;
    }
    if (include_taken == 0 && EventSchedule_HasTakenPart(event->id)) {
        return 1;
    }
    if (kind == EVENT_CALENDAR_KIND_4) {
        u8 weekday = EVENT_KEY_WEEKDAY(date);
        if (today_only != 0) {
            if (EventSchedule_IsExcluded(event->id, weekday)) {
                return 1;
            }
        } else if (EventSchedule_IsExcluded(event->id, weekday) && EventSchedule_IsExcluded(event->id, (u8) (weekday - 1))) {
            return 1;
        }
        return PairedTown_CurrentUnflaggedInLastWeek() || PairedTown_CurrentFlaggedInLastWeek();
    }

    /* The game tests the overlap both ways round; the two tests are the same. */
    u32 from = event->start & ~0xffu;
    u32 to = event->end & ~0xffu;
    for (int i = 0; i < count; i++) {
        const EventCalendarEvent *other = &listed[i];
        if (other->kind == EVENT_CALENDAR_KIND_FREE || kind < other->kind) {
            continue;
        }
        u32 other_from = other->start & ~0xffu;
        u32 other_to = other->end & ~0xffu;
        if (from < other_to && to > other_from) {
            return 1;
        }
    }
    if (kind >= 2 && (PairedTown_CurrentUnflaggedInLastWeek() || PairedTown_CurrentFlaggedInLastWeek())) {
        return 1;
    }
    if (kind >= 3 && WfcStats_IsInUse((const WfcStats *) data_021f3278)) {
        return 1;
    }
    switch (event->id) {
        case EVENT_CALENDAR_EVENT_3C:
            return EventSchedule_3cBarred(date);
        case EVENT_CALENDAR_FOX:
            return EventSchedule_FoxBarred(date);
    }
    return 0;
}
CLEAN_AS(func_02040034, EventCalendar_IsBlocked)

/* func_02040164: `count` events of a list set to none (kind 5); their dates are left. */
void EventCalendar_ClearList(EventCalendarEvent *list, int count)
{
    for (int i = 0; i < count; i++) {
        list[i].id = EVENT_CALENDAR_NONE;
        list[i].kind = EVENT_CALENDAR_KIND_FREE;
    }
}
CLEAN_AS(func_02040164, EventCalendar_ClearList)

/* func_02040180: the key of an event's end rule. */
int EventCalendar_EndKey(const EventRule *rule, int year, EventKey date, int event)
{
    return (int) EventCalendar_RuleKey(rule, year, date, event);
}
CLEAN_AS(func_02040180, EventCalendar_EndKey)

/* func_0204019c: the key of an event's start rule. */
int EventCalendar_StartKey(const EventRule *rule, int year, EventKey date, int event)
{
    return (int) EventCalendar_RuleKey(rule, year, date, event);
}
CLEAN_AS(func_0204019c, EventCalendar_StartKey)

/* func_020401b8: the date and hour `rule` gives `event` in `year`, seen from `date` (a key with
 * its weekday); 0 for none. Its weekday byte is 0. */
EventKey EventCalendar_RuleKey(const EventRule *rule, int year, EventKey date, int event)
{
    u32 flags = rule->flags;
    int rule_month = EVENT_RULE_MONTH(flags);
    int week = EVENT_RULE_WEEK(flags);
    u32 weekday = EVENT_RULE_WEEKDAY(flags);
    int move = flags & EVENT_RULE_MOVE;
    int date_month = EVENT_KEY_MONTH(date);
    EventKey key = 0;
    u8 month;

    switch (EVENT_RULE_KIND(flags)) {
        case EVENT_RULE_MONTHS_1_5_10_12:
            switch (date_month) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 10:
                case 11:
                case 12:
                    month = (u8) date_month;
                    break;
                default:
                    month = 1;
                    break;
            }
            key = EVENT_KEY_MAKE(month, EventCalendar_RuleDay(rule, year, date, month, event), rule->hour, 0);
            break;
        case EVENT_RULE_MONTHS_6_9:
            switch (date_month) {
                case 6:
                case 7:
                case 8:
                case 9:
                    month = (u8) date_month;
                    break;
                default:
                    month = 6;
                    break;
            }
            key = EVENT_KEY_MAKE(month, EventCalendar_RuleDay(rule, year, date, month, event), rule->hour, 0);
            break;
        case EVENT_RULE_COMPUTED:
            month = (u8) EventCalendar_RuleMonth(rule, year, date, event);
            key = EVENT_KEY_MAKE(month, EventCalendar_RuleDay(rule, year, date, month, event), rule->hour, 0);
            break;
        case EVENT_RULE_PLAYER_BIRTHDAY:
            EventCalendar_PlayerBirthdayKey(rule, &key);
            break;
        case EVENT_RULE_VILLAGER_BIRTHDAY:
            EventCalendar_VillagerBirthdayKey(rule, &key, event);
            break;
        case EVENT_RULE_NTH_WEEKDAY: {
            /* The first weekday of the rule's month, counted from that of `date`'s month by the
         * lengths of the months between. */
            int first = first_weekday(date);
            int m = rule_month;
            int to = date_month;
            if (m != to) {
                int days = 0;
                if ((u32) m < (u32) to) {
                    for (; m < to; m++) {
                        days += Calendar_DaysInMonth((u32) year, (u8) m);
                    }
                    first = (first - days % 7 + 7) % 7;
                } else {
                    for (; (u32) to < (u32) m; to++) {
                        days += Calendar_DaysInMonth((u32) year, (u8) to);
                    }
                    first = (first + days) % 7;
                }
            }
            key = EVENT_KEY_MAKE(rule_month, nth_weekday(first, weekday, week), rule->hour, 0);
            break;
        }
        case EVENT_RULE_SCHEDULE:
            switch (event) {
                case 0x3d:
                case 0x3e:
                case 0x3f:
                case 0x40:
                case 0x41:
                case 0x42:
                case 0x43:
                case 0x44:
                case 0x45:
                case 0x60:
                    key = EventCalendar_ScheduleKey(rule, event, date);
                    break;
                case EVENT_CALENDAR_EVENT_61:
                case EVENT_CALENDAR_EVENT_62:
                    /* Around the new year: with the move bit, from 31 December at 6:00 (seen from
             * January) or at 24:00 (seen from another month, and then not moved); without it,
             * 1 January at 0:00 (from January) or 31 December at 6:00. */
                    if (move) {
                        if (date_month == 1) {
                            key = EVENT_KEY_MAKE(12, 31, 6, 0);
                        } else {
                            move = 0;
                            key = EVENT_KEY_MAKE(12, 31, 24, 0);
                        }
                    } else if (date_month == 1) {
                        key = EVENT_KEY_MAKE(1, 1, 0, 0);
                    } else {
                        key = EVENT_KEY_MAKE(12, 31, 6, 0);
                    }
                    break;
            }
            break;
    }

    if (key != 0) {
        DateTime when = {0};
        u8 day = EVENT_KEY_DAY(key);
        when.year = (u8) year;
        when.month = EVENT_KEY_MONTH(key);
        when.day = day;
        int days = Calendar_DaysInMonth((u32) year, EVENT_KEY_MONTH(key));
        if (day > days) {
            when.day = (u8) days;
            DateTime_AddDays(&when, day - days);
        }
        if (move) {
            int by = rule->days;
            if (by < 0) {
                DateTime_SubtractDays(&when, -by);
            } else {
                DateTime_AddDays(&when, by);
            }
        }
        key = (key & 0x0000ffffu) | EVENT_KEY_MAKE(when.month, when.day, 0, 0);
    }
    return key;
}
CLEAN_AS(func_020401b8, EventCalendar_RuleKey)

/* func_020404b4: the date of `event`'s day in the schedule, at the rule's hour; 0 when it has
 * none. Event 0x45 is looked for on `date`'s weekday, the others (0x60 as 0x40) on the day
 * before it, then on it. */
EventKey EventCalendar_ScheduleKey(const EventRule *rule, int event, EventKey date)
{
    EventSchedule *schedule = &data_021f39c0;
    int weekday = EVENT_KEY_WEEKDAY(date);
    EventScheduleDay *day;

    if (event == EVENT_CALENDAR_EVENT_45) {
        day = EventSchedule_Day(schedule, weekday);
        if (day != NULL && event == day->event) {
            return EVENT_KEY_MAKE(day->month, day->day, rule->hour, 0);
        }
        return 0;
    }
    if (event == EVENT_CALENDAR_EVENT_60) {
        event = EVENT_CALENDAR_EVENT_40;
    }
    for (int i = 0; i < 2; i++) {
        day = EventSchedule_Day(schedule, weekday - 1 + i);
        if (day != NULL && event == day->event) {
            return EVENT_KEY_MAKE(day->month, day->day, rule->hour, 0);
        }
    }
    return 0;
}
CLEAN_AS(func_020404b4, EventCalendar_ScheduleKey)

/* func_02040548: in `key`, the birthday of villager `villager` (0-7, or an event number from
 * 0x4b) at the rule's hour; 0 when that villager does not count (EventCalendar_VillagerCounts)
 * or has no data. */
void EventCalendar_VillagerBirthdayKey(const EventRule *rule, EventKey *key, int villager)
{
    *key = 0;
    if (villager < 0 || villager > 7) {
        villager -= EVENT_CALENDAR_VILLAGER_EVENT_FIRST;
    }
    u8 *place = VillagerRoster_At(&data_021e5a2c, villager);
    if (!EventCalendar_VillagerCounts(place, VillagerMove_VillagerIndex(&data_021e5a2c))) {
        return;
    }
    const MonthDay *birthday = VillagerData_Birthday(place);
    if (birthday != NULL) {
        *key_byte(key, EVENT_KEY_BYTE_MONTH) = birthday->month;
        *key_byte(key, EVENT_KEY_BYTE_DAY) = birthday->day;
        *key_byte(key, EVENT_KEY_BYTE_HOUR) = (u8) rule->hour;
    }
}
CLEAN_AS(func_02040548, EventCalendar_VillagerBirthdayKey)

/* func_020405a8: 1 when `villager` is there (a valid NpcId), staying as a resident, with an
 * entry of the state table, and is not the villager `moving` (VillagerMove_VillagerIndex). */
int EventCalendar_VillagerCounts(u8 *villager, int moving)
{
    if (!NpcId_IsValid(TownVillager_NpcId(villager)) || VillagerStatus_Stay(villager) != VILLAGER_STAY_RESIDENT) {
        return 0;
    }
    int index = VillagerStatus_Index(villager);
    return index != -1 && index != moving;
}
CLEAN_AS(func_020405a8, EventCalendar_VillagerCounts)

/* func_020405e4: in `key`, the current player's birthday at the rule's hour; left as it is
 * without a current player or birthday. */
void EventCalendar_PlayerBirthdayKey(const EventRule *rule, EventKey *key)
{
    if (PlayerRecords_Current() == NULL) {
        return;
    }
    const u8 *birthday = PlayerRecord_Birthday(PlayerRecords_Current()); /* day, month */
    if (birthday == NULL) {
        return;
    }
    *key_byte(key, EVENT_KEY_BYTE_MONTH) = birthday[1];
    *key_byte(key, EVENT_KEY_BYTE_DAY) = birthday[0];
    *key_byte(key, EVENT_KEY_BYTE_HOUR) = (u8) rule->hour;
}
CLEAN_AS(func_020405e4, EventCalendar_PlayerBirthdayKey)

/* func_02040614: the day in `month` that `rule` gives `event`, seen from `date`
 * (enum EventRuleWeek). Week 1-5 is the n-th of the rule's weekday, found from `date`'s
 * weekday by counting the months between; December seen from January counts back over
 * December. For events 9, 0x14, 0x25, 0x26 and 0x46 in February, April or October the week is
 * the fourth whatever the rule says.
 * QUIRK: EVENT_RULE_DAY_LAST takes `date`'s weekday, not the rule's. */
u8 EventCalendar_RuleDay(const EventRule *rule, int year, EventKey date, int month, int event)
{
    u32 flags = rule->flags;
    int week = EVENT_RULE_WEEK(flags);
    u32 weekday = EVENT_RULE_WEEKDAY(flags);
    int month_days = Calendar_DaysInMonth((u32) year, (u32) month);
    int date_month = EVENT_KEY_MONTH(date);
    int date_month_days = Calendar_DaysInMonth((u32) year, (u32) date_month);
    int date_weekday = EVENT_KEY_WEEKDAY(date);

    switch (week) {
        case EVENT_RULE_DAY_FIXED:
            return (u8) rule->days;
        case EVENT_RULE_DAY_LAST: {
            int last = Calendar_Weekday((u8) year, month, (u8) month_days);
            if (last < date_weekday) {
                return (u8) (month_days - 7 + (date_weekday - last));
            }
            return (u8) (month_days - (last - date_weekday));
        }
        case EVENT_RULE_DAY_NEXT: {
            int day = (u8) (EVENT_KEY_DAY(date) + weekday - date_weekday + (weekday < (u32) date_weekday ? 7 : 0));
            if (date_month != month && day > date_month_days) {
                day -= date_month_days;
            }
            return (u8) day;
        }
    }

    int first = first_weekday(date);
    if (month != date_month) {
        int days = 0;
        int from = month;
        if (month == 1 && date_month == 12) {
            from = 13;
        }
        if ((u32) from < (u32) date_month) {
            for (int m = from; m < date_month; m++) {
                days += Calendar_DaysInMonth((u32) year, (u8) m);
            }
            first = (first - days % 7 + 7) % 7;
        } else {
            for (int m = date_month; m < from; m++) {
                days += Calendar_DaysInMonth((u32) year, (u8) m);
            }
            first = (first + days) % 7;
        }
    }
    switch (event) {
        case 0x09:
        case 0x14:
        case 0x25:
        case 0x26:
        case 0x46:
            if (month == 2 || month == 4 || month == 10) {
                week = 4;
            }
            break;
    }
    return nth_weekday(first, weekday, week);
}
CLEAN_AS(func_02040614, EventCalendar_RuleDay)

/* func_020407b0: the month of a rule of kind 0 (enum EventRuleMonthMode), seen from `date`; 0 for
 * mode 3. In mode 1, events 0xb, 0x29, 0x2a and 0x48 take February for January or August.
 * QUIRK: mode 1 moves the date forward by the size of `days` whatever its sign; event 0x48
 * moves it by 4. */
int EventCalendar_RuleMonth(const EventRule *rule, int year, EventKey date, int event)
{
    u32 flags = rule->flags;
    int rule_month = EVENT_RULE_MONTH(flags);
    u8 month = EVENT_KEY_MONTH(date);
    int result = 0;

    switch (EVENT_RULE_MONTH_MODE(flags)) {
        case EVENT_RULE_MONTH_FIXED:
            result = rule_month;
            break;
        case EVENT_RULE_MONTH_AHEAD:
            if (rule_month == 0) {
                result = month;
            } else {
                int by = event == EVENT_CALENDAR_EVENT_48 ? -4 : rule->days;
                DateTime when = {0};
                when.year = (u8) year;
                when.month = month;
                when.day = EVENT_KEY_DAY(date);
                if (by < 0) {
                    by = -by;
                }
                DateTime_AddDays(&when, by);
                result = when.month;
            }
            switch (event) {
                case EVENT_CALENDAR_EVENT_0B:
                case EVENT_CALENDAR_EVENT_29:
                case EVENT_CALENDAR_EVENT_2A:
                case EVENT_CALENDAR_EVENT_48:
                    if (result == 1 || result == 8) {
                        result = 2;
                    }
                    break;
            }
            break;
        case EVENT_RULE_MONTH_PARITY:
            result = rule_month == 1 ? (u8) ((month & ~1) + 1) : (u8) ((month + 1) & ~1);
            break;
    }
    return result;
}
CLEAN_AS(func_020407b0, EventCalendar_RuleMonth)

/* func_02040868: the destructor of the calendar's dates (data_021c74d0, data_021c7528). */
void EventCalendar_DateDestruct(void *date)
{
    (void) date;
}
CLEAN_AS(func_02040868, EventCalendar_DateDestruct)

/* func_0204086c: their constructor: 1 January 2000. */
void EventCalendar_DateConstruct(Date *date)
{
    date->day = 1;
    date->month = 1;
    date->year = 0;
    date->unused = 0;
}
CLEAN_AS(func_0204086c, EventCalendar_DateConstruct)
