/* func_ov004_02238fe4 @ 0x02238fe4, 0x3e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov004_02238fe4(short *out, u8 *flag, int *ctr, int lim, int mul)
{
    int v;
    if (*flag != 0) {
        *ctr = *ctr + 1;
    } else {
        *ctr = *ctr - 1;
    }
    v = (short) (*ctr * mul);
    if (v >= lim) {
        v = lim;
        *flag = 0;
    } else if (v <= 0) {
        v = 0;
        *flag = 1;
    }
    *out = v;
}
