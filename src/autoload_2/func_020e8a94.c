/* func_020e8a94 @ 0x020e8a94, 0x78 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int _s32_div_f(int, int);

void func_020e8a94(short *r5, int r1, int r2, int r4)
{
    int r0;
    int r3;
    int r6;

    r0 = (short) r5[0];
    r0 = (short) (r1 - r0);
    r0 = _s32_div_f(r0, r2);
    r0 = (short) r0;
    r3 = r0;
    if (r3 > r4) {
        r0 = (short) r5[0];
        r0 = r0 + r4;
        r5[0] = (short) r0;
        return;
    }
    r0 = -r4;
    if (r3 < r0) {
        r0 = (short) r5[0];
        r0 = r0 - r4;
        r5[0] = (short) r0;
    } else {
        r0 = (short) r5[0];
        r0 = r0 + r3;
        r5[0] = (short) r0;
    }
}
