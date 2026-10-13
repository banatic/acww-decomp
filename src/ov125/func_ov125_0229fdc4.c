/* func_ov125_0229fdc4 @ 0x0229fdc4, 0x7c bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov002_0220a784(int a, int b);
extern int func_ov125_0229fe40(int a, int b);
extern int func_ov125_0229fe4c(int a, int b);

int func_ov125_0229fdc4(int param0)
{
    unsigned char i;
    int c1, c2, lo1, hi1, lo2, hi2;
    if (func_ov002_0220a784(param0 + 0x6a8, 9) != 0) {
        return 8;
    }
    c1 = data_021f6c58;
    c2 = data_021f6c54;
    lo1 = c1 - 0x10;
    hi1 = c1 + 0x10;
    lo2 = c2 - 0x10;
    hi2 = c2 + 0x10;
    for (i = 0; i < 8; i++) {
        int v = func_ov125_0229fe4c(param0, i);
        if (lo1 >= v) {
            continue;
        }
        if (v >= hi1) {
            continue;
        }
        v = func_ov125_0229fe40(param0, i);
        if (lo2 >= v) {
            continue;
        }
        if (v >= hi2) {
            continue;
        }
        return i;
    }
    return 9;
}
