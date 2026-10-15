/* func_ov004_0223a5e4 @ 0x0223a5e4, 0xac bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_02054e54(void *argument0);
extern void func_0209d0a4(void *argument0);
extern void *func_0209d11c(void *argument0);
extern void func_0209d34c(unsigned short *argument0);
extern void __cxa_vec_ctor();
extern void *func_ov004_02239c40(char *argument0);
extern void func_020012dc(void *arg0);
extern void func_020012e8(void *arg0);
extern void *data_ov004_02255db4;

void *func_ov004_0223a5e4(char *self)
{
    // DECLS
    int i;
    // ENDDECLS
    *(void **) (self) = &data_ov004_02255db4;
    func_ov004_02239c40(self + 0x4);
    func_02054e54(self + 0x64);
    func_0209d34c((unsigned short *) (self + 0x166));
    func_0209d11c(self + 0x168);
    __cxa_vec_ctor(self + 0x1d0, 0x2, 0xc, (void *) func_020012e8, (void *) func_020012dc);
    *(int *) (self + 0x15c) = -0x1;
    *(void **) (self + 0x160) = 0x0;
    func_0209d0a4(self + 0x168);
    *(u8 *) (self + 0x1c6) = 0x0;
    *(u8 *) (self + 0x1c7) = 0x1;
    *(u8 *) (self + 0x1f1) = 0x0;
    *(u16 *) (self + 0x1c4) = 0x0;
    for (i = 0; i < 0x4; i++) {
        *(void **) (self + (i << 2) + 0x54) = 0x0;
    }
    return self;
}
