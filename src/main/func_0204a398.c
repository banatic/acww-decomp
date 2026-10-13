/* func_0204a398 @ 0x0204a398, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0204a398(int a, int *p, int b, int c)
{
    if (*p == b * c) {
        return 0;
    }
    if (*p > 0 || p[1] > 0) {
        return 1;
    }
    if (p[2] > 0) {
        return 2;
    }
    if (p[4] < 8) {
        return 3;
    }
    return 4;
}
