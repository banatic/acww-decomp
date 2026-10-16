/* What the room score (room_score.h) keeps between its judgements: the date the house's rooms
 * were last judged, a Date in the state block (at 0x173c8, data_021f3b70), and the
 * destructors of its tables, which have nothing to do.
 *
 * The game's day starts at 6:00: before that hour the date judged is the day before. The
 * letters about the rooms are sent once a week: when the last judgement was before the Sunday
 * that starts the clock's week (RoomScoreState_WeekPassed). */
#ifndef CLEAN_MAIN_ROOM_SCORE_STATE_H
#define CLEAN_MAIN_ROOM_SCORE_STATE_H

#include "calendar.h"
#include "types.h"

void RoomScoreState_SetJudgeDate(Date *date);
int RoomScoreState_WeekPassed(Date *date);
void RoomScoreState_ResetJudgeDate(Date *date);
void RoomScoreState_SetClockDate(Date *date);
void RoomScoreState_DestructJudgeDate(void *date);
void RoomScoreState_ConstructJudgeDate(void *date);
void RoomScoreState_DestructCategories(void *categories);
void RoomScoreState_DestructMarks(void *marks);
void RoomScoreState_DestructBest(void *best);

#endif
