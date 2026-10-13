/* func_ov004_0220db48 @ 0x0220db48, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov004_0220db48(char *self)
{
    // DECLS
    u32 i;
    // ENDDECLS
    *(void **) (self) = 0x0;
    for (i = 0; i < 0x4; i++) {
        *(void **) (self + (i << 2) + 0x4) = 0x0;
    }
}
