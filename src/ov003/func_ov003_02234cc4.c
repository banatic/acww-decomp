/* func_ov003_02234cc4 @ 0x02234cc4, 0x2a bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020550e4(u8 *p, int mode);

void func_ov003_02234cc4(u8 *self)
{
    if ((((unsigned int) (*(int *) (self + 0xf4)) << 4) >> 16) == 1) {
        func_020550e4(self + 0x50, 2);
    } else {
        func_020550e4(self + 0x50, 1);
    }
}
