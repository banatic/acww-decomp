/* func_ov004_0223cc5c @ 0x0223cc5c, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov004_0223cc5c(char *self, int a1, int a2, int a3)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + ((a3 & 0x1) << 8) + ((a2 & 0xf) << 4) + (a1 & 0xf)) == 0xff) {
        return -0x1;
    }
    return *(u8 *) (self + ((a3 & 0x1) << 8) + ((a2 & 0xf) << 4) + (a1 & 0xf));
}
