/* func_ov004_0222c51c @ 0x0222c51c, 0x1a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov004_0222c51c(char *self)
{
    // DECLS
    u32 i;
    // ENDDECLS
    *(void **) (self) = 0x0;
    *(void **) (self + 0x4) = 0x0;
    for (i = 0; i < 0xd; i++) {
        *(void **) (self + (i << 2) + 0x3c) = 0x0;
        *(void **) (self + (i << 2) + 0x8) = 0x0;
        *(void **) (self + (i << 2) + 0x70) = 0x0;
    }
}
