/* func_ov004_0222c3b4 @ 0x0222c3b4, 0x10 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov004_0222c3b4(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if ((u32) a1 < 0xd) {
        return *(int *) (self + (a1 << 2) + 0x3c);
    }
    return 0x0;
}
