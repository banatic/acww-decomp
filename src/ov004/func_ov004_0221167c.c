/* func_ov004_0221167c @ 0x0221167c, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0203e020(char *self);
void func_ov004_0221167c(char *self)
{
    if (*(u16 *) (self + 0x852) == 0) {
        func_0203e020(self);
    }
    self += 0x852;
    if (*(u16 *) self != 0) {
        *(u16 *) self = *(u16 *) self - 1;
    }
}
