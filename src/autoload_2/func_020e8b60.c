/* func_020e8b60 @ 0x020e8b60, 0x50 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

void func_020e8b60(int *p, int target, int scale, int max)
{
    int delta;
    int inc;

    if (*p == target) {
        return;
    }

    delta = target - *p;
    inc = (int) (((long long) delta * scale + 0x800) >> 12);

    if (inc > max) {
        inc = max;
    } else if (inc < -max) {
        inc = -max;
    }

    *p += inc;
}
