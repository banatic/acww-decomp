/* func_ov004_022447c0 @ 0x022447c0, 0xdc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int n);

short func_ov004_022447c0(short ang, int mode)
{
    short orig;
    unsigned char r;

    orig = ang;
    r = (unsigned char) func_020644cc(0x64);
    if (mode == 3) {
        ang = (short) (ang + 0x8000);
        if (r < 5) {
            ang = (short) (ang + 0x2aaa);
        } else if (r < 0xa) {
            ang = (short) (ang - 0x2aaa);
        }
    } else if ((mode == 1 && (ang < -0x4000 || (ang >= 0 && ang < 0x4000))) ||
               (mode == 2 && (ang > 0x4000 || (ang <= 0 && ang > -0x4000)))) {
        ang = (short) (-ang);
    } else if (ang >= 0) {
        ang = (short) (0x8000 - ang);
    } else {
        ang = (short) (-0x8000 - ang);
    }
    if (r > 0x50) {
        if (ang - orig >= 0) {
            ang = (short) (ang + 0x1554);
        } else {
            ang = (short) (ang - 0x1554);
        }
    }
    if (ang == orig) {
        if (ang >= 0) {
            ang = (short) (ang + 0xaaa);
        } else {
            ang = (short) (ang - 0xaaa);
        }
    }
    return ang;
}
