/* func_ov126_022a011c @ 0x022a011c, 0x4c bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov126_022a0740(unsigned char *p);
extern void func_ov124_0229f2c8(unsigned char *p, int a, int b, int c, int d);

void func_ov126_022a011c(unsigned char *p)
{
    int diff;
    int min;
    int k1;
    int k2;

    if (func_ov126_022a0740(p)) {
        unsigned char a = p[0xaa];
        unsigned char b = p[0xa9];

        if (b > a) {
            min = a;
            diff = b - a;
        } else {
            min = b;
            diff = a - b;
        }
        k1 = 7;
        k2 = 6;
    } else {
        diff = 0;
    }

    if (diff != 0) {
        func_ov124_0229f2c8(p + 0xb0, k1, k2, min, diff);
    }
}
