/* Angles and random numbers (fx_math.h). */
#include "fx_math.h"

#include "clean.h"

extern fx32 FX_Div(fx32 numerator, fx32 denominator);

/* The arctangent of 0 to 1 in 1024 steps, as an angle (0 to 0x2000): entry i is atan(i / 1024). */
extern const u16 data_0213dda0[0x401];

/* The angle of the slope `small` / `large`, 0 to 1 (REQUIRES: 0 <= small <= large). */
static int octant_angle(fx32 small, fx32 large)
{
    return data_0213dda0[FX_Div(small, large) >> 2];
}

/* func_020e8ed8: the angle of the direction (x, y). The angle of (0, 0) is 0.
 * Each octant divides the smaller coordinate by the larger and looks the slope up.
 * REQUIRES: neither coordinate is -0x80000000, which cannot be negated. */
s16 Math_Atan2(fx32 y, fx32 x)
{
    int angle;
    if (y == 0) {
        angle = x >= 0 ? 0 : 0x8000;
    } else if (x == 0) {
        angle = y >= 0 ? 0x4000 : 0xc000;
    } else if (y > 0) {
        if (x > 0) {
            angle = x >= y ? octant_angle(y, x) : 0x4000 - octant_angle(x, y);
        } else {
            x = -x;
            angle = x < y ? 0x4000 + octant_angle(x, y) : 0x8000 - octant_angle(y, x);
        }
    } else if (x < 0) {
        angle = x <= y ? 0x8000 + octant_angle(-y, -x) : 0xc000 - octant_angle(-x, -y);
    } else {
        y = -y;
        angle = x < y ? 0xc000 + octant_angle(x, y) : -octant_angle(y, x);
    }
    return (s16) angle;
}
CLEAN_AS(func_020e8ed8, Math_Atan2)

/* func_020e92d0: a random number from 0 to `range` - 1: the next state scaled to the range. */
u32 Random_Below(Random *random, u32 range)
{
    return (u32) (((u64) range * Random_Next(random)) >> 32);
}
CLEAN_AS(func_020e92d0, Random_Below)

/* func_020e92e8: the next state, which is the random number. The constants are those of
 * Numerical Recipes' quick generator. */
u32 Random_Next(Random *random)
{
    random->state = random->state * 0x0019660du + 0x3c6ef35fu;
    return random->state;
}
CLEAN_AS(func_020e92e8, Random_Next)

/* func_020e930c: the generator's constructor. */
void Random_Init(Random *random, u32 seed)
{
    random->state = seed;
}
CLEAN_AS(func_020e930c, Random_Init)
