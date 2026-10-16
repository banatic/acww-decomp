/* The week's turnip prices (the state block's part at 0x17364, 0x1a bytes).
 *
 * On the week's first game day (a game day starts at 6:00) a buying price of 90-110 is drawn
 * for Sunday, morning and afternoon, and the twelve selling prices of Monday to Saturday follow
 * one of four patterns, each a share of the Sunday price (TurnipPrices_Draw):
 *
 * - random: highs of 0.8-1.4 and lows of 0.4-0.8 in a fixed order;
 * - big spike: falling from 0.79, then 1.4-2.0, 2.0-6.1 (the peak, which may pass 255 and is
 *   kept in `peak`), 1.4-2.0, 0.8-1.4, then falling again;
 * - falling: from 0.79 down by 0.025 a half day, all week;
 * - small spike: falling, two of 0.8-1.4, then 1.4-1.7, 1.7-2.0, 1.4-1.7, then falling.
 *
 * The next week's pattern depends on this week's; a clock moved back (or the global flags
 * 0x20 and 0x08, func_0206f798 and func_0206f7a4) forces the falling one.
 *
 * A second date (`bought`) goes with flag 4 of the state block, which overlay 73 sets when it
 * sells item 0x1567 for 1000 Bells: a week after that date the flag is cleared. */
#ifndef CLEAN_MAIN_TURNIP_PRICES_H
#define CLEAN_MAIN_TURNIP_PRICES_H

#include "calendar.h"
#include "types.h"

#define TURNIP_PRICES_HALF_DAYS 14 /* Sunday to Saturday, morning and afternoon */
#define TURNIP_PATTERN_NONE 0xff   /* before the first draw */

enum TurnipPattern {
    TURNIP_PATTERN_RANDOM = 0,
    TURNIP_PATTERN_BIG_SPIKE = 1,
    TURNIP_PATTERN_FALLING = 2,
    TURNIP_PATTERN_SMALL_SPIKE = 3
};

typedef struct TurnipPrices {
    Date week;                          /* 0x00: the game day the prices were drawn */
    Date bought;                        /* 0x04: the game day flag 4 of the state block counts from */
    u16 peak;                           /* 0x08: the big spike's peak, in place of its 0 price */
    u8 prices[TURNIP_PRICES_HALF_DAYS]; /* 0x0a: by weekday (0 Sunday) * 2 + afternoon */
    u8 pattern;                         /* 0x18: TurnipPattern or TURNIP_PATTERN_NONE */
    u8 unused_19;
} TurnipPrices;

void TurnipPrices_SetBought(TurnipPrices *prices, const DateTime *when);
void TurnipPrices_ExpireBought(TurnipPrices *prices);
void TurnipPrices_SetWeek(TurnipPrices *prices, const DateTime *when);
void TurnipPrices_Update(TurnipPrices *prices, int unused);
void TurnipPrices_RedrawIfClockMoved(TurnipPrices *prices);
int TurnipPrices_Current(TurnipPrices *prices);
void TurnipPrices_Draw(TurnipPrices *prices, int falling);
int TurnipPrices_DrawPeak(TurnipPrices *prices);
void TurnipPrices_DrawSmallSpike(TurnipPrices *prices);
int TurnipPrices_DrawHigh(TurnipPrices *prices);
int TurnipPrices_DrawMid(TurnipPrices *prices);
int TurnipPrices_DrawLow(TurnipPrices *prices);
void TurnipPrices_DrawFalling(TurnipPrices *prices, int start, int end);
int TurnipPrices_DrawShare(TurnipPrices *prices, int share, int spread);
void TurnipPrices_SetUp(TurnipPrices *prices);
void TurnipPrices_Clear(TurnipPrices *prices);
void TurnipPrices_Destruct(TurnipPrices *prices);
void TurnipPrices_Construct(TurnipPrices *prices);

#endif
