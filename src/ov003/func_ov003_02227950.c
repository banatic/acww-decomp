/* func_ov003_02227950 @ 0x02227950, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

int func_ov003_02227950(int a, int b, int c)
{
    int r = 0;
    a = a - b;
    if (a < 0) {
        a = -a;
    }
    b = c - b;
    if (b < 0) {
        b = -b;
    }
    if (a >= b) {
        r = 1;
    }
    return r;
}
