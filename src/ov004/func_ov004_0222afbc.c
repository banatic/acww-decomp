/* func_ov004_0222afbc @ 0x0222afbc, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov004_0222afbc(char *self, u8 a, int b, int c, u8 d)
{
    *(u8 *) self = a;
    *(int *) (self + 4) = b;
    *(int *) (self + 8) = c;
    *(u8 *) (self + 0xc) = d;
}
