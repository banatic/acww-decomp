/* Angles and random numbers. Angles are 16-bit fractions of a turn (0x10000 = 360 degrees),
 * counted from +X towards +Y, as NitroSDK's FX_SinIdx takes them. */
#ifndef CLEAN_AUTOLOAD_2_FX_MATH_H
#define CLEAN_AUTOLOAD_2_FX_MATH_H

#include "types.h"

/* A linear congruential generator; the game keeps one per user (the first is at 021cb5a0). */
typedef struct Random {
    u32 state;
} Random;

s16 Math_Atan2(fx32 y, fx32 x);
u32 Random_Below(Random *random, u32 range);
u32 Random_Next(Random *random);
void Random_Init(Random *random, u32 seed);

#endif
