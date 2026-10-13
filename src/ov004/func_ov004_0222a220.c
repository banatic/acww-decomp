/* func_ov004_0222a220 @ 0x0222a220, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void *func_ov004_0222a220(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if (a1 > 0x333) {
        *(u8 *) (self) = 0x0;
    } else {
        *(u8 *) (self) = 0x1;
    }
    *(u8 *) (self + 0x1) = 0x0;
    return self;
}
