/* func_ov004_022199a8 @ 0x022199a8, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0220d030(void *);
extern int func_ov004_0220e4b0(void *);
extern void func_ov004_0220ffbc(void *);
extern void func_ov004_02219884(void *);

int func_ov004_022199a8(char *self)
{
    // DECLS
    u32 i;
    // ENDDECLS
    func_ov004_0220d030(self + 0x84c);
    func_ov004_02219884(self);
    *(int *) (self + 0x5e4) = *(int *) (self + 0x848);
    for (i = 0; i < 0x4; i++) {
        if (func_ov004_0220e4b0(self + 0x7c4 + (i << 5)) != 0x0) {
            *(int *) (self + (i << 5) + 0x7d4) = *(int *) (self + 0x848);
        }
    }
    func_ov004_0220ffbc(self);
    return 0x1;
}
