/* func_ov002_02208d30 @ 0x02208d30, 0x1c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov002_02208d30(u8 *p, u8 v)
{
    int i;

    for (i = 0; i < 5; i++) {
        u8 *q = p + i;
        p[i] = 0xff;
        q[5] = v;
    }
    p[0xa] = 0;
}
