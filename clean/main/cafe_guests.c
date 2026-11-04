/* The cafe's guests of the day (cafe_guests.h). */
#include "cafe_guests.h"

#include "autoload_2/approach.h"
#include "calendar.h"
#include "clean.h"
#include "nook_store.h"
#include "main_random.h"

#define CAFE_GUESTS_SUNDAY 0
#define CAFE_GUESTS_SATURDAY 6
/* The Nook's store level that bit 7 may be set for. */
#define CAFE_GUESTS_NIGHT_STORE_LEVEL 3

extern NookStore data_021f395c; /* the town's Nook's store */

static int cafe_guests_get(const u8 *plan, u8 mask, int shift)
{
    return (*plan & mask) >> shift;
}

static void cafe_guests_set(u8 *plan, u8 mask, int shift, u32 value)
{
    *plan = (u8) ((*plan & ~mask) | ((value << shift) & mask));
}

/* func_02086eb0 */
int CafeGuests_Night(const u8 *plan)
{
    return cafe_guests_get(plan, CAFE_GUESTS_NIGHT_MASK, CAFE_GUESTS_NIGHT_SHIFT);
}
CLEAN_AS(func_02086eb0, CafeGuests_Night)

/* func_02086ec4 */
int CafeGuests_Afternoon(const u8 *plan)
{
    return cafe_guests_get(plan, CAFE_GUESTS_AFTERNOON_MASK, CAFE_GUESTS_AFTERNOON_SHIFT);
}
CLEAN_AS(func_02086ec4, CafeGuests_Afternoon)

/* func_02086ecc */
int CafeGuests_Noon(const u8 *plan)
{
    return cafe_guests_get(plan, CAFE_GUESTS_NOON_MASK, CAFE_GUESTS_NOON_SHIFT);
}
CLEAN_AS(func_02086ecc, CafeGuests_Noon)

/* func_02086ed4 */
int CafeGuests_Morning(const u8 *plan)
{
    return cafe_guests_get(plan, CAFE_GUESTS_MORNING_MASK, CAFE_GUESTS_MORNING_SHIFT);
}
CLEAN_AS(func_02086ed4, CafeGuests_Morning)

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
void CafeGuests_Draw(u8 *plan)
{
    cafe_guests_set(plan, CAFE_GUESTS_MORNING_MASK, CAFE_GUESTS_MORNING_SHIFT, MainRandom_Below(2));
    cafe_guests_set(plan, CAFE_GUESTS_NIGHT_MASK, CAFE_GUESTS_NIGHT_SHIFT, 1);
    int x = (int) MainRandom_Below(100);
    int y = (int) MainRandom_Below(100);
    int z = (int) MainRandom_Below(100);
    u32 noon;
    u32 afternoon;
    switch (Calendar_TodayWeekday()) {
        case CAFE_GUESTS_SATURDAY:
            if (Math_IsBetween(x, 0, 74)) {
                noon = 0;
            } else if (Math_IsBetween(x, 75, 84)) {
                noon = 1;
            } else {
                noon = 2;
            }
            cafe_guests_set(plan, CAFE_GUESTS_NOON_MASK, CAFE_GUESTS_NOON_SHIFT, noon);
            if (Math_IsBetween(y, 0, 74)) {
                afternoon = 0;
            } else if (Math_IsBetween(y, 75, 84)) {
                afternoon = 1;
            } else {
                afternoon = 2;
            }
            cafe_guests_set(plan, CAFE_GUESTS_AFTERNOON_MASK, CAFE_GUESTS_AFTERNOON_SHIFT, afternoon);
            break;
        case CAFE_GUESTS_SUNDAY:
            if (Math_IsBetween(x, 0, 49)) {
                noon = 0;
            } else if (Math_IsBetween(x, 50, 59)) {
                noon = 1;
            } else if (Math_IsBetween(x, 60, 70)) {
                noon = 2;
            } else {
                noon = 4;
            }
            cafe_guests_set(plan, CAFE_GUESTS_NOON_MASK, CAFE_GUESTS_NOON_SHIFT, noon);
            if (Math_IsBetween(y, 0, 74)) {
                afternoon = 0;
            } else if (Math_IsBetween(y, 75, 84)) {
                afternoon = 1;
            } else if (Math_IsBetween(y, 85, 94)) {
                afternoon = 2;
            } else {
                afternoon = 3;
            }
            cafe_guests_set(plan, CAFE_GUESTS_AFTERNOON_MASK, CAFE_GUESTS_AFTERNOON_SHIFT, afternoon);
            break;
        default:
            if (Math_IsBetween(x, 0, 74)) {
                noon = 0;
            } else if (Math_IsBetween(x, 75, 85)) {
                noon = 1;
            } else {
                noon = 2;
            }
            cafe_guests_set(plan, CAFE_GUESTS_NOON_MASK, CAFE_GUESTS_NOON_SHIFT, noon);
            if (Math_IsBetween(y, 0, 74)) {
                afternoon = 0;
            } else if (Math_IsBetween(y, 75, 85)) {
                afternoon = 1;
            } else {
                afternoon = 2;
            }
            cafe_guests_set(plan, CAFE_GUESTS_AFTERNOON_MASK, CAFE_GUESTS_AFTERNOON_SHIFT, afternoon);
            if (Math_IsBetween(z, 0, 29) && NookStore_Level(&data_021f395c) == CAFE_GUESTS_NIGHT_STORE_LEVEL) {
                cafe_guests_set(plan, CAFE_GUESTS_NIGHT_MASK, CAFE_GUESTS_NIGHT_SHIFT, 1);
            } else {
                cafe_guests_set(plan, CAFE_GUESTS_NIGHT_MASK, CAFE_GUESTS_NIGHT_SHIFT, 0);
            }
            break;
    }
    if (CafeGuests_Noon(plan) == CafeGuests_Afternoon(plan)) {
        cafe_guests_set(plan, CAFE_GUESTS_AFTERNOON_MASK, CAFE_GUESTS_AFTERNOON_SHIFT, 0);
    }
}
CLEAN_AS(func_02086ee8, CafeGuests_Draw)

/* func_02087138: the town's setting up draws the first plan. */
void CafeGuests_SetUp(u8 *plan)
{
    CafeGuests_Draw(plan);
}
CLEAN_AS(func_02087138, CafeGuests_SetUp)

/* func_02087140 */
void CafeGuests_Clear(u8 *plan)
{
    *plan = 0;
}
CLEAN_AS(func_02087140, CafeGuests_Clear)

/* func_02087164: the destructor does nothing. */
void CafeGuests_Destruct(u8 *plan)
{
    (void) plan;
}
CLEAN_AS(func_02087164, CafeGuests_Destruct)

/* func_02087168: the constructor does nothing. */
void CafeGuests_Construct(u8 *plan)
{
    (void) plan;
}
CLEAN_AS(func_02087168, CafeGuests_Construct)
