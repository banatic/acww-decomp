/* room_villager_6: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221ecf8 @ 0x0221ecf8, 0x14 bytes, Thumb
 * func_ov004_0221ecec @ 0x0221ecec, 0xc bytes, Thumb
 */

#include "types.h"

int func_ov004_0221ecf8(unsigned char *p)
{
    if (p[0x8d4] != 0) {
        return 0;
    }
    return 1;
}

void *func_ov004_0221ecec(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x8d4) = 0x1;
    return self;
}
