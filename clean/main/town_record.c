/* The town's record in the state block (town_record.h). */
#include "town_record.h"

#include <string.h>

#include "acre_map.h"
#include "acre_tile.h"
#include "clean.h"
#include "clock.h"
#include "date_time.h"
#include "event_calendar.h"
#include "main_random.h"
#include "player_records.h"
#include "session.h"
#include "state_block.h"

static_assert(sizeof(TownRecord) == sizeof(((StateBlock *) NULL)->part_17254), "TownRecord");
static_assert(offsetof(TownRecord, summary_days) == 0x21, "TownRecord.summary_days");
static_assert(offsetof(TownRecord, events) == 0x24, "TownRecord.events");
static_assert(offsetof(TownRecord, player_days) == 0x58, "TownRecord.player_days");
static_assert(offsetof(TownRecord, unk_6b) == 0x6b, "TownRecord.unk_6b");

extern TownRecord data_021f39fc;                    /* the state block's (data_021dc7a8 + 0x17254) */
extern TownDayEvent data_021f3a20[TOWN_DAY_EVENTS]; /* its events */
extern NetSession *data_020ccf94;                   /* the session */
/* The tree code each fruit is planted as, by TownRecord.own_fruit. */
extern const u16 data_020cb758[TOWN_RECORD_FRUITS];

#define TOWN_RECORD_NO_EVENT 99
/* The event span of a free entry. */
#define TOWN_RECORD_FREE_SPAN 1
#define TOWN_RECORD_WEEK 7
/* The days after the week's end the pelican day is never drawn for (Monday and Tuesday). */
#define TOWN_RECORD_PELICAN_SKIP_A 1
#define TOWN_RECORD_PELICAN_SKIP_B 2
/* The growth line 0x5d-0x61, which ends at code 0x2a below the first three rows of acres. */
#define TOWN_RECORD_LINE_5D_FIRST 0x5d
#define TOWN_RECORD_LINE_5D_LAST 0x61
#define TOWN_RECORD_LINE_5D_END 0x2a
#define TOWN_RECORD_LINE_5D_FIRST_ROW 0x30
/* The five lines of eight fruit tree codes. */
#define TOWN_RECORD_FRUIT_TREE_FIRST 0x2f
#define TOWN_RECORD_FRUIT_TREE_LAST 0x56
#define TOWN_RECORD_ACRE_SHIFT 4 /* 16 tiles to an acre */
#define TOWN_RECORD_ACRE_MASK 15
#define TOWN_RECORD_LAYER 0
#define TOWN_RECORD_NEVER 0xff

/* func_0204ca60: the town's fruit (0-4). */
int TownRecord_OwnFruit(const TownRecord *record)
{
    return (int) record->own_fruit;
}
CLEAN_AS(func_0204ca60, TownRecord_OwnFruit)

/* func_0204ca8c: the period of the town's day noted (at most 0x16), unless linked with other
 * systems. */
void TownRecord_SetPeriod(u32 period)
{
    if (Session_IsLinked(data_020ccf94)) {
        return;
    }
    if (period > TOWN_RECORD_LAST_PERIOD) {
        period = TOWN_RECORD_LAST_PERIOD;
    }
    data_021f39fc.period = (u8) period;
}
CLEAN_AS(func_0204ca8c, TownRecord_SetPeriod)

/* func_0204cab4: the period of the town's day noted last. */
u8 TownRecord_Period(void)
{
    return data_021f39fc.period;
}
CLEAN_AS(func_0204cab4, TownRecord_Period)

/* func_0204cac0: the days in a row the town's summary answered 4: after `days` more days with
 * the answer `summary` (1 when the count starts), -1 for another answer.
 * QUIRK: the count is kept in a signed byte and wraps. */
void TownRecord_CountSummaryDays(TownRecord *record, int summary, int days)
{
    if (summary != TOWN_RECORD_SUMMARY_COUNTED) {
        record->summary_days = -1;
    } else if (record->summary_days < 0) {
        record->summary_days = 1;
    } else {
        record->summary_days = (s8) (record->summary_days + days);
    }
}
CLEAN_AS(func_0204cac0, TownRecord_CountSummaryDays)

/* func_0204cae8: whether the town's summary answered 4 for 15 days in a row or more. */
int TownRecord_Summary4Long(void)
{
    return data_021f39fc.summary_days >= TOWN_RECORD_SUMMARY_LONG_DAYS;
}
CLEAN_AS(func_0204cae8, TownRecord_Summary4Long)

/* func_0204cafc: whether the current player's day in the record is not today (the player has
 * a turn left today; TownRecord_UsePlayerTurn uses it up). */
int TownRecord_PlayerTurnLeft(TownRecord *record)
{
    int player = PlayerRecords_CurrentNumber();
    Date today;
    Calendar_Today(&today);
    return Calendar_DaysFrom(&today, &record->player_days[player]) != 0;
}
CLEAN_AS(func_0204cafc, TownRecord_PlayerTurnLeft)

/* func_0204cb2c: the current player's day in the record set to today. */
void TownRecord_UsePlayerTurn(int record)
{
    int player = PlayerRecords_CurrentNumber();
    Calendar_Today((Date *) (uintptr_t) (u32) TownRecord_PlayerDay(record, player));
}
CLEAN_AS(func_0204cb2c, TownRecord_UsePlayerTurn)

/* func_0204cb48: the address of player `player`'s day in the record. */
int TownRecord_PlayerDay(int record, int player)
{
    return (int) ((u32) record + offsetof(TownRecord, player_days) + ((u32) player << 2));
}
CLEAN_AS(func_0204cb48, TownRecord_PlayerDay)

/* func_0204cb50: event `event` given an entry, unless it has one: the first free entry gets it
 * with today's span of the event (EventCalendar_TodaySpan) and the clock's year. The entry's
 * index, -1 when none is free.
 * QUIRK: the entries are always data_021f39fc's, whatever `record` is. */
int TownRecord_MarkEvent(int record, int event)
{
    int index = TownRecord_FindEvent(record, event);
    if (index >= 0) {
        return index;
    }
    index = TownRecord_FindEvent(record, TOWN_RECORD_NO_EVENT);
    if (index < 0) {
        return index;
    }
    TownDayEvent *entry = (TownDayEvent *) (uintptr_t) (u32) TownRecord_Event(index);
    entry->id = (u16) event;
    EventCalendar_TodaySpan(&entry->start, &entry->end, event);
    entry->year = (u8) Clock_Year();
    return index;
}
CLEAN_AS(func_0204cb50, TownRecord_MarkEvent)

/* func_0204cb90: the index of the entry of event `event` (99: the first free one), -1 for none.
 * QUIRK: `record` is not used; the entries are data_021f39fc's. */
int TownRecord_FindEvent(int record, int event)
{
    (void) record;
    const TownDayEvent *entry = (const TownDayEvent *) (uintptr_t) (u32) TownRecord_Event(0);
    for (int i = 0; i < TOWN_DAY_EVENTS; i++, entry++) {
        if (event == entry->id) {
            return i;
        }
    }
    return -1;
}
CLEAN_AS(func_0204cb90, TownRecord_FindEvent)

static void town_record_free_entry(TownDayEvent *entry)
{
    entry->id = TOWN_RECORD_NO_EVENT;
    entry->start = TOWN_RECORD_FREE_SPAN;
    entry->end = TOWN_RECORD_FREE_SPAN;
}

/* func_0204cbc0: the entry of event `event`, if any, set free. */
void TownRecord_FreeEvent(int record, int event)
{
    int index = TownRecord_FindEvent(record, event);
    if (index >= 0) {
        town_record_free_entry((TownDayEvent *) (uintptr_t) (u32) TownRecord_Event(index));
    }
}
CLEAN_AS(func_0204cbc0, TownRecord_FreeEvent)

/* func_0204cbe0: every event entry set free.
 * QUIRK: `record` is not used; the entries are data_021f39fc's. */
void TownRecord_ClearEvents(void *record)
{
    (void) record;
    TownDayEvent *entry = (TownDayEvent *) (uintptr_t) (u32) TownRecord_Event(0);
    for (int i = 0; i < TOWN_DAY_EVENTS; i++) {
        town_record_free_entry(&entry[i]);
    }
}
CLEAN_AS(func_0204cbe0, TownRecord_ClearEvents)

/* func_0204cc04: the address of event entry `index` of data_021f39fc. */
int TownRecord_Event(int index)
{
    return (int) ((u32) (uintptr_t) data_021f3a20 + (u32) index * sizeof(TownDayEvent));
}
CLEAN_AS(func_0204cc04, TownRecord_Event)

/* func_0204cc14: every slogan message free again. */
void TownRecord_ClearSloganUsed(TownRecord *record)
{
    memset(record->slogan_used, 0, sizeof(record->slogan_used));
}
CLEAN_AS(func_0204cc14, TownRecord_ClearSloganUsed)

/* func_0204cc24: every pelican message free again. */
void TownRecord_ClearPelicanUsed(TownRecord *record)
{
    memset(record->pelican_used, 0, sizeof(record->pelican_used));
}
CLEAN_AS(func_0204cc24, TownRecord_ClearPelicanUsed)

/* func_0204cc34: the next pelican day drawn after the day `from`: in the week after `from`'s
 * (weeks from Sunday), on its Sunday or one of Wednesday to Saturday. */
void TownRecord_DrawPelicanDay(TownRecord *record, const TownDayStamp *from)
{
    int weekday = Calendar_Weekday(from->year, from->month, from->day);
    int extra;
    do {
        extra = (int) MainRandom_Below(TOWN_RECORD_WEEK);
    } while (extra == TOWN_RECORD_PELICAN_SKIP_A || extra == TOWN_RECORD_PELICAN_SKIP_B);

    DateTime when = {0};
    when.year = from->year;
    when.month = from->month;
    when.day = from->day;
    DateTime_AddDays(&when, TOWN_RECORD_WEEK - weekday + extra);

    record->pelican_day.year = when.year;
    record->pelican_day.month = when.month;
    record->pelican_day.day = when.day;
}
CLEAN_AS(func_0204cc34, TownRecord_DrawPelicanDay)

/* The item code on tile (x, z) of the town's map (from 0, 0). */
static u16 *town_record_tile(AcreMap *map, int x, int z)
{
    return AcreTile_ItemInAcre(map, (u32) (x >> TOWN_RECORD_ACRE_SHIFT), (u32) (z >> TOWN_RECORD_ACRE_SHIFT),
                               x & TOWN_RECORD_ACRE_MASK, z & TOWN_RECORD_ACRE_MASK, TOWN_RECORD_LAYER);
}

static int town_record_in(u16 code, u16 first, u16 last)
{
    return code >= first && code <= last;
}

/* func_0204cc98: on the town's map, from the fourth row of acres down, every code of the line
 * 0x5d-0x61 becomes 0x2a. */
void TownRecord_EndLine5d(void *unused)
{
    (void) unused;
    AcreMap *map = (AcreMap *) (uintptr_t) AcreMap_Town();
    if (map == NULL) {
        return;
    }
    int wide = (int) ((u32) map->acres_wide << TOWN_RECORD_ACRE_SHIFT);
    int high = (int) ((u32) map->acres_high << TOWN_RECORD_ACRE_SHIFT);
    for (int z = TOWN_RECORD_LINE_5D_FIRST_ROW; z < high; z++) {
        for (int x = 0; x < wide; x++) {
            u16 *code = town_record_tile(map, x, z);
            if (code != NULL && town_record_in(*code, TOWN_RECORD_LINE_5D_FIRST, TOWN_RECORD_LINE_5D_LAST)) {
                u16 end = TOWN_RECORD_LINE_5D_END;
                AcreTile_SetItem(map, &end, x, z, TOWN_RECORD_LAYER);
            }
        }
    }
}
CLEAN_AS(func_0204cc98, TownRecord_EndLine5d)

/* func_0204cd20: on the town's map every fruit tree (0x2f-0x56) becomes a tree of the town's
 * fruit (data_020cb758) and its tile is unmarked (AcreTile_Unmark). */
void TownRecord_PlantOwnFruit(TownRecord *record)
{
    AcreMap *map = (AcreMap *) (uintptr_t) AcreMap_Town();
    if (map == NULL) {
        return;
    }
    int wide = (int) ((u32) map->acres_wide << TOWN_RECORD_ACRE_SHIFT);
    int high = (int) ((u32) map->acres_high << TOWN_RECORD_ACRE_SHIFT);
    u16 tree = data_020cb758[record->own_fruit];
    for (int z = 0; z < high; z++) {
        for (int x = 0; x < wide; x++) {
            u16 *code = town_record_tile(map, x, z);
            if (code != NULL && town_record_in(*code, TOWN_RECORD_FRUIT_TREE_FIRST, TOWN_RECORD_FRUIT_TREE_LAST)) {
                u16 planted = tree;
                AcreTile_SetItem(map, &planted, x, z, TOWN_RECORD_LAYER);
                AcreTile_Unmark(map, x, z);
            }
        }
    }
}
CLEAN_AS(func_0204cd20, TownRecord_PlantOwnFruit)

/* func_0204cdc8: the day set back to today when today is before it. */
void TownRecord_PullBackDay(Date *day)
{
    Date today;
    Calendar_Today(&today);
    if (!Calendar_IsOnOrAfter(&today, day)) {
        *day = today;
    }
}
CLEAN_AS(func_0204cdc8, TownRecord_PullBackDay)

/* 1 January 2000, the day the record's days start from. */
static void town_record_first_day(Date *day)
{
    day->day = 1;
    day->month = 1;
    day->year = 0;
    day->unused = 0;
}

/* What TownRecord_Init and TownRecord_Start both do after the pelican day: the messages and
 * events free, the players' days and unk_54 at the first day, the summary not counted. */
static void town_record_reset_days(TownRecord *record)
{
    for (int i = 0; i < TOWN_RECORD_PLAYERS; i++) {
        town_record_first_day(&record->player_days[i]);
    }
    record->summary_days = -1;
    town_record_first_day(&record->unk_54);
}

/* func_0204cdfc: the record set up with the state block: today's day, fruit 0, the pelican day
 * at the first day, every message and event free, the players' days at the first day. */
void TownRecord_Init(TownRecord *record)
{
    Calendar_Today(&record->today);
    record->own_fruit = 0;
    town_record_first_day(&record->pelican_day);
    TownRecord_ClearPelicanUsed(record);
    TownRecord_ClearSloganUsed(record);
    TownRecord_ClearEvents(record);
    town_record_reset_days(record);
}
CLEAN_AS(func_0204cdfc, TownRecord_Init)

/* func_0204ce64: the record of a town being started: today's day, a fruit drawn, the pelican
 * day drawn from today, every message free, the town's fruit trees planted and the line
 * 0x5d-0x61 ended (TownRecord_EndLine5d), every event free, the players' days at the first
 * day; then the town's day refreshed (TownDay_Refresh) and the board's last day at never.
 * QUIRK: today's weekday is asked for once more and not used. */
void TownRecord_Start(TownRecord *record)
{
    Calendar_Today(&record->today);
    record->own_fruit = MainRandom_Below(TOWN_RECORD_FRUITS);
    Calendar_Weekday(record->today.year, record->today.month, record->today.day);
    TownRecord_DrawPelicanDay(record, (const TownDayStamp *) (const void *) &record->today);
    TownRecord_ClearPelicanUsed(record);
    TownRecord_ClearSloganUsed(record);
    TownRecord_PlantOwnFruit(record);
    TownRecord_EndLine5d(record);
    TownRecord_ClearEvents(record);
    town_record_reset_days(record);
    TownDay_Refresh();
    record->unk_6b = 0;
    record->last_day[2] = TOWN_RECORD_NEVER;
    record->last_day[1] = TOWN_RECORD_NEVER;
    record->last_day[0] = TOWN_RECORD_NEVER;
    record->events_posted = 0;
}
CLEAN_AS(func_0204ce64, TownRecord_Start)

/* func_0204cf0c: the destructor; nothing to do. */
void TownRecord_Destruct(void *record)
{
    (void) record;
}
CLEAN_AS(func_0204cf0c, TownRecord_Destruct)

/* func_0204cf10: the constructor; nothing to do. */
void TownRecord_Construct(void *record)
{
    (void) record;
}
CLEAN_AS(func_0204cf10, TownRecord_Construct)
