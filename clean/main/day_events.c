/* The dated events of a player's year (day_events.h). */
#include "day_events.h"

#include "calendar.h"
#include "clean.h"
#include "date_time.h"
#include "museum_record.h"
#include "nook_store.h"
#include "player_record.h"
#include "player_records.h"
#include "session.h"

static_assert(sizeof(DayEventMark) == 5, "day event mark");

/* An event's first day: the `week`-th `weekday` of `month` (0: no event); when the month has
 * no such week, the week before is taken. */
typedef struct DayEventsStart {
    u8 month;
    u8 week;
    u8 unused[2];
    u32 weekday;
} DayEventsStart;

static_assert(sizeof(DayEventsStart) == 8, "day event start");

extern const DayEventsStart data_020d0704[DAY_EVENTS_KINDS][DAY_EVENTS_PER_KIND];
/* Each part's length in days, 0 for no part. */
extern const s32 data_020d07a4[DAY_EVENTS_KINDS][DAY_EVENTS_PER_KIND][DAY_EVENTS_PARTS];

extern NetSession *data_020ccf94; /* the session */
extern MuseumRecord data_021f38f8;
extern NookStore data_021f395c;

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* Byte 8 of a player record's object at 0x2416. */
extern int func_02088bdc(u8 *field);

/* The player record's flag that rules all events out, the flags that qualify for kinds 0 and
 * 1, the value kind 2 asks of byte 8 at 0x2416 and the store level kind 3 asks for. */
#define DAY_EVENTS_FLAG_NONE 1
#define DAY_EVENTS_FLAG_KIND_0 6
#define DAY_EVENTS_FLAG_KIND_1 8
#define DAY_EVENTS_KIND_2_VALUE 0xf
#define DAY_EVENTS_KIND_3_LEVEL 3

/* func_02088470: whether the current player has the event part running on the date given
 * (year from 2000), which is stored in *event (DayEvents_Find). Never during a session with
 * others, nor for a player with flag 1. */
int DayEvents_PlayerHas(int year, int month, int day, u8 *event)
{
    if (Session_IsLinked(data_020ccf94) != 0) {
        return 0;
    }
    u8 *record = PlayerRecords_Current();
    if (PlayerRecord_TestFlag(record, DAY_EVENTS_FLAG_NONE) != 0) {
        return 0;
    }
    if (DayEvents_Find(year, (u8) month, (u8) day, event) == 0) {
        return 0;
    }

    u8 marked;
    DayEvents_MarkEvent((DayEventMark *) PlayerRecord_Field2427(record), &marked);
    const u8 *date = DayEvents_MarkDate((DayEventMark *) PlayerRecord_Field2427(record));

    int kind = DAY_EVENT_KIND(*event);
    int index = DAY_EVENT_INDEX(*event);
    int part = DAY_EVENT_PART(*event);
    int same_event = kind == DAY_EVENT_KIND(marked) && index == DAY_EVENT_INDEX(marked);

    if (same_event && part == DAY_EVENT_PART(marked)) {
        /* The marked part: on its own day, or when no day is marked. */
        if (date[2] == year && date[1] == month && date[0] == day) {
            return 1;
        }
        return date[2] == 0 && date[1] == 0 && date[0] == 0;
    }
    if (part != 0) {
        /* A later part counts when it follows the marked one. */
        return same_event && (u8) (part - 1) == DAY_EVENT_PART(marked);
    }
    switch (kind) {
        case 0:
            return PlayerRecord_TestFlag(record, DAY_EVENTS_FLAG_KIND_0) != 0;
        case 1:
            return PlayerRecord_TestFlag(record, DAY_EVENTS_FLAG_KIND_1) != 0 || MuseumRecord_Complete(&data_021f38f8) != 0;
        case 2:
            return func_02088bdc(PlayerRecord_Field2416(record)) == DAY_EVENTS_KIND_2_VALUE;
        default:
            return NookStore_Level(&data_021f395c) == DAY_EVENTS_KIND_3_LEVEL;
    }
}
CLEAN_AS(func_02088470, DayEvents_PlayerHas)

/* func_020885d8: the event part running on a date (year from 2000), searching the events
 * that start in that year and the year before, kind by kind and event by event; 1 with it in
 * *event, else 0 with *event untouched.
 * QUIRK: when the days from the date to a part's start are 0, the game counts them again the
 * other way round, which gives 0 again. */
int DayEvents_Find(int year, u8 month, u8 day, u8 *event)
{
    DateTime date = {0};
    date.year = (u8) year;
    date.month = month;
    date.day = day;

    for (int start_year = year - 1; start_year <= year; start_year++) {
        if (start_year < 0) {
            continue;
        }
        for (int kind = 0; kind < DAY_EVENTS_KINDS; kind++) {
            for (int index = 0; index < DAY_EVENTS_PER_KIND; index++) {
                const DayEventsStart *start = &data_020d0704[kind][index];
                if (start->month == 0) {
                    continue;
                }
                u8 week = start->week;
                int first;
                while ((first = Calendar_NthWeekday((u8) start_year, start->month, (int) start->weekday, week)) == -1) {
                    week--;
                }

                DateTime part_start = {0};
                part_start.year = (u8) start_year;
                part_start.month = start->month;
                part_start.day = (u8) first;

                for (int part = 0; part < DAY_EVENTS_PARTS; part++) {
                    int length = data_020d07a4[kind][index][part];
                    if (length == 0) {
                        continue;
                    }
                    int offset = DateTime_DaysBetween(&date, &part_start);
                    if (offset == 0) {
                        offset = -DateTime_DaysBetween(&part_start, &date);
                    }
                    /* The date is in [start, start + length). */
                    if (offset <= 0 && offset + length > 0) {
                        *event = DAY_EVENT_MAKE(kind, index, part);
                        return 1;
                    }
                    DateTime_AddDays(&part_start, length);
                }
            }
        }
    }
    return 0;
}
CLEAN_AS(func_020885d8, DayEvents_Find)

/* func_02088724: the mark's date (day, month, year). */
u8 *DayEvents_MarkDate(DayEventMark *mark)
{
    return &mark->day;
}
CLEAN_AS(func_02088724, DayEvents_MarkDate)

/* func_02088728: the mark set to *event, today. */
void DayEvents_SetMark(DayEventMark *mark, const u8 *event)
{
    Calendar_Today((Date *) (void *) &mark->day);
    MI_CpuCopy8(event, &mark->event, 1);
}
CLEAN_AS(func_02088728, DayEvents_SetMark)

/* func_02088748: the marked event byte copied to *event. */
void DayEvents_MarkEvent(const DayEventMark *mark, u8 *event)
{
    MI_CpuCopy8(&mark->event, event, 1);
}
CLEAN_AS(func_02088748, DayEvents_MarkEvent)

/* func_02088754: no event marked (the date is kept). */
void DayEvents_ClearMark(DayEventMark *mark)
{
    MI_CpuFill8(&mark->event, DAY_EVENT_NONE, 1);
}
CLEAN_AS(func_02088754, DayEvents_ClearMark)

/* func_02088760: the mark's destructor, which does nothing. */
void DayEvents_MarkDestruct(DayEventMark *mark)
{
    (void) mark;
}
CLEAN_AS(func_02088760, DayEvents_MarkDestruct)

/* func_02088764: the mark's constructor, which does nothing. */
void DayEvents_MarkConstruct(DayEventMark *mark)
{
    (void) mark;
}
CLEAN_AS(func_02088764, DayEvents_MarkConstruct)
