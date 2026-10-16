/* The notices the game puts on the town's bulletin board (bbs.h) as the days go by. A board day
 * starts at 6:00; the first time the game looks after a board day began, it catches up on
 * every day since the last one it saw (31 at most):
 *
 *   - on a day drawn for it each week, a notice of "bbs_pelican" (76 messages);
 *   - on Mondays, a notice of "bbs_slogan" (84 messages);
 *   - each day, a notice of "bbs_event" for each villager's birthday and each event of the
 *     calendar that is on that day, once the board has had its first notices (see
 *     BoardNoticesState.events_posted).
 *
 * The pelican and slogan notices are drawn among the messages not used yet, kept as one bit
 * per message; when all were used, all are free again. The state lives in the state block
 * (data_021dc7a8) from 0x17254. */
#ifndef CLEAN_MAIN_BOARD_NOTICES_H
#define CLEAN_MAIN_BOARD_NOTICES_H

#include "calendar.h"
#include "event_calendar.h"
#include "state_block.h"
#include "types.h"

#define BOARD_NOTICES_PELICAN_MESSAGES 0x4c
#define BOARD_NOTICES_SLOGAN_MESSAGES 0x54
#define BOARD_NOTICES_MAX_DAYS 31
#define BOARD_NOTICES_EVENTS 7 /* the events EventCalendar_ListAll gives at most */
#define BOARD_NOTICES_DAY_START_HOURS 6
#define BOARD_NOTICES_SLOGAN_WEEKDAY 1 /* Monday */

/* A day as three bytes: day, month, year (from 2000). 0xff 0xff 0xff: never. */
typedef struct BoardNoticesDay {
    u8 day;
    u8 month;
    u8 year;
} BoardNoticesDay;

/* StateBlock.part_17254 */
typedef struct BoardNoticesState {
    u8 unk_00[8];                                              /* 0x17254 */
    BoardNoticesDay pelican_day;                               /* 0x1725c: the next pelican notice's day */
    u8 unk_0b;                                                 /* 0x1725f */
    u8 pelican_used[(BOARD_NOTICES_PELICAN_MESSAGES + 7) / 8]; /* 0x17260 */
    u8 slogan_used[(BOARD_NOTICES_SLOGAN_MESSAGES + 7) / 8];   /* 0x1726a */
    u8 unk_21;                                                 /* 0x17275 */
    u8 events_posted;                                          /* 0x17276: cleared with the town's last player */
    u8 unk_23[0x68 - 0x23];                                    /* 0x17277 */
    BoardNoticesDay last_day;                                  /* 0x172bc: the last board day seen */
    u8 unk_6b;                                                 /* 0x172bf */
} BoardNoticesState;

/* The text a villager's name is written into (0x24 bytes; func_02094fd4 builds it,
 * func_02094fbc destroys it). */
typedef struct BoardNoticesText {
    u32 words[0x24 / 4];
} BoardNoticesText;

void BoardNotices_Update(void);
void BoardNotices_PostDays(void *unused, StateBlock *block, int days, const DateTime *first, int weekday);
void BoardNotices_PostFirstEvents(int unused, StateBlock *block, const DateTime *when);
void BoardNotices_CatchUpPelicanDay(int unused, StateBlock *block, const DateTime *when);
int BoardNotices_DaysSince(int unused, const BoardNoticesDay *last, const DateTime *now);
void BoardNotices_PostEvents(int unused, const EventCalendarEvent *events, const DateTime *when);
void BoardNotices_PostPelican(void *unused, StateBlock *block, const DateTime *when);
void BoardNotices_PostSlogan(void *unused, StateBlock *block, const DateTime *when);
int BoardNotices_PostUnused(int unused, int pick, const char *archive, u8 *used, int count, const DateTime *when);
void BoardNotices_PackBits(void *unused, u8 *bits, const u8 *flags, int bytes);
int BoardNotices_UnpackBits(int unused, u8 *flags, const u8 *bits, int count);

#endif
