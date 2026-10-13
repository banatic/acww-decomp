/* func_ov004_02226db4 @ 0x02226db4, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020109a0(void *, int, int, int);
extern int func_02056fcc(void *, int, int, int, int);
extern int func_ov004_02230ce4(int);
extern int func_ov004_022318f8(int);

int func_ov004_02226db4(char *self)
{
    // DECLS
    // ENDDECLS
    func_020109a0(self, 0x78, 0x3, 0x0);
    return func_ov004_02230ce4(
        func_ov004_022318f8(func_02056fcc(self + 0x2d0, ((u32) (*(int *) (self + 0x2d4) << 4) >> 16), 0x3, 0x1000,
                                          (u16) (((u32) (*(int *) (self + 0x2d4) << 4) >> 16) - 0x1))));
}
