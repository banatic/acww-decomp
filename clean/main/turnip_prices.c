/* The week's turnip prices (turnip_prices.h). */
#include "turnip_prices.h"

#include "clean.h"
#include "date_time.h"
#include "state_block.h"
#include "main_random.h"
#include "state_flags.h"

static_assert(offsetof(TurnipPrices, peak) == 0x08 && offsetof(TurnipPrices, prices) == 0x0a, "TurnipPrices");
static_assert(offsetof(TurnipPrices, pattern) == 0x18 && sizeof(TurnipPrices) == 0x1a, "TurnipPrices");

/* The game's day starts at 6:00. */
#define TURNIP_DAY_START_HOUR 6
#define TURNIP_NOON 12
#define TURNIP_WEEK_DAYS 7
/* Flag 4 of the state block (see turnip_prices.h). */
#define TURNIP_BOUGHT_FLAG 4

/* The Sunday price: 90 plus 0-20. */
#define TURNIP_BUY_BASE 90
#define TURNIP_BUY_SPREAD 21
/* The odds of the next pattern: a number 0-100. */
#define TURNIP_PATTERN_ODDS 101
#define TURNIP_PATTERNS 4

/* The shares of the Sunday price, in 4.12 fixed point: the lowest share and the spread drawn
 * on top of it. */
#define TURNIP_HIGH_SHARE 0x0ccd /* 0.8-1.4 */
#define TURNIP_HIGH_SPREAD 0x09c3
#define TURNIP_MID_SHARE 0x1666 /* 1.4-2.0 */
#define TURNIP_MID_SPREAD 0x09c3
#define TURNIP_LOW_SHARE 0x0666 /* 0.4-0.8 */
#define TURNIP_LOW_SPREAD 0x068f
#define TURNIP_PEAK_SHARE 0x2000 /* 2.0-6.1 */
#define TURNIP_PEAK_SPREAD 0x419a
#define TURNIP_SMALL_PEAK_SHARE 0x1b33 /* 1.7-2.0 */
#define TURNIP_SMALL_PEAK_SPREAD 0x04f6
#define TURNIP_SMALL_SIDE_SHARE 0x168f /* 1.4-1.7 */
#define TURNIP_SMALL_SIDE_SPREAD 0x04a4
#define TURNIP_FALLING_SHARE 0x0ca4 /* 0.79, less 0.025 each half day */
#define TURNIP_FALLING_STEP 0x0066
#define TURNIP_FALLING_SPREAD 0x0029

/* The first half day of the week's selling prices (Monday morning). */
#define TURNIP_FIRST_SALE 2
/* The big spike's peak: half day 8-11 (Thursday morning to Friday afternoon). */
#define TURNIP_BIG_PEAK_FIRST 8
#define TURNIP_BIG_PEAK_CHOICES 4
/* The small spike's peak: half day 7-12. */
#define TURNIP_SMALL_PEAK_FIRST 7
#define TURNIP_SMALL_PEAK_CHOICES 6

extern u32 data_021dc7a8[]; /* the state block */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* Whether a date is 1 January 2000, the clock's first day: there is no day before it. */
static int turnip_is_first_day(const DateTime *when)
{
    return when->year == 0 && when->month == 1 && when->day == 1;
}

/* The game day of `when` with its time at 6:00 when it was moved back. */
static void turnip_game_day_start(DateTime *when)
{
    if (!turnip_is_first_day(when) && when->hour < TURNIP_DAY_START_HOUR) {
        DateTime_SubtractDays(when, 1);
        when->hour = TURNIP_DAY_START_HOUR;
        when->minute = 0;
        when->second = 0;
    }
}

/* The game day of `when` (now when NULL) into `date`.
 * QUIRK: before 6:00 on 1 January 2000 the day stays the same. */
static void turnip_set_game_day(Date *date, const DateTime *when)
{
    DateTime day = {0};
    if (when == NULL) {
        DateTime_Now(&day);
    } else {
        MI_CpuCopy8(when, &day, sizeof(day));
    }
    if (!turnip_is_first_day(&day) && day.hour < TURNIP_DAY_START_HOUR) {
        DateTime_SubtractDays(&day, 1);
    }
    date->year = day.year;
    date->month = day.month;
    date->day = day.day;
}

/* func_02087274: `bought` set to the game day of `when`, or of now when it is NULL. */
void TurnipPrices_SetBought(TurnipPrices *prices, const DateTime *when)
{
    turnip_set_game_day(&prices->bought, when);
}
CLEAN_AS(func_02087274, TurnipPrices_SetBought)

/* func_020872d0: a week or more after `bought` (by game days), flag 4 of the state block is
 * cleared and `bought` set to today. */
void TurnipPrices_ExpireBought(TurnipPrices *prices)
{
    DateTime bought;
    DateTime_Set(&bought, &prices->bought, TURNIP_DAY_START_HOUR, 0, 0);
    DateTime now = {0};
    DateTime_Now(&now);
    turnip_game_day_start(&now);
    if (DateTime_Compare(&now, &bought, DATE_TIME_DAY | DATE_TIME_MONTH | DATE_TIME_YEAR) == 1 &&
        DateTime_DaysBetween(&bought, &now) >= TURNIP_WEEK_DAYS) {
        StateBlock_ClearFlag(data_021dc7a8, TURNIP_BOUGHT_FLAG);
        TurnipPrices_SetBought(prices, &now);
    }
}
CLEAN_AS(func_020872d0, TurnipPrices_ExpireBought)

/* func_02087358: `week` set to the game day of `when`, or of now when it is NULL. */
void TurnipPrices_SetWeek(TurnipPrices *prices, const DateTime *when)
{
    turnip_set_game_day(&prices->week, when);
}
CLEAN_AS(func_02087358, TurnipPrices_SetWeek)

/* func_020873b4: brought up to date (by game days), after TurnipPrices_ExpireBought: a new
 * week (today's weekday before the week's day's, or 7 days or more later) has new prices; a
 * clock moved back before the week's day gets falling prices and both dates set to today.
 * `unused` is not read. */
void TurnipPrices_Update(TurnipPrices *prices, int unused)
{
    (void) unused;
    DateTime week;
    DateTime_Set(&week, &prices->week, TURNIP_DAY_START_HOUR, 0, 0);
    DateTime now = {0};
    DateTime_Now(&now);
    turnip_game_day_start(&now);
    int order = DateTime_Compare(&now, &week, DATE_TIME_DAY | DATE_TIME_MONTH | DATE_TIME_YEAR);
    TurnipPrices_ExpireBought(prices);
    if (order == 1) {
        int week_weekday = Calendar_Weekday(week.year, week.month, week.day);
        int weekday = Calendar_Weekday(now.year, now.month, now.day);
        if (weekday < week_weekday || DateTime_DaysBetween(&week, &now) >= TURNIP_WEEK_DAYS) {
            TurnipPrices_Draw(prices, 0);
            TurnipPrices_SetWeek(prices, &now);
        }
    } else if (order == -1) {
        TurnipPrices_Draw(prices, 1);
        TurnipPrices_SetWeek(prices, &now);
        TurnipPrices_SetBought(prices, &now);
    }
}
CLEAN_AS(func_020873b4, TurnipPrices_Update)

/* func_02087480: when the clock was moved (global flag 0x20 or 0x08), falling prices and both
 * dates set to today. */
void TurnipPrices_RedrawIfClockMoved(TurnipPrices *prices)
{
    if (StateFlags_Test20() != 0 || StateFlags_Test8() != 0) {
        DateTime now = {0};
        DateTime_Now(&now);
        TurnipPrices_Draw(prices, 1);
        TurnipPrices_SetWeek(prices, &now);
        TurnipPrices_SetBought(prices, &now);
    }
}
CLEAN_AS(func_02087480, TurnipPrices_RedrawIfClockMoved)

/* func_020874c4: the price of this half day (by the calendar's day, not the game's): the
 * peak where the price is 0. */
int TurnipPrices_Current(TurnipPrices *prices)
{
    DateTime now = {0};
    DateTime_Now(&now);
    int afternoon = now.hour >= TURNIP_NOON ? 1 : 0;
    int index = Calendar_TodayWeekday() * 2 + afternoon;
    u8 price = prices->prices[index];
    if (price != 0) {
        return price;
    }
    return prices->peak;
}
CLEAN_AS(func_020874c4, TurnipPrices_Current)

/* func_02087500: the week's prices drawn. The pattern follows from the last one with a number
 * 0-100 (random: 0-29 big spike, 30-64 small spike, 65-79 falling; big spike: 0-19 small spike,
 * 20-64 random, 65-84 falling; falling: 0-44 big spike, 45-69 small spike, 70-94 random; small
 * spike: 0-24 big spike, 25-69 random, 70-84 falling; else the same), or is forced to falling;
 * the first one is drawn 0-3. */
void TurnipPrices_Draw(TurnipPrices *prices, int falling)
{
    if (prices->pattern != TURNIP_PATTERN_NONE) {
        int odds = (int) MainRandom_Below(TURNIP_PATTERN_ODDS);
        switch (prices->pattern) {
            case TURNIP_PATTERN_RANDOM:
                if (odds < 30) {
                    prices->pattern = TURNIP_PATTERN_BIG_SPIKE;
                } else if (odds < 65) {
                    prices->pattern = TURNIP_PATTERN_SMALL_SPIKE;
                } else if (odds < 80) {
                    prices->pattern = TURNIP_PATTERN_FALLING;
                }
                break;
            case TURNIP_PATTERN_BIG_SPIKE:
                if (odds < 20) {
                    prices->pattern = TURNIP_PATTERN_SMALL_SPIKE;
                } else if (odds < 65) {
                    prices->pattern = TURNIP_PATTERN_RANDOM;
                } else if (odds < 85) {
                    prices->pattern = TURNIP_PATTERN_FALLING;
                }
                break;
            case TURNIP_PATTERN_FALLING:
                if (odds < 45) {
                    prices->pattern = TURNIP_PATTERN_BIG_SPIKE;
                } else if (odds < 70) {
                    prices->pattern = TURNIP_PATTERN_SMALL_SPIKE;
                } else if (odds < 95) {
                    prices->pattern = TURNIP_PATTERN_RANDOM;
                }
                break;
            case TURNIP_PATTERN_SMALL_SPIKE:
                if (odds < 25) {
                    prices->pattern = TURNIP_PATTERN_BIG_SPIKE;
                } else if (odds < 70) {
                    prices->pattern = TURNIP_PATTERN_RANDOM;
                } else if (odds < 85) {
                    prices->pattern = TURNIP_PATTERN_FALLING;
                }
                break;
            default:
                break;
        }
        if (falling) {
            prices->pattern = TURNIP_PATTERN_FALLING;
        }
    } else {
        prices->pattern = (u8) MainRandom_Below(TURNIP_PATTERNS);
    }

    prices->peak = 0;
    MI_CpuFill8(prices->prices, 0, sizeof(prices->prices));
    prices->prices[0] = (u8) (MainRandom_Below(TURNIP_BUY_SPREAD) + TURNIP_BUY_BASE);
    prices->prices[1] = prices->prices[0];

    u8 *p = prices->prices;
    switch (prices->pattern) {
        case TURNIP_PATTERN_RANDOM:
            p[2] = (u8) TurnipPrices_DrawHigh(prices);
            p[3] = (u8) TurnipPrices_DrawLow(prices);
            p[4] = (u8) TurnipPrices_DrawLow(prices);
            p[5] = (u8) TurnipPrices_DrawLow(prices);
            p[6] = (u8) TurnipPrices_DrawHigh(prices);
            p[7] = (u8) TurnipPrices_DrawHigh(prices);
            p[8] = (u8) TurnipPrices_DrawHigh(prices);
            p[9] = (u8) TurnipPrices_DrawLow(prices);
            p[10] = (u8) TurnipPrices_DrawLow(prices);
            p[11] = (u8) TurnipPrices_DrawHigh(prices);
            p[12] = (u8) TurnipPrices_DrawHigh(prices);
            p[13] = (u8) TurnipPrices_DrawHigh(prices);
            break;
        case TURNIP_PATTERN_BIG_SPIKE: {
            int peak = (int) MainRandom_Below(TURNIP_BIG_PEAK_CHOICES) + TURNIP_BIG_PEAK_FIRST;
            p[peak] = (u8) TurnipPrices_DrawPeak(prices);
            TurnipPrices_DrawFalling(prices, TURNIP_FIRST_SALE, peak - 2);
            p[peak - 1] = (u8) TurnipPrices_DrawMid(prices);
            p[peak + 1] = (u8) TurnipPrices_DrawMid(prices);
            p[peak - 2] = (u8) TurnipPrices_DrawHigh(prices);
            p[peak + 2] = (u8) TurnipPrices_DrawHigh(prices);
            TurnipPrices_DrawFalling(prices, peak + 3, TURNIP_PRICES_HALF_DAYS);
            break;
        }
        case TURNIP_PATTERN_FALLING:
            TurnipPrices_DrawFalling(prices, TURNIP_FIRST_SALE, TURNIP_PRICES_HALF_DAYS);
            break;
        case TURNIP_PATTERN_SMALL_SPIKE:
            TurnipPrices_DrawSmallSpike(prices);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_02087500, TurnipPrices_Draw)

/* func_020876c8: the big spike's peak, 2.0-6.1 times the Sunday price, into `peak`; its price
 * slot gets 0.
 * QUIRK: the peak is cut to 16 bits, which it never fills. */
int TurnipPrices_DrawPeak(TurnipPrices *prices)
{
    int share = (int) MainRandom_BelowB(TURNIP_PEAK_SPREAD) + TURNIP_PEAK_SHARE;
    prices->peak = (u16) ((prices->prices[0] * share) >> 12);
    return 0;
}
CLEAN_AS(func_020876c8, TurnipPrices_DrawPeak)

/* func_020876f0: the small spike: its peak on half day 7-12; falling before the two highs that
 * lead to it, the peak between two of 1.4-1.7, falling after. */
void TurnipPrices_DrawSmallSpike(TurnipPrices *prices)
{
    u8 *p = prices->prices;
    int peak = (int) MainRandom_Below(TURNIP_SMALL_PEAK_CHOICES) + TURNIP_SMALL_PEAK_FIRST;
    TurnipPrices_DrawFalling(prices, TURNIP_FIRST_SALE, peak - 3);
    p[peak - 3] = (u8) TurnipPrices_DrawHigh(prices);
    p[peak - 2] = (u8) TurnipPrices_DrawHigh(prices);
    p[peak] = (u8) TurnipPrices_DrawShare(prices, TURNIP_SMALL_PEAK_SHARE, TURNIP_SMALL_PEAK_SPREAD);
    p[peak - 1] = (u8) TurnipPrices_DrawShare(prices, TURNIP_SMALL_SIDE_SHARE, TURNIP_SMALL_SIDE_SPREAD);
    p[peak + 1] = (u8) TurnipPrices_DrawShare(prices, TURNIP_SMALL_SIDE_SHARE, TURNIP_SMALL_SIDE_SPREAD);
    TurnipPrices_DrawFalling(prices, peak + 2, TURNIP_PRICES_HALF_DAYS);
}
CLEAN_AS(func_020876f0, TurnipPrices_DrawSmallSpike)

/* func_02087770: 1.4-2.0 times the Sunday price. */
int TurnipPrices_DrawMid(TurnipPrices *prices)
{
    return TurnipPrices_DrawShare(prices, TURNIP_MID_SHARE, TURNIP_MID_SPREAD);
}
CLEAN_AS(func_02087770, TurnipPrices_DrawMid)

/* func_02087784: 0.8-1.4 times the Sunday price. */
int TurnipPrices_DrawHigh(TurnipPrices *prices)
{
    return TurnipPrices_DrawShare(prices, TURNIP_HIGH_SHARE, TURNIP_HIGH_SPREAD);
}
CLEAN_AS(func_02087784, TurnipPrices_DrawHigh)

/* func_02087798: 0.4-0.8 times the Sunday price. */
int TurnipPrices_DrawLow(TurnipPrices *prices)
{
    return TurnipPrices_DrawShare(prices, TURNIP_LOW_SHARE, TURNIP_LOW_SPREAD);
}
CLEAN_AS(func_02087798, TurnipPrices_DrawLow)

/* func_020877ac: half days `start` to `end` (excluded) falling: 0.79 times the Sunday price for
 * the first, 0.025 less for each next, each with up to 0.01 more. */
void TurnipPrices_DrawFalling(TurnipPrices *prices, int start, int end)
{
    int share = TURNIP_FALLING_SHARE;
    for (int i = start; i < end; i++) {
        prices->prices[i] = (u8) TurnipPrices_DrawShare(prices, share, TURNIP_FALLING_SPREAD);
        share -= TURNIP_FALLING_STEP;
    }
}
CLEAN_AS(func_020877ac, TurnipPrices_DrawFalling)

/* func_020877dc: the Sunday price times `share` plus a random part of `spread` (4.12 fixed
 * point), cut to a byte.
 * QUIRK: a price of 256 or more wraps; the shares drawn here stay below. */
int TurnipPrices_DrawShare(TurnipPrices *prices, int share, int spread)
{
    int random = (int) MainRandom_BelowB(spread);
    return (u8) ((prices->prices[0] * (share + random)) >> 12);
}
CLEAN_AS(func_020877dc, TurnipPrices_DrawShare)

/* func_02087800: the town's setting up: new prices, both dates today. */
void TurnipPrices_SetUp(TurnipPrices *prices)
{
    TurnipPrices_Draw(prices, 0);
    DateTime now = {0};
    DateTime_Now(&now);
    TurnipPrices_SetWeek(prices, &now);
    TurnipPrices_SetBought(prices, &now);
}
CLEAN_AS(func_02087800, TurnipPrices_SetUp)

/* func_02087830: no pattern yet, no peak, both dates 1 January 2000. The prices are left as
 * they are. */
void TurnipPrices_Clear(TurnipPrices *prices)
{
    prices->pattern = TURNIP_PATTERN_NONE;
    prices->peak = 0;
    prices->week = (Date){1, 1, 0, 0};
    prices->bought = (Date){1, 1, 0, 0};
}
CLEAN_AS(func_02087830, TurnipPrices_Clear)

/* func_0208784c: the destructor does nothing. */
void TurnipPrices_Destruct(TurnipPrices *prices)
{
    (void) prices;
}
CLEAN_AS(func_0208784c, TurnipPrices_Destruct)

/* func_02087850: the constructor does nothing. */
void TurnipPrices_Construct(TurnipPrices *prices)
{
    (void) prices;
}
CLEAN_AS(func_02087850, TurnipPrices_Construct)
