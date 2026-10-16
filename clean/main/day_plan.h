/* The day's plan: one byte of the state block (0xf52b) drawn at random each day
 * (DayPlan_Draw, from the town's setting up and its daily update) and read by overlay 68 at
 * set times of the day:
 *
 * - bit 0: something at 6:00-6:54;
 * - bits 1-3: one of 0-4 at 12:00-13:29;
 * - bits 4-6: one of 0-3 at 14:30-15:59 (never the same as bits 1-3 unless both are 0);
 * - bit 7: something at 23:00-23:59 on weekdays, when Nook's store is at level 3.
 *
 * The weekday (Saturday, Sunday or another) sets the odds of each value. */
#ifndef CLEAN_MAIN_DAY_PLAN_H
#define CLEAN_MAIN_DAY_PLAN_H

#include "types.h"

#define DAY_PLAN_MORNING_SHIFT 0
#define DAY_PLAN_MORNING_MASK 0x01
#define DAY_PLAN_NOON_SHIFT 1
#define DAY_PLAN_NOON_MASK 0x0e
#define DAY_PLAN_AFTERNOON_SHIFT 4
#define DAY_PLAN_AFTERNOON_MASK 0x70
#define DAY_PLAN_NIGHT_SHIFT 7
#define DAY_PLAN_NIGHT_MASK 0x80

int DayPlan_Night(const u8 *plan);
int DayPlan_Afternoon(const u8 *plan);
int DayPlan_Noon(const u8 *plan);
int DayPlan_Morning(const u8 *plan);
void DayPlan_Draw(u8 *plan);
void DayPlan_SetUp(u8 *plan);
void DayPlan_Clear(u8 *plan);
void DayPlan_Destruct(u8 *plan);
void DayPlan_Construct(u8 *plan);

#endif
