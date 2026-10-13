/* func_ov004_0220d494 @ 0x0220d494, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov004_0220d494(char *self, int a1, char *a2, int a3)
{
    // DECLS
    // ENDDECLS
    if (a1 >= 0x0 && (u32) a1 < 0x1c) {
        *(u16 *) (self) = a1;
        *(int *) (self + 0x4) = *(int *) (a2);
        *(int *) (self + 0x8) = *(int *) (a2 + 0x4);
        *(int *) (self + 0xc) = *(int *) (a2 + 0x8);
        *(u16 *) (self + 0x2) = a3;
        return 0x1;
    }
    return 0x0;
}
