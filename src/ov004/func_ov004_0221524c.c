/* func_ov004_0221524c @ 0x0221524c, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02004108(void *, int, int);

void func_ov004_0221524c(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x858) != 0x0) {
        func_02004108(self + 0x844, a1, 0x844);
    }
}
