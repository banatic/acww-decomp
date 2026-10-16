/* The letters from the player's mother, written from the templates "mother_day" (letters
 * 0x00-0x21, for days of the year), "mother_always" (0x22-0x59, any time) and "mother_season"
 * (0x5a on, a few for each month).
 *
 * On each new day (MomLetters_DailyCheck) the mother writes for the player's birthday (letter
 * 0x20 or 0x21, in the week from the birthday on, once a year), else for a day of the year
 * (MomLetters_SendForDay), else two days in ten a letter of the month or one of the others
 * (MomLetters_SendSeasonalOrAlways). Each letter goes into the player's mailbox, else waits at
 * the post office (mail.h); some carry a present (MomLetters_Present).
 *
 * The player's record keeps, at 0x243e (MomLetterState), the day it last checked, the year of
 * the last birthday letter and a bit for each letter sent; within a group the letters are drawn
 * among those not sent yet. */
#ifndef CLEAN_MAIN_MOM_LETTERS_H
#define CLEAN_MAIN_MOM_LETTERS_H

#include "types.h"

/* The groups of letters. */
#define MOM_DAY_FIRST 0x00
#define MOM_ALWAYS_FIRST 0x22
#define MOM_ALWAYS_COUNT 0x38
#define MOM_SEASON_FIRST 0x5a

/* The day's letters: two for each day N/N (MOM_DAY_FIRST + 2 * (N - 1)) and these. */
#define MOM_MOTHERS_DAY 0x18 /* the second Sunday of May */
#define MOM_FATHERS_DAY 0x1a /* the third Sunday of June */
#define MOM_FIRST_OF_APRIL 0x1c
#define MOM_CHRISTMAS_EVE 0x1e /* 12/24 */
#define MOM_BIRTHDAY 0x20

/* A date as the day's update hands it over. */
typedef struct MomDate {
    u32 year; /* 0-99 */
    u32 month;
    u32 day;
} MomDate;

/* What a player's record keeps at 0x243e. */
typedef struct MomLetterState {
    u8 day; /* the day last checked, valid with MOM_STATE_DATE_SET */
    u8 month;
    u8 year;
    u8 flags;   /* MOM_STATE_DATE_SET, and in the low seven bits the year of the last birthday letter */
    u8 sent[1]; /* a bit for each letter sent (letter n: byte n / 8, bit n % 8), on past the struct */
} MomLetterState;

#define MOM_STATE_DATE_SET 0x80
#define MOM_STATE_YEAR_MASK 0x7f

u8 MomLetters_GroupIndex(int letter);
int MomLetters_Present(int letter);
const char *MomLetters_Template(int letter);
int MomLetters_Send(int letter, int month);
int MomLetters_SendOneOf(int first, int count, int month, int recycle);
void MomLetters_Unmark(int first, int count);
int MomLetters_NthUnsent(int first, int count, int n);
int MomLetters_CountUnsent(int first, int count);
void MomLetters_UnmarkOtherMonths(int month);
u8 MomLetters_SeasonCount(u32 month);
int MomLetters_SeasonFirst(int month);
int MomLetters_SendSeasonalOrAlways(MomDate *date);
int MomLetters_SendForDay(MomDate *date);
int MomLetters_SendBirthday(MomDate *date);
void MomLetters_DailyCheck(MomDate *date, int days);
u8 MomLetters_PaperForMonth(u32 month);
u8 MomLetters_PaperFromSet(int set);
int MomLetters_DrawPaper(int set, int month);

void MomLetterState_SetBirthdayYear(MomLetterState *state, u8 year);
u8 MomLetterState_BirthdayYear(MomLetterState *state);
int MomLetterState_IsSent(MomLetterState *state, int letter);
void MomLetterState_Unmark(MomLetterState *state, int letter);
void MomLetterState_MarkSent(MomLetterState *state, int letter);
int MomLetterState_TestFlags(MomLetterState *state, u32 flags);
void MomLetterState_SetFlags(MomLetterState *state, int flags);

#endif
