/* func_ov004_02227e7c @ 0x02227e7c, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov004_02227e7c(char *self, int a, short b, int c, int d, u8 e)
{
    *(int *) self = a;
    *(short *) (self + 4) = b;
    *(int *) (self + 8) = c;
    *(int *) (self + 0xc) = d;
    *(u8 *) (self + 0x10) = e;
}
