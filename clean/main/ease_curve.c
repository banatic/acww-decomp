/* An eased move's share done (ease_curve.h). */
#include "ease_curve.h"

#include "clean.h"

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_MulFunc(fx32 a, fx32 b);

#define EASE_CURVE_ALL 0x1000 /* 1.0 */

static fx32 at_most_all(fx32 share)
{
    return share > EASE_CURVE_ALL ? EASE_CURVE_ALL : share;
}

/* func_020643dc: the share (0 to 1.0) of a move from `start` to `end` done at `time`, its speed
 * rising over the first `rise` and falling over the last `fall`. The even speed is 2k, k being
 * 1.0 over (2 * length - rise - fall); the rising part gives k * x^2 / rise at x into the move,
 * the falling part takes k * y^2 / fall off at y before its end. A move shorter than its rise
 * and fall together is not done at all (0) until `end`.
 * QUIRK: the products are fixed-point (FX_MulFunc, FX_Div) and wrap as the game's do. */
fx32 EaseCurve_Share(fx32 time, fx32 start, fx32 end, fx32 rise, fx32 fall)
{
    if (time >= end) {
        return EASE_CURVE_ALL;
    }
    if (time <= start) {
        return 0;
    }
    fx32 length = end - start;
    fx32 x = time - start;
    if (length < rise + fall) {
        return 0;
    }
    fx32 k = FX_Div(EASE_CURVE_ALL, length * 2 - rise - fall);

    fx32 share = 0;
    if (rise != 0) {
        if (x <= rise) {
            return at_most_all(FX_Div(FX_MulFunc(k, FX_MulFunc(x, x)), rise));
        }
        share = FX_MulFunc(k, rise);
    }
    if (x <= length - fall) {
        return at_most_all(share + (FX_MulFunc(k, x - rise) * 2));
    }
    share += FX_MulFunc(k, length - rise - fall) * 2;
    if (fall != 0) {
        share += FX_MulFunc(k, fall);
        if (x < length) {
            fx32 y = length - x;
            share -= FX_Div(FX_MulFunc(k, FX_MulFunc(y, y)), fall);
        }
    }
    return at_most_all(share);
}
CLEAN_AS(func_020643dc, EaseCurve_Share)
