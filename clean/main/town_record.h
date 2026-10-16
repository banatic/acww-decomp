/* The town's record in the state block (StateBlock.part_17254, data_021f39fc, 0x6c bytes): the
 * day the town was last brought up to (town_day.h), the town's own fruit, the bulletin board's
 * state (board_notices.h), the period of the day, the four events the town takes part in, and
 * a day for each player.
 *
 * The town's fruit is one of the five items 0x1518-0x151c (planted, each becomes a tree code of
 * the five lines of eight at 0x2f-0x56; map_item.h), drawn when the town is started: its trees
 * are the only fruit trees the new town gets (TownRecord_PlantOwnFruit), and it sells for a
 * fifth of the others' price (ItemTraits_Price). */
#ifndef CLEAN_MAIN_TOWN_RECORD_H
#define CLEAN_MAIN_TOWN_RECORD_H

#include "calendar.h"
#include "town_day.h" /* TownDayEvent, TownDayStamp */
#include "types.h"

#define TOWN_RECORD_FRUITS 5
#define TOWN_RECORD_PLAYERS 4
#define TOWN_RECORD_PELICAN_BYTES 10
#define TOWN_RECORD_SLOGAN_BYTES 11
/* The last period of the day (Calendar_PeriodBOf). */
#define TOWN_RECORD_LAST_PERIOD 0x16
/* The town summary's answer (func_0204a3cc) whose days in a row are counted, and the count
 * TownRecord_Summary4Long asks for. */
#define TOWN_RECORD_SUMMARY_COUNTED 4
#define TOWN_RECORD_SUMMARY_LONG_DAYS 15

typedef struct TownRecord {
    Date today;                                 /* 0x00: the day the town was brought up to */
    u32 own_fruit;                              /* 0x04: 0-4, the item 0x1518 + own_fruit */
    Date pelican_day;                           /* 0x08: BoardNoticesState.pelican_day */
    u8 pelican_used[TOWN_RECORD_PELICAN_BYTES]; /* 0x0c: BoardNoticesState.pelican_used */
    u8 slogan_used[TOWN_RECORD_SLOGAN_BYTES];   /* 0x16: BoardNoticesState.slogan_used */
    s8 summary_days;                            /* 0x21: days in a row the summary was 4, -1 */
    u8 events_posted;                           /* 0x22: BoardNoticesState.events_posted */
    u8 period;                                  /* 0x23: the period of the town's day */
    TownDayEvent events[TOWN_DAY_EVENTS];       /* 0x24: data_021f3a20 */
    Date unk_54;                                /* 0x54 */
    Date player_days[TOWN_RECORD_PLAYERS];      /* 0x58: the day each player last used a turn */
    u8 last_day[3];                             /* 0x68: BoardNoticesState.last_day */
    u8 unk_6b;                                  /* 0x6b */
} TownRecord;

int TownRecord_OwnFruit(const TownRecord *record);
void TownRecord_SetPeriod(u32 period);
u8 TownRecord_Period(void);
void TownRecord_CountSummaryDays(TownRecord *record, int summary, int days);
int TownRecord_Summary4Long(void);
int TownRecord_PlayerTurnLeft(TownRecord *record);
void TownRecord_UsePlayerTurn(int record);
int TownRecord_PlayerDay(int record, int player);
int TownRecord_MarkEvent(int record, int event);
int TownRecord_FindEvent(int record, int event);
void TownRecord_FreeEvent(int record, int event);
void TownRecord_ClearEvents(void *record);
int TownRecord_Event(int index);
void TownRecord_ClearSloganUsed(TownRecord *record);
void TownRecord_ClearPelicanUsed(TownRecord *record);
void TownRecord_DrawPelicanDay(TownRecord *record, const TownDayStamp *from);
void TownRecord_EndLine5d(void *unused);
void TownRecord_PlantOwnFruit(TownRecord *record);
void TownRecord_PullBackDay(Date *day);
void TownRecord_Init(TownRecord *record);
void TownRecord_Start(TownRecord *record);
void TownRecord_Destruct(void *record);
void TownRecord_Construct(void *record);

#endif
