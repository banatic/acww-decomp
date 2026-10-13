/* func_ov068_022759f8 @ 0x022759f8, 0x3c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_020147e0(void *p, int a, int b);

void func_ov068_022759f8(void *self)
{
    signed char *p;
    int v;

    p = (signed char *) self;
    v = p[0xa61];
    if (v > 0) {
        p[0xa61] = v - 1;
    }
    if (p[0xa61] == 0) {
        func_020147e0((char *) self + 0x618, 0, 1);
        p[0xa61] = -1;
    }
}
