/* The letters from the player's mother (mom_letters.h). */
#include "mom_letters.h"

#include "calendar.h"
#include "clean.h"
#include "date_time.h"
#include "mail.h"
#include "item_lists.h"
#include "letter.h"
#include "main_random.h"
#include "player_record.h"
#include "player_records.h"

#define NO_ITEM 0xfff1

#define MONTHS 12
#define SUNDAY 0

/* The byte the letter keeps at 0xfb: 0x12 for the Father's Day letter, else 1. */
#define LETTER_KIND 1
#define LETTER_KIND_FATHERS_DAY 0x12

/* The paper sets MomLetters_PaperFromSet draws from (data_020d18e0 and data_020e3058); the
 * letters always use the last. */
#define PAPER_SET_MOM 3

/* The week after the birthday, the birthday included, in DateTime_AddDays's days. */
#define BIRTHDAY_WEEK 7

/* The presents. Letters of these numbers carry an item drawn from an item list
 * (func_02063ccc's kinds 2 and 0) or from func_02063414; the items 0x1518-0x151c are drawn
 * among, leaving out the one the word at data_021f39a8 + 0x58 names. */
#define PRESENT_RANGE_FIRST 0x1518
#define PRESENT_RANGE_COUNT 5
#define PRESENT_LIST_A 2
#define PRESENT_LIST_B 0

/* A list of items (func_02063ccc constructs it, func_02063cc8 destructs it). */
typedef struct MomItemList {
    int kind;
    int unk_04;
} MomItemList;

typedef struct MomGlobal {
    u8 unk_00[0x58];
    u32 unk_58;
} MomGlobal;

extern const char data_020e307c[];     /* "mother_day" */
extern const char data_020e3088[];     /* "mother_always" */
extern const char data_020e3098[];     /* "mother_season" */
extern const u8 data_020e3030[MONTHS]; /* each month's first letter, after MOM_SEASON_FIRST */
extern const u8 data_020e303c[MONTHS]; /* and how many it has */
/* The papers for each season (spring, summer, autumn, winter) and how many each table holds. */
extern const u8 *const data_020e3048[4];
extern const int data_020d18d0[4];
/* The paper sets: tables of papers and their sizes. */
extern const u8 *const data_020e3058[];
extern const int data_020d18e0[];
extern MomGlobal data_021f39a8;

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

static u8 *sent_bits(MomLetterState *state)
{
    return (u8 *) state + offsetof(MomLetterState, sent);
}

/* func_02096ebc: a letter's number within its template. */
u8 MomLetters_GroupIndex(int letter)
{
    if (letter >= MOM_DAY_FIRST && letter < MOM_ALWAYS_FIRST) {
        return (u8) letter;
    }
    if (letter >= MOM_ALWAYS_FIRST && letter < MOM_SEASON_FIRST) {
        return (u8) (letter - MOM_ALWAYS_FIRST);
    }
    return (u8) (letter - MOM_SEASON_FIRST);
}
CLEAN_AS(func_02096ebc, MomLetters_GroupIndex)

/* The present range's item `i`, the first one past the range. */
static u16 range_item(u32 i)
{
    return (u16) (i < PRESENT_RANGE_COUNT ? PRESENT_RANGE_FIRST + i : PRESENT_RANGE_FIRST);
}

static u16 list_item(int kind)
{
    MomItemList list;
    u16 item;
    ItemList_Construct((ItemList *) &list, kind, 0);
    ItemLists_Draw(&item, (ItemList *) &list, 0, 0, 1, 1, 0);
    ItemList_Destruct(&list);
    return item;
}

/* func_02096ee4: the item letter `letter` carries, NO_ITEM for none. */
int MomLetters_Present(int letter)
{
    switch (letter) {
        case 0x23:
        case 0x32:
        case 0x5f:
        case 0x73:
            return list_item(PRESENT_LIST_A);
        case 0x4a: {
            u16 item;
            ItemLists_DrawRange(&item, 0x1380, 0x20, 0, 0, 0, 1, 0xa, 0, 1);
            return item;
        }
        case 0x1e:
        case 0x1f:
            return list_item(PRESENT_LIST_B);
        case 0x25:
        case 0x37:
        case 0x38:
        case 0x51: {
            /* One of the range other than the one data_021f39a8 names, at random. */
            u16 excluded = range_item(data_021f39a8.unk_58);
            int skip = (int) MainRandom_Below(4);
            for (u32 i = 0; i < PRESENT_RANGE_COUNT; i++) {
                u16 item = range_item(i);
                if (item == excluded) {
                    continue;
                }
                if (skip <= 0) {
                    return item;
                }
                skip--;
            }
            return PRESENT_RANGE_FIRST;
        }
        case 0x2e:
            return 0x149b;
        case 0:
        case 1:
            return 0x14a4;
        case 0x6e:
        case 0x6f:
            return 0x1542;
        case 0x72:
            return 0x1518;
        case 0x48:
            return 0x3648;
        case 0x47:
            return 0x3420;
    }
    return NO_ITEM;
}
CLEAN_AS(func_02096ee4, MomLetters_Present)

/* func_020970a4: the template a letter is written from. */
const char *MomLetters_Template(int letter)
{
    if (letter >= MOM_DAY_FIRST && letter < MOM_ALWAYS_FIRST) {
        return data_020e307c;
    }
    if (letter >= MOM_ALWAYS_FIRST && letter < MOM_SEASON_FIRST) {
        return data_020e3088;
    }
    return data_020e3098;
}
CLEAN_AS(func_020970a4, MomLetters_Template)

/* func_020970cc: write letter `letter` to the current player, on a paper for `month`, with its
 * present, and post it, else leave it at the post office; 0 when there is no room for it in
 * either. */
int MomLetters_Send(int letter, int month)
{
    Letter mail;
    Letter_Construct(&mail);
    Letter_Clear(&mail);
    void *name = PlayerRecord_Player(PlayerRecords_Current());
    u8 message = MomLetters_GroupIndex(letter);
    u8 kind = letter == MOM_FATHERS_DAY ? LETTER_KIND_FATHERS_DAY : LETTER_KIND;
    u8 paper = (u8) MomLetters_DrawPaper(PAPER_SET_MOM, month);
    Letter_WriteSpecialToPlayer(&mail, &message, MomLetters_Template(letter), &kind, &paper, name);
    int item = MomLetters_Present(letter);
    if (item != NO_ITEM) {
        Letter_SetItem(&mail, (u16) item, 1);
    }
    int sent = Mail_Post(&mail) != 0 || Mail_HoldAtPostOffice(&mail, 0) != 0;
    Letter_Destruct(&mail);
    return sent;
}
CLEAN_AS(func_020970cc, MomLetters_Send)

/* func_02097188: send one of the letters first..first + count - 1 not sent yet, at random, and
 * mark it sent; 0 when none was sent. With none left, `recycle` unmarks them all first, else
 * none is sent. QUIRK: with `recycle`, sending the last one left unmarks the whole group
 * instead, the one just sent included. */
int MomLetters_SendOneOf(int first, int count, int month, int recycle)
{
    MomLetterState *state = PlayerRecord_MomLetterState(PlayerRecords_Current());
    int unsent = MomLetters_CountUnsent(first, count);
    if (unsent == 0) {
        if (recycle == 0) {
            return 0;
        }
        unsent = count;
        MomLetters_Unmark(first, count);
        recycle = 0;
    }
    int pick = (int) MainRandom_Below(unsent);
    int letter = MomLetters_NthUnsent(first, count, pick);
    int sent = MomLetters_Send(letter, month);
    if (sent != 0) {
        if (unsent == 1 && recycle == 1) {
            MomLetters_Unmark(first, count);
        } else {
            MomLetterState_MarkSent(state, letter);
        }
    }
    return sent;
}
CLEAN_AS(func_02097188, MomLetters_SendOneOf)

/* func_02097204: mark letters first..first + count - 1 not sent. */
void MomLetters_Unmark(int first, int count)
{
    MomLetterState *state = PlayerRecord_MomLetterState(PlayerRecords_Current());
    for (int i = 0; i < count; i++) {
        MomLetterState_Unmark(state, first + i);
    }
}
CLEAN_AS(func_02097204, MomLetters_Unmark)

/* func_02097234: the n-th (from 0) of letters first..first + count - 1 not sent yet; `first`
 * when there are not that many. */
int MomLetters_NthUnsent(int first, int count, int n)
{
    MomLetterState *state = PlayerRecord_MomLetterState(PlayerRecords_Current());
    int seen = 0;
    for (int i = 0; i < count; i++) {
        if (MomLetterState_IsSent(state, first + i) == 0) {
            if (seen == n) {
                return first + i;
            }
            seen++;
        }
    }
    return first;
}
CLEAN_AS(func_02097234, MomLetters_NthUnsent)

/* func_0209727c: how many of letters first..first + count - 1 are not sent yet. */
int MomLetters_CountUnsent(int first, int count)
{
    MomLetterState *state = PlayerRecord_MomLetterState(PlayerRecords_Current());
    int unsent = 0;
    for (int i = 0; i < count; i++) {
        if (MomLetterState_IsSent(state, first + i) == 0) {
            unsent++;
        }
    }
    return unsent;
}
CLEAN_AS(func_0209727c, MomLetters_CountUnsent)

/* func_020972b4: mark the letters of every month but `month` not sent. */
void MomLetters_UnmarkOtherMonths(int month)
{
    for (int m = 1; m <= MONTHS; m++) {
        if (m == month) {
            continue;
        }
        MomLetters_Unmark(MomLetters_SeasonFirst((u8) m), MomLetters_SeasonCount((u8) m));
    }
}
CLEAN_AS(func_020972b4, MomLetters_UnmarkOtherMonths)

/* func_020972e4: how many letters month `month` (1-12) has. */
u8 MomLetters_SeasonCount(u32 month)
{
    return data_020e303c[month - 1];
}
CLEAN_AS(func_020972e4, MomLetters_SeasonCount)

/* func_020972f0: the first letter of month `month` (1-12). */
int MomLetters_SeasonFirst(int month)
{
    return data_020e3030[month - 1] + MOM_SEASON_FIRST;
}
CLEAN_AS(func_020972f0, MomLetters_SeasonFirst)

/* func_02097300: a letter of the date's month, or one of the letters for any time: while some
 * of the month's were sent, a draw over all those not sent yet picks the group. */
int MomLetters_SendSeasonalOrAlways(MomDate *date)
{
    int first = MomLetters_SeasonFirst((u8) date->month);
    int count = MomLetters_SeasonCount((u8) date->month);
    int unsent = MomLetters_CountUnsent(first, count);
    if (unsent == count) {
        return MomLetters_SendOneOf(first, count, (u8) date->month, 0);
    }
    int draw = (int) MainRandom_Below(MomLetters_CountUnsent(MOM_ALWAYS_FIRST, MOM_ALWAYS_COUNT) + unsent);
    if (draw < unsent) {
        return MomLetters_SendOneOf(first, count, (u8) date->month, 0);
    }
    return MomLetters_SendOneOf(MOM_ALWAYS_FIRST, MOM_ALWAYS_COUNT, (u8) date->month, 1);
}
CLEAN_AS(func_02097300, MomLetters_SendSeasonalOrAlways)

/* func_0209737c: the letter for the date's day of the year, if it has one: days N/N, April 1st,
 * December 24th, Father's Day and Mother's Day; 0 when none was sent. */
int MomLetters_SendForDay(MomDate *date)
{
    int month = (int) date->month;
    int day = (int) date->day;
    if (month == day) {
        return MomLetters_SendOneOf(MOM_DAY_FIRST + 2 * day - 2, 2, (u8) month, 1);
    }
    if (month == 4 && day == 1) {
        return MomLetters_SendOneOf(MOM_FIRST_OF_APRIL, 2, (u8) month, 1);
    }
    if (month == 12 && day == 24) {
        return MomLetters_SendOneOf(MOM_CHRISTMAS_EVE, 2, (u8) month, 1);
    }
    if (month == 6 && day == Calendar_NthWeekday((u8) date->year, (u8) month, SUNDAY, 3)) {
        return MomLetters_SendOneOf(MOM_FATHERS_DAY, 2, (u8) month, 1);
    }
    if (month == 5 && day == Calendar_NthWeekday((u8) date->year, (u8) month, SUNDAY, 2)) {
        return MomLetters_SendOneOf(MOM_MOTHERS_DAY, 2, (u8) month, 1);
    }
    return 0;
}
CLEAN_AS(func_0209737c, MomLetters_SendForDay)

/* func_02097430: the birthday letter, when the player has a birthday, none was sent this year
 * and the date is in the week from the birthday on (across the new year too); 0 when none was
 * sent. */
int MomLetters_SendBirthday(MomDate *date)
{
    void *player = PlayerRecords_Current();
    MomLetterState *state = PlayerRecord_MomLetterState(player);
    u8 *birthday = PlayerRecord_Birthday(player);
    if (birthday[0] == 0 && birthday[1] == 0) {
        return 0;
    }
    if (date->year == MomLetterState_BirthdayYear(state)) {
        return 0;
    }

    DateTime start = {0};
    start.year = (u8) date->year;
    start.month = birthday[1];
    start.day = birthday[0];
    DateTime today = {0};
    today.year = (u8) date->year;
    today.month = (u8) date->month;
    today.day = (u8) date->day;
    DateTime end = {0};
    MI_CpuCopy8(&start, &end, sizeof(DateTime));
    DateTime_AddDays(&end, BIRTHDAY_WEEK);

    int due;
    if (end.year != start.year) {
        /* The week runs into the next year: compare with its end as if in this year. */
        end.year = start.year;
        due = !(DateTime_Compare(&today, &end, DATE_TIME_YEAR | DATE_TIME_MONTH | DATE_TIME_DAY) == 1 &&
                DateTime_Compare(&today, &start, DATE_TIME_YEAR | DATE_TIME_MONTH | DATE_TIME_DAY) == -1);
    } else {
        due = !(DateTime_Compare(&today, &end, DATE_TIME_YEAR | DATE_TIME_MONTH | DATE_TIME_DAY) == 1 ||
                DateTime_Compare(&today, &start, DATE_TIME_YEAR | DATE_TIME_MONTH | DATE_TIME_DAY) == -1);
    }
    if (due) {
        due = MomLetters_SendOneOf(MOM_BIRTHDAY, 2, (u8) date->month, 1);
    }
    return due;
}
CLEAN_AS(func_02097430, MomLetters_SendBirthday)

/* func_0209751c: the day's update, `days` days on: unless the current player's mailbox and the
 * post office are both full, unmark the other months' letters and, once a day, send the
 * birthday letter, else the day's letter, else two times in ten one more (MomLetters_
 * SendSeasonalOrAlways); then note the day. On the first day only the day is noted. */
void MomLetters_DailyCheck(MomDate *date, int days)
{
    void *player = PlayerRecords_Current();
    if (player == NULL) {
        return;
    }
    if (days < 1) {
        return;
    }
    if (Mail_PostOfficeHasRoom() == 0 && Mail_IsMailboxFull(-1) == 1) {
        return;
    }
    MomLetterState *state = PlayerRecord_MomLetterState(player);
    MomLetters_UnmarkOtherMonths((u8) date->month);
    if (MomLetterState_IsDate(state, date) != 0) {
        return;
    }
    if (MomLetters_SendBirthday(date) != 0) {
        MomLetterState_SetBirthdayYear(state, (u8) date->year);
    } else if (MomLetters_SendForDay(date) == 0 && MainRandom_Below(10) < 2) {
        MomLetters_SendSeasonalOrAlways(date);
    }
    MomLetterState_SetDate(state, date);
}
CLEAN_AS(func_0209751c, MomLetters_DailyCheck)

/* func_0209761c: a paper for the season of `month`: winter (12, 1, 2 and 0), spring (3-5),
 * summer (6-8) or autumn (9 on), at random from that season's table. */
u8 MomLetters_PaperForMonth(u32 month)
{
    int season;
    if (month <= 2 || month == 12) {
        season = 3;
    } else if (month <= 5) {
        season = 0;
    } else if (month <= 8) {
        season = 1;
    } else {
        season = 2;
    }
    return data_020e3048[season][MainRandom_Below(data_020d18d0[season])];
}
CLEAN_AS(func_0209761c, MomLetters_PaperForMonth)

/* func_0209765c: a paper from paper set `set`, at random. */
u8 MomLetters_PaperFromSet(int set)
{
    u32 pick = MainRandom_Below(data_020d18e0[set]);
    return data_020e3058[set][pick];
}
CLEAN_AS(func_0209765c, MomLetters_PaperFromSet)

/* func_0209767c: three times in ten a paper of the season of `month`, else one of set `set`. */
int MomLetters_DrawPaper(int set, int month)
{
    if (MainRandom_Below(10) < 3) {
        return MomLetters_PaperForMonth((u32) month);
    }
    return MomLetters_PaperFromSet(set);
}
CLEAN_AS(func_0209767c, MomLetters_DrawPaper)

/* ---- The state in the player's record ---- */

/* func_02097cbc */
void MomLetterState_SetBirthdayYear(MomLetterState *state, u8 year)
{
    state->flags = (u8) (year | (state->flags & MOM_STATE_DATE_SET));
}
CLEAN_AS(func_02097cbc, MomLetterState_SetBirthdayYear)

/* func_02097cc8 */
u8 MomLetterState_BirthdayYear(MomLetterState *state)
{
    return state->flags & MOM_STATE_YEAR_MASK;
}
CLEAN_AS(func_02097cc8, MomLetterState_BirthdayYear)

/* func_02097cd4 */
int MomLetterState_IsSent(MomLetterState *state, int letter)
{
    return (sent_bits(state)[letter >> 3] & (1 << (letter & 7))) != 0;
}
CLEAN_AS(func_02097cd4, MomLetterState_IsSent)

/* func_02097cf8 */
void MomLetterState_Unmark(MomLetterState *state, int letter)
{
    sent_bits(state)[letter >> 3] &= (u8) ~(1 << (letter & 7));
}
CLEAN_AS(func_02097cf8, MomLetterState_Unmark)

/* func_02097d18 */
void MomLetterState_MarkSent(MomLetterState *state, int letter)
{
    sent_bits(state)[letter >> 3] |= (u8) (1 << (letter & 7));
}
CLEAN_AS(func_02097d18, MomLetterState_MarkSent)

/* func_02097d38: whether any of `flags` is set. */
int MomLetterState_TestFlags(MomLetterState *state, u32 flags)
{
    return (state->flags & flags) != 0;
}
CLEAN_AS(func_02097d38, MomLetterState_TestFlags)

/* func_02097d48 */
void MomLetterState_SetFlags(MomLetterState *state, int flags)
{
    state->flags = (u8) (state->flags | flags);
}
CLEAN_AS(func_02097d48, MomLetterState_SetFlags)

/* func_02097d50: the day last checked becomes `date`. */
void MomLetterState_SetDate(MomLetterState *state, const MomDate *date)
{
    state->year = (u8) date->year;
    state->month = (u8) date->month;
    state->day = (u8) date->day;
    MomLetterState_SetFlags(state, MOM_STATE_DATE_SET);
}
CLEAN_AS(func_02097d50, MomLetterState_SetDate)

/* func_02097d68: whether the day last checked is `date`. With no day kept yet, it becomes
 * `date` and the answer is 1. */
int MomLetterState_IsDate(MomLetterState *state, const MomDate *date)
{
    if (MomLetterState_TestFlags(state, MOM_STATE_DATE_SET) == 0) {
        MomLetterState_SetDate(state, date);
        return 1;
    }
    return state->year == date->year && state->month == date->month && state->day == date->day;
}
CLEAN_AS(func_02097d68, MomLetterState_IsDate)

/* func_02097dac: a new player's state: day 1/1/00 (not marked as set), no letter sent, and
 * MOM_STATE_NO_BIRTHDAY as the year of the last birthday letter. */
void MomLetterState_Init(MomLetterState *state)
{
    state->day = 1;
    state->month = 1;
    state->year = 0;
    for (int i = 0; i < MOM_STATE_SENT_BYTES; i++) {
        sent_bits(state)[i] = 0;
    }
    state->flags = MOM_STATE_NO_BIRTHDAY;
}
CLEAN_AS(func_02097dac, MomLetterState_Init)

/* func_02097dcc: the destructor (of a player record, func_02099ad0): nothing to do. */
void MomLetterState_Destruct(MomLetterState *state)
{
    (void) state;
}
CLEAN_AS(func_02097dcc, MomLetterState_Destruct)

/* func_02097dd0: the constructor (of a player record, func_02099bc8): nothing to do. */
void MomLetterState_Construct(MomLetterState *state)
{
    (void) state;
}
CLEAN_AS(func_02097dd0, MomLetterState_Construct)
