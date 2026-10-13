/* func_020114b0 @ 0x020114b0, 0x6e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int, int);

void func_020114b0(int *p, int target, int a, int limit1, int limit2)
{
    int diff, adiff, res, ares;

    if (*p == target) {
        return;
    }

    diff = target - *p;
    adiff = (diff < 0) ? -diff : diff;

    if (adiff < limit2) {
        *p = target;
        return;
    }

    res = FX_MulFunc(diff, a);
    ares = (res < 0) ? -res : res;

    if (ares > limit1) {
        if (res >= 0) {
            *p += limit1;
        } else {
            *p -= limit1;
        }
        return;
    } else {
        if (ares < limit2) {
            if (res >= 0) {
                *p += limit2;
            } else {
                *p -= limit2;
            }
            return;
        } else {
            *p += res;
            return;
        }
    }
}
