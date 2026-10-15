/* func_ov004_02227664 @ 0x02227664, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0222626c(void *argument0, unsigned int argument1, unsigned int argument2);

void func_ov004_02227664(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x704) == 0x3f && (u32) ((u32) (*(int *) (self + 0x2d8) << 4) >> 16) >= 0x9) {
        func_ov004_0222626c(self, 0x0, 0x6);
    }
}
