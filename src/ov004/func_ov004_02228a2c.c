/* func_ov004_02228a2c @ 0x02228a2c, 0x10 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void *func_ov004_02228a2c(char *self, char *a1, int a2)
{
    // DECLS
    // ENDDECLS
    *(int *) (self) = *(int *) (a1);
    *(int *) (self + 0x4) = *(int *) (a1 + 0x4);
    *(int *) (self + 0x8) = *(int *) (a1 + 0x8);
    *(u8 *) (self + 0xc) = a2;
    return self;
}
