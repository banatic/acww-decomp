/* func_ov004_0222d30c @ 0x0222d30c, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov004_0222d30c(char *self, int v)
{
    *(u8 *) (self + 0x490) = 1;
    *(int *) (self + 0x494) = v;
}
