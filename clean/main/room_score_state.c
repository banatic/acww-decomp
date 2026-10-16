/* What the room score keeps between its judgements (room_score_state.h). */
#include "room_score_state.h"

#include "clean.h"
#include "date_time.h"

/* The hour the game's day starts at, and the hour a judged date stands for. */
#define ROOM_SCORE_STATE_DAY_START 6
#define ROOM_SCORE_STATE_JUDGE_HOUR 7
#define ROOM_SCORE_STATE_DATE_FIELDS (DATE_TIME_DAY | DATE_TIME_MONTH | DATE_TIME_YEAR)
#define ROOM_SCORE_STATE_WEEK 7

/* func_0205be64: the date set to the game's day: the clock's date, or the day before when the
 * hour is before 6:00. Its unused byte is left as it is. */
void RoomScoreState_SetJudgeDate(Date *date)
{
    DateTime now = {0};
    DateTime_Now(&now);
    if (now.hour < ROOM_SCORE_STATE_DAY_START) {
        DateTime_SubtractDays(&now, 1);
    }
    date->day = now.day;
    date->month = now.month;
    date->year = now.year;
}
CLEAN_AS(func_0205be64, RoomScoreState_SetJudgeDate)

/* func_0205be9c: whether a week has passed since `date`: whether it is before the Sunday that
 * starts the clock's week, and that Sunday is not after the game's day.
 * When `date` is after the game's day (the clock was set back), it is set to the game's day
 * and the answer is no.
 * QUIRK: the week's Sunday is counted from the clock's date, not from the game's day. When it
 * falls in a later year than the game's day (on a Sunday the 1st of January before 6:00), it
 * is moved a week on, and the answer is no.
 * QUIRK: the last comparison is made twice. */
int RoomScoreState_WeekPassed(Date *date)
{
    DateTime today = {0};
    DateTime_Now(&today);
    if (today.hour < ROOM_SCORE_STATE_DAY_START) {
        today.hour = ROOM_SCORE_STATE_JUDGE_HOUR;
        DateTime_SubtractDays(&today, 1);
    }

    DateTime sunday = {0};
    DateTime_Now(&sunday);
    int weekday = Calendar_Weekday(sunday.year, sunday.month, sunday.day);
    DateTime_SubtractDays(&sunday, weekday);
    if (sunday.year > today.year) {
        DateTime_AddDays(&sunday, ROOM_SCORE_STATE_WEEK);
    }

    DateTime judged = {0};
    judged.year = date->year;
    judged.month = date->month;
    judged.day = date->day;
    judged.hour = ROOM_SCORE_STATE_JUDGE_HOUR;

    if (DateTime_Compare(&today, &judged, ROOM_SCORE_STATE_DATE_FIELDS) == -1) {
        date->year = today.year;
        date->month = today.month;
        date->day = today.day;
        return 0;
    }
    if (DateTime_Compare(&judged, &sunday, ROOM_SCORE_STATE_DATE_FIELDS) != -1) {
        return 0;
    }
    if (DateTime_Compare(&sunday, &today, ROOM_SCORE_STATE_DATE_FIELDS) == -1) {
        return 1;
    }
    return DateTime_Compare(&sunday, &today, ROOM_SCORE_STATE_DATE_FIELDS) == 0;
}
CLEAN_AS(func_0205be9c, RoomScoreState_WeekPassed)

/* func_0205bf88: the town's set-up (StateBlock_SetUpTown): the date set to the clock's. */
void RoomScoreState_ResetJudgeDate(Date *date)
{
    RoomScoreState_SetClockDate(date);
}
CLEAN_AS(func_0205bf88, RoomScoreState_ResetJudgeDate)

/* func_0205bf90: the date set to the clock's (whatever the hour), its unused byte cleared. */
void RoomScoreState_SetClockDate(Date *date)
{
    DateTime now = {0};
    DateTime_Now(&now);
    date->day = now.day;
    date->month = now.month;
    date->year = now.year;
    date->unused = 0;
}
CLEAN_AS(func_0205bf90, RoomScoreState_SetClockDate)

/* func_0205bfbc: the date's destructor: nothing to do. */
void RoomScoreState_DestructJudgeDate(void *date)
{
    (void) date;
}
CLEAN_AS(func_0205bfbc, RoomScoreState_DestructJudgeDate)

/* func_0205bfc0: the date's constructor (__sinit_020c64e8): nothing to do. */
void RoomScoreState_ConstructJudgeDate(void *date)
{
    (void) date;
}
CLEAN_AS(func_0205bfc0, RoomScoreState_ConstructJudgeDate)

/* func_0205bfc4: the destructor of the groups' categories (data_021c997c), registered by
 * __sinit_020c5788: nothing to do. */
void RoomScoreState_DestructCategories(void *categories)
{
    (void) categories;
}
CLEAN_AS(func_0205bfc4, RoomScoreState_DestructCategories)

/* func_0205bfc8: the destructor of the special items' marks (data_021c9774): nothing to do. */
void RoomScoreState_DestructMarks(void *marks)
{
    (void) marks;
}
CLEAN_AS(func_0205bfc8, RoomScoreState_DestructMarks)

/* func_0205bfcc: the destructor of the groups' best scores (data_021c9854): nothing to do. */
void RoomScoreState_DestructBest(void *best)
{
    (void) best;
}
CLEAN_AS(func_0205bfcc, RoomScoreState_DestructBest)
