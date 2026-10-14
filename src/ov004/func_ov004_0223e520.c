/* func_ov004_0223e520 @ 0x0223e520, 0xd0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02003564();
extern void func_02032c64();
extern void func_02055210();
extern void func_02089bd4();
extern void __cxa_vec_ctor();
extern void func_020012dc();
extern void func_020012e8();
extern void *data_0213efe8;
extern void *data_0213f020;
extern void *data_ov004_0225622c;

void *func_ov004_0223e520(char *self)
{
    // DECLS
    // ENDDECLS
    func_02003564(self);
    *(void **) (self) = &data_ov004_0225622c;
    *(int *) (self + 0xd4) = 0x614;
    *(int *) (self + 0xd8) = 0x6b8;
    func_02032c64(self + 0xdc);
    *(void **) (self + 0x114) = &data_0213efe8;
    *(void **) (self + 0x114) = &data_0213f020;
    func_02055210(self + 0x120);
    func_02089bd4(self + 0x1d8);
    __cxa_vec_ctor(self + 0x230, 0x2, 0xc, (void *) func_020012e8, (void *) func_020012dc);
    __cxa_vec_ctor(self + 0x248, 0x2, 0xc, (void *) func_020012e8, (void *) func_020012dc);
    *(int *) (self + 0x110) = 0x1;
    *(u8 *) (self + 0x260) = 0x0;
    *(u8 *) (self + 0x262) = 0x0;
    *(u16 *) (self + 0x22e) = 0x0;
    *(int *) (self + 0x10c) = 0x3;
    return self;
}
