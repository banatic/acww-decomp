/* func_ov004_0221b060 @ 0x0221b060, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0221afe8(void);
extern s16 data_ov004_02253238;
extern int data_ov004_022577d0;
extern int func_ov004_0221afb8(void *self);
extern int func_020b65c4(void);
extern void func_0203efb0(void *self, u16 a);
extern int func_ov004_0221ae7c(void *self, int a);

int func_ov004_0221b060(char *self)
{
    func_ov004_0221afe8();
    *(s16 *) (self + 0x156) = data_ov004_02253238;
    *(int *) (self + 0x158) = data_ov004_022577d0;
    if (func_ov004_0221afb8(self)) {
        func_0203efb0(self, (u16) (*(u8 *) (self + 0x154) | (func_020b65c4() << 8)));
        func_ov004_0221ae7c(self, 0);
        return 1;
    }
    return 0;
}
