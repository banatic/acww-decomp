/* func_ov096_0229f320 @ 0x0229f320, 0x7c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229e158(void);
extern int func_0204c120(int a, int b, int c);

int func_ov096_0229f320(char *p, int a, int b)
{
    int threshold;

    if (b < 0x50 || b > 0x60) {
        return 0;
    }
    p[0xbf] = 0;
    if (a < 0x30) {
        return 0;
    }
    if (a < 0x40) {
        threshold = 10000;
        p[0xbf] = 3;
    } else if (a < 0x48) {
        threshold = 1000;
        p[0xbf] = 2;
    } else if (a < 0x60) {
        threshold = 100;
        p[0xbf] = 1;
    } else {
        return 0;
    }
    // clang-format off
    asm {
        mov r0, p
    }
    // clang-format on
    if (threshold > func_ov096_0229e158())
    {
        return 1;
    }
    *(short *) (p + 0xae) = func_0204c120(threshold, 0, 0);
    return 2;
}
