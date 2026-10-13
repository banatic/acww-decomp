/* func_ov004_0222005c @ 0x0222005c, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov004_0222005c(u8 *self, u8 v)
{
    int i = 0;
    do {
        int j = i + 1;
        *(self + i + 0x8ac) = *(self + j + 0x8ac);
        i = j;
    } while (i < 0x63);
    *(self + 0x90f) = v;
}
