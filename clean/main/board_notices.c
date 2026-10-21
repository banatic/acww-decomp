/* The notices the game puts on the town's bulletin board (board_notices.h). */
#include "board_notices.h"

#include "bbs.h"
#include "clean.h"
#include "date_time.h"
#include "mail_text.h"
#include "npc_id.h"
#include "npc_lookup.h"
#include "player_records.h"
#include "process_020dabc0.h"
#include "town_villager.h"
#include "villager_roster.h"
#include "villager_town.h"
#include "main_random.h"
#include "player_id.h"
#include "town_record.h"

static_assert(sizeof(BoardNoticesState) == sizeof(((StateBlock *) NULL)->part_17254), "BoardNoticesState");
static_assert(offsetof(BoardNoticesState, pelican_day) == 0x1725c - 0x17254, "BoardNoticesState.pelican_day");
static_assert(offsetof(BoardNoticesState, pelican_used) == 0x17260 - 0x17254, "BoardNoticesState.pelican_used");
static_assert(offsetof(BoardNoticesState, slogan_used) == 0x1726a - 0x17254, "BoardNoticesState.slogan_used");
static_assert(offsetof(BoardNoticesState, events_posted) == 0x17276 - 0x17254, "BoardNoticesState.events_posted");
static_assert(offsetof(BoardNoticesState, last_day) == 0x172bc - 0x17254, "BoardNoticesState.last_day");
static_assert(sizeof(EventCalendarEvent) == 12, "EventCalendarEvent");

extern StateBlock data_021dc7a8;
extern VillagerTown data_021e5a2c; /* the state block's villagers */
/* An object of main that the functions here are handed and never read. */
extern u8 data_021c7768[];

extern const char data_020db864[]; /* "bbs_event" */
extern const char data_020db870[]; /* "bbs_pelican" */
extern const char data_020db87c[]; /* "bbs_slogan" */
/* The "bbs_event" message of each calendar event 0x1c-0x39 (the events 0x1c-0x22 take the
 * messages 0-6, 0x23 and 0x24 take 0x1c and 0x1d, the others 7-0x1b in order). */
extern const u32 data_020cb5c0[0x3a - 0x1c];

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

#define BOARD_NOTICES_NEVER 0xff
#define BOARD_NOTICES_BIRTHDAYS 8 /* events 0-7: the birthday of the villager of that number */
#define BOARD_NOTICES_FIRST_EVENT 0x1c
#define BOARD_NOTICES_LAST_EVENT 0x39
#define BOARD_NOTICES_BIRTHDAY_MESSAGE 0x1e /* and the two after it, one drawn */
#define BOARD_NOTICES_NO_MESSAGE (-1)

static BoardNoticesState *BoardNotices_State(StateBlock *block)
{
    return (BoardNoticesState *) block->part_17254;
}

/* A board day as a DateTime at 0:00:00. */
static void BoardNotices_DayToDateTime(DateTime *when, const BoardNoticesDay *day)
{
    when->second = 0;
    when->minute = 0;
    when->hour = 0;
    when->day = day->day;
    when->month = day->month;
    when->year = day->year;
    when->unused[0] = 0;
    when->unused[1] = 0;
}

/* Whether more than one player lives in the town, or func_0203fae4 does not hold the notices
 * back. */
static int BoardNotices_MayPostEvents(StateBlock *block)
{
    return PlayerRecords_CountTown(block->players) > 1 || !Process020dabc0_IsHeldBack();
}

/* func_02042500: the board brought up to date: when a board day (from 6:00) began since the
 * last one seen, it becomes the last one and the notices of each day since are posted (the
 * pelican day first moved up to the first of them). On the same board day, the day's event
 * notices are posted if the board has had none yet and BoardNotices_MayPostEvents. */
void BoardNotices_Update(void)
{
    StateBlock *block = &data_021dc7a8;
    BoardNoticesState *state = BoardNotices_State(block);
    DateTime now = {0};
    DateTime_Now(&now);
    DateTime_SubtractHours(&now, BOARD_NOTICES_DAY_START_HOURS);
    int days = BoardNotices_DaysSince((int) (uintptr_t) data_021c7768, &state->last_day, &now);
    if (days != 0) {
        state->last_day.year = now.year;
        state->last_day.month = now.month;
        state->last_day.day = now.day;
        DateTime_SubtractDays(&now, days - 1);
        int weekday = Calendar_Weekday(now.year, now.month, now.day);
        BoardNotices_CatchUpPelicanDay((int) (uintptr_t) data_021c7768, block, &now);
        BoardNotices_PostDays(data_021c7768, block, days, &now, weekday);
    } else if (!state->events_posted && BoardNotices_MayPostEvents(block)) {
        BoardNotices_PostFirstEvents((int) (uintptr_t) data_021c7768, block, &now);
    }
}
CLEAN_AS(func_02042500, BoardNotices_Update)

/* func_020425a8: the notices of `days` days from `first` (whose weekday is `weekday`): the
 * pelican notice on the pelican day (and the next pelican day drawn), the slogan on a Monday,
 * the events of each day once the board had its first notices (or BoardNotices_MayPostEvents,
 * asked once). */
void BoardNotices_PostDays(void *unused, StateBlock *block, int days, const DateTime *first, int weekday)
{
    BoardNoticesState *state = BoardNotices_State(block);
    DateTime pelican = {0};
    DateTime day = {0};
    DateTime copy;
    MI_CpuCopy8(first, &day, sizeof(DateTime));
    int post_events = state->events_posted || BoardNotices_MayPostEvents(block);

    for (; days > 0; days--) {
        BoardNotices_DayToDateTime(&pelican, &state->pelican_day);
        if (DateTime_DaysBetween(&day, &pelican) == 0) {
            MI_CpuCopy8(&pelican, &copy, sizeof(DateTime));
            BoardNotices_PostPelican(unused, block, &copy);
            TownRecord_DrawPelicanDay((TownRecord *) state, (const TownDayStamp *) &state->pelican_day);
        }
        if (weekday == BOARD_NOTICES_SLOGAN_WEEKDAY) {
            MI_CpuCopy8(&day, &copy, sizeof(DateTime));
            BoardNotices_PostSlogan(unused, block, &copy);
        }
        if (post_events) {
            BoardNotices_PostFirstEvents((int) (uintptr_t) unused, block, &day);
        }
        weekday = (weekday + 1) % 7;
        DateTime_AddDays(&day, 1);
    }
}
CLEAN_AS(func_020425a8, BoardNotices_PostDays)

/* func_02042684: the notices of the events on `when`'s day, and the board marked as having had
 * its first notices. */
void BoardNotices_PostFirstEvents(int unused, StateBlock *block, const DateTime *when)
{
    DateTime day = {0};
    DateTime asked;
    DateTime posted;
    EventCalendarEvent events[BOARD_NOTICES_EVENTS];
    MI_CpuCopy8(when, &day, sizeof(DateTime));
    MI_CpuCopy8(&day, &asked, sizeof(DateTime));
    if (EventCalendar_ListAll(events, &asked) > 0) {
        MI_CpuCopy8(&day, &posted, sizeof(DateTime));
        BoardNotices_PostEvents(unused, events, &posted);
    }
    BoardNotices_State(block)->events_posted = 1;
}
CLEAN_AS(func_02042684, BoardNotices_PostFirstEvents)

/* func_020426d8: the pelican day moved on (func_0204cc34) until it is not before `when`. */
void BoardNotices_CatchUpPelicanDay(int unused, StateBlock *block, const DateTime *when)
{
    (void) unused;
    BoardNoticesState *state = BoardNotices_State(block);
    DateTime pelican;
    BoardNotices_DayToDateTime(&pelican, &state->pelican_day);
    while (DateTime_DaysBetween(when, &pelican) < 0) {
        TownRecord_DrawPelicanDay((TownRecord *) state, (const TownDayStamp *) &state->pelican_day);
        BoardNotices_DayToDateTime(&pelican, &state->pelican_day);
    }
}
CLEAN_AS(func_020426d8, BoardNotices_CatchUpPelicanDay)

/* func_02042730: the board days from `last` to `now`: 0 on the same day, 1 when there was none
 * (or `now` is before `last`), 31 at most. */
int BoardNotices_DaysSince(int unused, const BoardNoticesDay *last, const DateTime *now)
{
    (void) unused;
    if (last->year == BOARD_NOTICES_NEVER && last->month == BOARD_NOTICES_NEVER && last->day == BOARD_NOTICES_NEVER) {
        return 1;
    }
    if (last->year == now->year && last->month == now->month && last->day == now->day) {
        return 0;
    }
    DateTime from;
    BoardNotices_DayToDateTime(&from, last);
    int days = DateTime_DaysBetween(&from, now);
    if (days > BOARD_NOTICES_MAX_DAYS) {
        return BOARD_NOTICES_MAX_DAYS;
    }
    if (days < 0) {
        return 1;
    }
    return days;
}
CLEAN_AS(func_02042730, BoardNotices_DaysSince)

/* func_02042798: a "bbs_event" notice dated `when` for each of the seven listed events that has
 * one: a villager's birthday (events 0-7, with the villager's name as the message's part 0 and
 * one of three messages drawn), or a calendar event (0x1c-0x39) running on that date. */
void BoardNotices_PostEvents(int unused, const EventCalendarEvent *events, const DateTime *when)
{
    (void) unused;
    BoardNoticesText name;
    DateTime asked;
    PlayerIdText_Construct((PlayerIdText *) &name);
    for (int i = 0; i < BOARD_NOTICES_EVENTS; i++, events++) {
        int message = BOARD_NOTICES_NO_MESSAGE;
        int id = events->id;
        if (id < BOARD_NOTICES_BIRTHDAYS) {
            u8 *villager = VillagerRoster_At(&data_021e5a2c, id);
            NpcId *npc;
            if (villager != NULL && (npc = TownVillager_NpcId(villager)) != NULL) {
                NpcLookup_FormatName((char *) &name, NpcId_Number(npc));
                MailText_SetPartText(0, &name);
                message = (int) MainRandom_Below(3) + BOARD_NOTICES_BIRTHDAY_MESSAGE;
            }
        } else if (id >= BOARD_NOTICES_FIRST_EVENT && id <= BOARD_NOTICES_LAST_EVENT) {
            MI_CpuCopy8(when, &asked, sizeof(DateTime));
            int state = EventCalendar_StateOn(id, &asked, 0);
            if (state == EVENT_CALENDAR_ON || state == EVENT_CALENDAR_ENDING) {
                message = (int) data_020cb5c0[id - BOARD_NOTICES_FIRST_EVENT];
            }
        }
        if (message != BOARD_NOTICES_NO_MESSAGE) {
            Bbs_PostMessageDated(message, data_020db864, when->year, when->month, when->day);
        }
    }
    PlayerIdText_Destruct((PlayerIdText *) &name);
}
CLEAN_AS(func_02042798, BoardNotices_PostEvents)

/* The flags BoardNotices_PostDrawn packs: whole bytes of the most messages and one more flag
 * (for BoardNotices_PostUnused's REQUIRES). */
#define BOARD_NOTICES_DRAWN_FLAGS ((BOARD_NOTICES_SLOGAN_MESSAGES + 1 + 7) / 8 * 8)

/* The notice of `archive` drawn among those not used yet (the bits at `bits`, `count`
 * messages); all are free again when none is left.
 * BUG: the bits are packed back in whole bytes, so their last byte also takes the 4 flags after
 * `count` (BoardNotices_PackBits shifts each whole byte in), which the ROM reads from past its
 * buffer of `count` flags: its stack there holds the caller's saved r4, the address
 * BoardNotices_PostDays (the only caller) keeps of the pelican day, `residue` here. Clean puts
 * that word's bytes there too, so the town record gets the ROM's bits (BUGFIX: pack the `count`
 * flags only and keep the byte's other bits).
 * REQUIRES: called from BoardNotices_PostDays, as the ROM's code is. */
static void BoardNotices_PostDrawn(void *unused, u8 *bits, int count, const char *archive, const DateTime *when, u32 residue)
{
    u8 used[BOARD_NOTICES_DRAWN_FLAGS] = {0};
    DateTime copy;
    int bytes = (count + 7) / 8;
    int left = BoardNotices_UnpackBits((int) (uintptr_t) unused, used, bits, count);
    if (left == 0) {
        left = count;
        MI_CpuFill8(used, 0, (u32) count);
    }
    for (int i = count; i < bytes * 8; i++) {
        used[i] = (u8) (residue >> (8 * ((i - count) & 3)));
    }
    int pick = (int) MainRandom_Below(left);
    MI_CpuCopy8(when, &copy, sizeof(DateTime));
    BoardNotices_PostUnused((int) (uintptr_t) unused, pick, archive, used, count, &copy);
#ifdef BUGFIX
    u8 kept = bits[bytes - 1];
    BoardNotices_PackBits(unused, bits, used, bytes);
    u8 mask = (u8) ((1u << (count - (bytes - 1) * 8)) - 1);
    bits[bytes - 1] = (u8) ((bits[bytes - 1] & mask) | (kept & ~mask));
#else
    BoardNotices_PackBits(unused, bits, used, bytes);
#endif
}

/* func_0204287c: the pelican notice of the day. */
void BoardNotices_PostPelican(void *unused, StateBlock *block, const DateTime *when)
{
    BoardNoticesState *state = BoardNotices_State(block);
    BoardNotices_PostDrawn(unused, state->pelican_used, BOARD_NOTICES_PELICAN_MESSAGES, data_020db870, when,
                           (u32) (uintptr_t) &state->pelican_day);
}
CLEAN_AS(func_0204287c, BoardNotices_PostPelican)

/* func_020428e8: the slogan notice of the week. */
void BoardNotices_PostSlogan(void *unused, StateBlock *block, const DateTime *when)
{
    BoardNoticesState *state = BoardNotices_State(block);
    BoardNotices_PostDrawn(unused, state->slogan_used, BOARD_NOTICES_SLOGAN_MESSAGES, data_020db87c, when,
                           (u32) (uintptr_t) &state->pelican_day);
}
CLEAN_AS(func_020428e8, BoardNotices_PostSlogan)

/* func_02042954: message number `pick` among the unused ones (the zero flags of `used`, `count`
 * of them) marked used and posted from `archive`, dated `when`; Bbs_PostMessageDated's result.
 * Without flags, message 0 is posted.
 * REQUIRES: `pick` is below the number of unused messages, as the callers draw it; else the
 * flag after the last is set. */
int BoardNotices_PostUnused(int unused, int pick, const char *archive, u8 *used, int count, const DateTime *when)
{
    (void) unused;
    int message = 0;
    if (used != NULL) {
        for (; message < count; message++) {
            if (used[message] == 0 && --pick < 0) {
                break;
            }
        }
        used[message] = 1;
    }
    return (int) (uintptr_t) Bbs_PostMessageDated(message, archive, when->year, when->month, when->day);
}
CLEAN_AS(func_02042954, BoardNotices_PostUnused)

/* func_020429a0: `bytes` bytes of bits made from eight flags each, the first flag in bit 0. */
void BoardNotices_PackBits(void *unused, u8 *bits, const u8 *flags, int bytes)
{
    (void) unused;
    for (int i = 0; i < bytes; i++, flags += 8) {
        u32 byte = 0;
        for (int bit = 0; bit < 8; bit++) {
            byte |= (u32) flags[bit] << bit;
        }
        bits[i] = (u8) byte;
    }
}
CLEAN_AS(func_020429a0, BoardNotices_PackBits)

/* func_02042a08: `count` flags (0 or 1) from the bits, the first from bit 0; how many are 0.
 * QUIRK: after each whole byte of flags the next byte is read, also past the last one needed. */
int BoardNotices_UnpackBits(int unused, u8 *flags, const u8 *bits, int count)
{
    (void) unused;
    int zeros = 0;
    u32 byte = *bits;
    for (int i = 0; i < count; i++) {
        flags[i] = (u8) ((byte >> (i & 7)) & 1);
        if (flags[i] == 0) {
            zeros++;
        }
        if ((i + 1) % 8 == 0) {
            bits++;
            byte = *bits;
        }
    }
    return zeros;
}
CLEAN_AS(func_02042a08, BoardNotices_UnpackBits)
