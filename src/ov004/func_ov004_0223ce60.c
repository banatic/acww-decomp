/* func_ov004_0223ce60 @ 0x0223ce60, 0x10 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov004_0223ce60(char *self)
{
    // DECLS
    u32 i;
    // ENDDECLS
    for (i = 0; i < 0x1c; i++) {
        *(void **) (self + (i << 2)) = 0x0;
    }
}
