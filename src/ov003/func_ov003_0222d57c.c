/* func_ov003_0222d57c @ 0x0222d57c, 0x110 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov003_0222d230();
extern void func_02032c64();
extern void func_02055210();
extern void func_02089b04();
extern void func_0209d11c();
extern void func_02138d6c();
extern void func_0209d34c();
extern void func_0209d0a4();
extern void func_020012e8();
extern void func_020012dc();
extern void *data_0213efe8;
extern void *data_0213f020;

void *func_ov003_0222d57c(char *self)
{
    func_ov003_0222d230(self);
    func_02032c64(self + 0x20);
    func_02055210(self + 0x50);
    func_02089b04(self + 0x108);
    func_0209d11c(self + 0x130);
    *(void **) (self + 0x174) = &data_0213efe8;
    *(void **) (self + 0x174) = &data_0213f020;
    func_02138d6c(self + 0x1ec, 0x2, 0xc, (void *) func_020012e8, (void *) func_020012dc);
    func_0209d34c(self + 0x230);
    func_0209d0a4(self + 0x130);
    *(u8 *) (self + 0x251) = 0x13;
    *(u8 *) (self + 0x24f) = 0;
    *(u16 *) (self + 0x23a) = 0;
    *(u16 *) (self + 0x23c) = 0;
    *(u16 *) (self + 0x238) = 0;
    *(s8 *) (self + 0x24d) = -1;
    *(u8 *) (self + 0x250) = 0;
    *(int *) (self + 0x170) = 0;
    *(u8 *) (self + 0x24c) = 1;
    *(u16 *) (self + 0x242) = 0;
    *(u8 *) (self + 0x24b) = 1;
    *(u8 *) (self + 0x24a) = 0;
    *(u8 *) (self + 0x248) = 0;
    *(u8 *) (self + 0x249) = 0;
    *(u8 *) (self + 0x252) = 0;
    *(int *) (self + 0x22c) = -1;
    return self;
}
