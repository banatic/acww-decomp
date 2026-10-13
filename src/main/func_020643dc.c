/* func_020643dc @ 0x020643dc, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);

int func_020643dc(int t, int a, int b, int rise, int fall)
{
    int span;
    int x;
    int k;
    int acc;

    if (t >= b) {
        return 0x1000;
    }
    if (t <= a) {
        return 0;
    }
    span = b - a;
    x = t - a;
    if (span < rise + fall) {
        return 0;
    }
    k = FX_Div(0x1000, span * 2 - rise - fall);
    acc = 0;
    if (rise != 0) {
        if (x <= rise) {
            int r = FX_Div(FX_MulFunc(k, FX_MulFunc(x, x)), rise);
            if (r > 0x1000) {
                r = 0x1000;
            }
            return r;
        }
        acc = FX_MulFunc(k, rise);
    }
    if (x <= span - fall) {
        int r = acc + (FX_MulFunc(k, x - rise) << 1);
        if (r > 0x1000) {
            r = 0x1000;
        }
        return r;
    }
    acc = acc + (FX_MulFunc(k, span - rise - fall) << 1);
    if (fall != 0) {
        acc = acc + FX_MulFunc(k, fall);
        if (x < span) {
            acc = acc - FX_Div(FX_MulFunc(k, FX_MulFunc(span - x, span - x)), fall);
        }
    }
    if (acc > 0x1000) {
        acc = 0x1000;
    }
    return acc;
}
