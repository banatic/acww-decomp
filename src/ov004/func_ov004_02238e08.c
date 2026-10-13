/* func_ov004_02238e08 @ 0x02238e08, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020e88dc();

void func_ov004_02238e08(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x264) = 0x1;
    *(void **) (self + 0x268) = 0x0;
    if (*(u8 *) (self + 0x280) != 0x0) {
        func_020e88dc(self + 0x278, 0x14, 0x29);
        func_020e88dc(self + 0x27c, 0xccd, 0xcd);
        *(u8 *) (self + 0x280) = (*(u8 *) (self + 0x280) - 0x1);
    } else {
        *(int *) (self + 0x278) = 0x14;
        *(int *) (self + 0x27c) = 0xccd;
    }
}
