/* func_ov004_0223d2b0 @ 0x0223d2b0, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov004_0223d2b0(char *self)
{
    // DECLS
    u32 i;
    // ENDDECLS
    for (i = 0; i < 0x2; i++) {
        *(void **) (self + (i << 2)) = 0x0;
        *(u16 *) (self + (i << 1) + 0x8) = 0xfff1;
        *(u8 *) (self + 0xc) = 0x0;
    }
}
