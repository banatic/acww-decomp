/* func_ov003_0223418c @ 0x0223418c, 0xd8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int n);

short func_ov003_0223418c(short a, int b)
{
    short a0;
    int t;

    a0 = a;
    if (b == 3) {
        t = func_020644cc(0x64);
        a = a + 0x8000;
        if (t < 5) {
            a = a + 0x2aaa;
        } else if (t < 0xa) {
            a = a - 0x2aaa;
        }
    } else if ((b == 1 && (a < -0x4000 || (a >= 0 && a < 0x4000))) || (b == 2 && (a > 0x4000 || (a <= 0 && a > -0x4000)))) {
        a = -a;
    } else if (a >= 0) {
        a = 0x8000 - a;
    } else {
        a = -0x8000 - a;
    }
    if (func_020644cc(0x64) < 0xa) {
        if (a >= 0) {
            a = a + 0xaaa;
        } else {
            a = a - 0xaaa;
        }
    }
    if (a == a0) {
        if (a >= 0) {
            a = a + 0xaaa;
        } else {
            a = a - 0xaaa;
        }
    }
    return a;
}
