/* func_ov002_02209b6c @ 0x02209b6c, 0x28 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov002_02209b6c(char *self, u8 a, u16 b, u8 c, u8 d)
{
    *(u8 *) (self + 0x6e) = a;
    *(u16 *) (self + 0x6c) = b;
    *(u8 *) (self + 0x6f) = c;
    *(u8 *) (self + 0x70) = d;
}
