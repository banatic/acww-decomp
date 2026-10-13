/* func_ov004_0223063c @ 0x0223063c, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov004_0223063c(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x6d4) = 0x0;
    *(u8 *) (self + 0x6b0) = 0x0;
    *(u8 *) (self + 0x6b1) = 0x1;
    *(u8 *) (self + 0x6b2) = 0x1;
    *(int *) (self + 0x4a4) = ((u32) ((*(int *) (self + 0x4a0) >> 12) << 16) >> 4);
    *(void **) (self + 0x4ac) = 0x0;
    *(int *) (self + 0x6bc) = ((u32) ((*(int *) (self + 0x6b8) >> 12) << 16) >> 4);
    *(void **) (self + 0x6c4) = 0x0;
    return 0x1;
}
