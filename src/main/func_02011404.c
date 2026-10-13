/* func_02011404 @ 0x02011404, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int, int);

int func_02011404(short *p, int b, int c, int d, int e)
{
    int diff;
    int from;
    int to;
    int step;
    short a = *p;

    if (a == b) {
        return 0;
    }
    from = a << 12;
    to = b << 12;
    diff = to - from;
    if (diff < 0) {
        diff = -diff;
    }
    if (diff > 0x08000000) {
        step = FX_MulFunc(c, 0x10000000 - diff);
    } else {
        step = FX_MulFunc(c, diff);
    }
    if (step <= e) {
        *p = b;
        return 0;
    }
    if (step > d) {
        step = d;
    }
    if (to >= from) {
        step = diff > 0x08000000 ? from - step : from + step;
    } else {
        step = diff > 0x08000000 ? from + step : from - step;
    }
    *p = step >> 12;
    return (short) (b - *p);
}
