/* func_ov002_02208d4c @ 0x02208d4c, 0x28 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov002_02208d4c(u8 *p, u8 a, u8 b)
{
    int i;

    for (i = 0; i < 5; i++) {
        u8 *q = p + i;
        if (p[i] == 0xff) {
            *q = a;
            q[5] = b;
            return 1;
        }
    }
    return 0;
}
