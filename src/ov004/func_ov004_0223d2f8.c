/* func_ov004_0223d2f8 @ 0x0223d2f8, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void __cxa_vec_ctor();
extern void func_ov004_0223d2b0();
extern void func_020051b0();
extern void func_02034ce0();

void *func_ov004_0223d2f8(char *self)
{
    // DECLS
    u32 i;
    // ENDDECLS
    __cxa_vec_ctor(self + 0x8, 0x2, 0x2, (void *) func_02034ce0, (void *) func_020051b0);
    func_ov004_0223d2b0(self);
    for (i = 0; i < 0x2; i++) {
        *(void **) (self + (i << 2) + 0x14) = 0x0;
        *(void **) (self + (i << 2) + 0x1c) = 0x0;
    }
    return self;
}
