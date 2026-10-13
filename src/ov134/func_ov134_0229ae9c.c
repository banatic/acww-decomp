/* func_ov134_0229ae9c @ 0x0229ae9c, 0x38 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

int func_ov134_0229ae9c(int unused, int a, int b)
{
    int diff1;
    int diff2;

    diff1 = a - b;
    diff2 = b - a;
    while (diff1 < 0) {
        diff1 += 0x10000;
    }
    while (diff1 >= 0x10000) {
        diff1 -= 0x10000;
    }
    while (diff2 < 0) {
        diff2 += 0x10000;
    }
    while (diff2 >= 0x10000) {
        diff2 -= 0x10000;
    }
    if (diff1 > diff2) {
        diff1 = -diff2;
    }
    return diff1;
}
