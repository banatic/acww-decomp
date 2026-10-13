/* func_ov004_02211764 @ 0x02211764, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_022118bc(char *self, int a);
void func_ov004_02211764(char *self)
{
    if (*(u16 *) (self + 0x852) == 0) {
        func_ov004_022118bc(self, 2);
    }
    self += 0x852;
    if (*(u16 *) self != 0) {
        *(u16 *) self = *(u16 *) self - 1;
    }
}
