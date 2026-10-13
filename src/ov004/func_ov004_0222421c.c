/* func_ov004_0222421c @ 0x0222421c, 0xe bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov004_0222421c(char *self, int v)
{
    *(int *) (self + 0xb0) = v;
    *(u8 *) (self + 0xb8) = 0;
}
