/* func_02087d00 @ 0x02087d00, 0xce bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void MI_CpuFill8(void *dst, int v, int n);
extern int func_020644cc(int);

int func_02087d00(int *out, int (*fn)(int, int, int), int ctx, int lo, int hi, int arg, u16 *bits, int nrows)
{
    int row;
    int k;
    int bit2;
    int bit;
    int count;
    int row2;
    int i;
    int t;
    u16 v;

    bit = 0;
    row = 0;
    count = 0;
    if (lo > hi) {
        t = lo;
        lo = hi;
        hi = t;
    }
    MI_CpuFill8(bits, 0, nrows * 2);
    for (i = lo; i <= hi; i++) {
        if (fn(ctx, i, arg) != 0) {
            v = bits[row];
            bits[row] = v | (1 << bit);
            count++;
        }
        bit++;
        if (bit >= 0x10) {
            bit = 0;
            row++;
        }
        if (row >= nrows) {
            break;
        }
    }
    if (count > 0) {
        k = func_020644cc(count);
        bit2 = 0;
        row2 = 0;
        for (; lo <= hi; lo++) {
            if (((bits[row2] >> bit2) & 1) != 0) {
                if (k == 0) {
                    *out = lo;
                    return 1;
                }
                k--;
            }
            bit2++;
            if (bit2 >= 0x10) {
                bit2 = 0;
                row2++;
            }
            if (row2 >= nrows) {
                break;
            }
        }
    }
    return 0;
}
