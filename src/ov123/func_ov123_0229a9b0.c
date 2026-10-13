/* func_ov123_0229a9b0 @ 0x0229a9b0, 0x168 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_ov123_0229cbac[];
extern int _s32_div_f(int a, int b);
extern void func_ov123_0229adc8(void *dst, unsigned char x, unsigned char y, int col);

void func_ov123_0229a9b0(void *dst, int l, int t, int r, unsigned char b, int col, int mode)
{
    int w;
    int cx;
    int ang;
    int i;
    int cy;
    int hw, hh;
    int h;
    int dx, dy;
    int step;
    int ya, yb, xb;
    int yl, xl, xr;
    int d;
    int s;
    int v;

    w = r - l;
    h = b - t;
    hw = w >> 1;
    hh = h >> 1;
    cx = l + hw;
    cy = t + hh;
    d = hw - hh;
    if (d < 0) {
        d = -d;
    }
    s = hw + hh;
    v = s - (((s >> 1) - (s >> 3)) - (d >> 1) - 5);
    step = _s32_div_f(0x40, (short) (v | 1));
    ang = 0;
    h = h & 1;
    w = w & 1;
    while (ang < 0x40) {
        dx = (data_ov123_0229cbac[ang + 0x40] * hw + 0x2d) >> 8;
        dy = (data_ov123_0229cbac[ang] * hh + 0x2d) >> 8;
        if (mode != 0) {
            i = cx - dx;
            ya = cy - dy;
            yb = h + (cy + dy);
            xb = w + (cx + dx);
            for (; i <= xb; i++) {
                func_ov123_0229adc8(dst, i, ya, col);
                func_ov123_0229adc8(dst, i, yb, col);
            }
        } else {
            xr = w + (cx + dx);
            yl = h + (cy + dy);
            func_ov123_0229adc8(dst, xr, yl, col);
            i = cy - dy;
            func_ov123_0229adc8(dst, xr, i, col);
            xl = cx - dx;
            func_ov123_0229adc8(dst, xl, yl, col);
            func_ov123_0229adc8(dst, xl, i, col);
        }
        ang = (short) (ang + step);
    }
}
