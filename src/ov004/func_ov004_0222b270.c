/* func_ov004_0222b270 @ 0x0222b270, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov004_0222b270(char *self, int a, int b, short c, u8 d, u8 e)
{
    *(int *) self = a;
    *(int *) (self + 4) = b;
    *(short *) (self + 8) = c;
    *(u8 *) (self + 0xa) = d;
    *(u8 *) (self + 0xb) = e;
}
