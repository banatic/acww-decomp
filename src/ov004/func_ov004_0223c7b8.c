/* func_ov004_0223c7b8 @ 0x0223c7b8, 0x1e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_0223cbb8(char *argument0);

void func_ov004_0223c7b8(char *self)
{
    // DECLS
    u32 i;
    // ENDDECLS
    for (i = 0; i < 0x2; i++) {
        func_ov004_0223cbb8(self + (i << 6));
    }
}
