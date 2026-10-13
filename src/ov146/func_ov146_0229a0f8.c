/* func_ov146_0229a0f8 @ 0x0229a0f8, 0x7c bytes, Thumb, module ov146
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

extern void MI_CpuFill8(u8 *dst, int val, int len);
extern void MI_CpuCopy8(u8 *src, u8 *dst, int len);
extern u8 *func_ov146_0229a174(u8 *self);
extern int func_ov146_02299ee8(u8 *self, u8 *p);

void func_ov146_0229a0f8(u8 *self)
{
    int i;
    u8 *base;
    u8 *src;

    MI_CpuFill8(self + 0x12a, 0, 0x460);
    base = func_ov146_0229a174(self);
    i = 0;
    do {
        src = (base + 0x180) + 0x23 * i;
        if (func_ov146_02299ee8(self, src) != 0) {
            MI_CpuCopy8(src, (self + 0x12a) + 0x23 * i, 0x23);
            (self + i)[0x10a] = 0x14;
        } else {
            (self + i)[0x10a] = 0;
        }
        i++;
    } while (i < 0x20);
}
