/* The day's plan (day_plan.h). */
#include "day_plan.h"

#include "autoload_2/approach.h"
#include "calendar.h"
#include "clean.h"
#include "nook_store.h"

#define DAY_PLAN_SUNDAY 0
#define DAY_PLAN_SATURDAY 6
/* The Nook's store level that bit 7 may be set for. */
#define DAY_PLAN_NIGHT_STORE_LEVEL 3

extern NookStore data_021f395c; /* the town's Nook's store */

extern u32 func_020644cc(int bound); /* a random number below `bound` */

static int day_plan_get(const u8 *plan, u8 mask, int shift)
{
    return (*plan & mask) >> shift;
}

static void day_plan_set(u8 *plan, u8 mask, int shift, u32 value)
{
    *plan = (u8) ((*plan & ~mask) | ((value << shift) & mask));
}

/* func_02086eb0 */
int DayPlan_Night(const u8 *plan)
{
    return day_plan_get(plan, DAY_PLAN_NIGHT_MASK, DAY_PLAN_NIGHT_SHIFT);
}
CLEAN_AS(func_02086eb0, DayPlan_Night)

/* func_02086ec4 */
int DayPlan_Afternoon(const u8 *plan)
{
    return day_plan_get(plan, DAY_PLAN_AFTERNOON_MASK, DAY_PLAN_AFTERNOON_SHIFT);
}
CLEAN_AS(func_02086ec4, DayPlan_Afternoon)

/* func_02086ecc */
int DayPlan_Noon(const u8 *plan)
{
    return day_plan_get(plan, DAY_PLAN_NOON_MASK, DAY_PLAN_NOON_SHIFT);
}
CLEAN_AS(func_02086ecc, DayPlan_Noon)

/* func_02086ed4 */
int DayPlan_Morning(const u8 *plan)
{
    return day_plan_get(plan, DAY_PLAN_MORNING_MASK, DAY_PLAN_MORNING_SHIFT);
}
CLEAN_AS(func_02086ed4, DayPlan_Morning)

/* func_02086ee8: a new plan. The morning bit is a coin toss and three numbers 0-99 are drawn,
 * x for noon, y for the afternoon and z for the night:
 *
 * - Saturday: noon 0 for x 0-74, 1 for 75-84, else 2; the afternoon the same from y;
 * - Sunday: noon 0 for x 0-49, 1 for 50-59, 2 for 60-70, else 4; the afternoon 0 for y 0-74,
 *   1 for 75-84, 2 for 85-94, else 3;
 * - other days: noon 0 for x 0-74, 1 for 75-85, else 2; the afternoon the same from y; the
 *   night bit set for z 0-29 when Nook's store is at level 3, else cleared.
 *
 * The night bit is set on Saturday and Sunday. An afternoon equal to the noon becomes 0. */
void DayPlan_Draw(u8 *plan)
{
    day_plan_set(plan, DAY_PLAN_MORNING_MASK, DAY_PLAN_MORNING_SHIFT, func_020644cc(2));
    day_plan_set(plan, DAY_PLAN_NIGHT_MASK, DAY_PLAN_NIGHT_SHIFT, 1);
    int x = (int) func_020644cc(100);
    int y = (int) func_020644cc(100);
    int z = (int) func_020644cc(100);
    u32 noon;
    u32 afternoon;
    switch (Calendar_TodayWeekday()) {
        case DAY_PLAN_SATURDAY:
            if (Math_IsBetween(x, 0, 74)) {
                noon = 0;
            } else if (Math_IsBetween(x, 75, 84)) {
                noon = 1;
            } else {
                noon = 2;
            }
            day_plan_set(plan, DAY_PLAN_NOON_MASK, DAY_PLAN_NOON_SHIFT, noon);
            if (Math_IsBetween(y, 0, 74)) {
                afternoon = 0;
            } else if (Math_IsBetween(y, 75, 84)) {
                afternoon = 1;
            } else {
                afternoon = 2;
            }
            day_plan_set(plan, DAY_PLAN_AFTERNOON_MASK, DAY_PLAN_AFTERNOON_SHIFT, afternoon);
            break;
        case DAY_PLAN_SUNDAY:
            if (Math_IsBetween(x, 0, 49)) {
                noon = 0;
            } else if (Math_IsBetween(x, 50, 59)) {
                noon = 1;
            } else if (Math_IsBetween(x, 60, 70)) {
                noon = 2;
            } else {
                noon = 4;
            }
            day_plan_set(plan, DAY_PLAN_NOON_MASK, DAY_PLAN_NOON_SHIFT, noon);
            if (Math_IsBetween(y, 0, 74)) {
                afternoon = 0;
            } else if (Math_IsBetween(y, 75, 84)) {
                afternoon = 1;
            } else if (Math_IsBetween(y, 85, 94)) {
                afternoon = 2;
            } else {
                afternoon = 3;
            }
            day_plan_set(plan, DAY_PLAN_AFTERNOON_MASK, DAY_PLAN_AFTERNOON_SHIFT, afternoon);
            break;
        default:
            if (Math_IsBetween(x, 0, 74)) {
                noon = 0;
            } else if (Math_IsBetween(x, 75, 85)) {
                noon = 1;
            } else {
                noon = 2;
            }
            day_plan_set(plan, DAY_PLAN_NOON_MASK, DAY_PLAN_NOON_SHIFT, noon);
            if (Math_IsBetween(y, 0, 74)) {
                afternoon = 0;
            } else if (Math_IsBetween(y, 75, 85)) {
                afternoon = 1;
            } else {
                afternoon = 2;
            }
            day_plan_set(plan, DAY_PLAN_AFTERNOON_MASK, DAY_PLAN_AFTERNOON_SHIFT, afternoon);
            if (Math_IsBetween(z, 0, 29) && NookStore_Level(&data_021f395c) == DAY_PLAN_NIGHT_STORE_LEVEL) {
                day_plan_set(plan, DAY_PLAN_NIGHT_MASK, DAY_PLAN_NIGHT_SHIFT, 1);
            } else {
                day_plan_set(plan, DAY_PLAN_NIGHT_MASK, DAY_PLAN_NIGHT_SHIFT, 0);
            }
            break;
    }
    if (DayPlan_Noon(plan) == DayPlan_Afternoon(plan)) {
        day_plan_set(plan, DAY_PLAN_AFTERNOON_MASK, DAY_PLAN_AFTERNOON_SHIFT, 0);
    }
}
CLEAN_AS(func_02086ee8, DayPlan_Draw)

/* func_02087138: the town's setting up draws the first plan. */
void DayPlan_SetUp(u8 *plan)
{
    DayPlan_Draw(plan);
}
CLEAN_AS(func_02087138, DayPlan_SetUp)

/* func_02087140 */
void DayPlan_Clear(u8 *plan)
{
    *plan = 0;
}
CLEAN_AS(func_02087140, DayPlan_Clear)

/* func_02087164: the destructor does nothing. */
void DayPlan_Destruct(u8 *plan)
{
    (void) plan;
}
CLEAN_AS(func_02087164, DayPlan_Destruct)

/* func_02087168: the constructor does nothing. */
void DayPlan_Construct(u8 *plan)
{
    (void) plan;
}
CLEAN_AS(func_02087168, DayPlan_Construct)
