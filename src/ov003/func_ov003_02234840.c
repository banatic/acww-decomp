/* func_ov003_02234840 @ 0x02234840, 0x9c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O1,s
 */

// base defaults to e228 and only the != arm overrides it.
void func_ov003_02234840(char *self, short *ph)
{
    int base, tmp;
    int hi = 0x300;
    int e228 = *(int *) (self + 0x228);
    unsigned char on = *(unsigned char *) (self + 0x24c);
    int *v = (int *) (self + 0x204);
    unsigned char *st = (unsigned char *) (self + 0x256);
    int e220 = *(int *) (self + 0x220);
    base = e228;
    if (e228 != e220) {
        tmp = hi + e220;
        base = e220;
    } else {
        tmp = hi + e228;
    }
    if (*st < *ph) {
        if (on != 0) {
            *ph = 0;
            *st = 0x10;
        } else {
            *ph = 8;
            *st = 0x14;
        }
    }
    if (on != 0) {
        if (v[1] > tmp) {
            *(char *) (self + 0x24c) = 0;
        }
    }
    if (v[1] < base) {
        if (v[1] > base - 0x320) {
            v[1] = base;
        }
        *(char *) (self + 0x24c) = 1;
    }
}
