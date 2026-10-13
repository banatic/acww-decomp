/* func_ov133_0229b0d4 @ 0x0229b0d4, 0x1c bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov133_0229b0d4(u8 *p)
{
    int i;

    for (i = 0; i < 0xc; i++) {
        u8 *q = p + i;
        if (q[0xa4] == 0xa) {
            return i;
        }
    }
    return 0xc;
}
