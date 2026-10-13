/* func_ov004_02227f90 @ 0x02227f90, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0200f328(void *, int);
extern void func_020109a0(void *, int, int, int);
extern int func_02056fcc(void *, int, int, int, int);
extern int func_02057cf4(int);
extern void func_02057d0c(int, void *);

int func_ov004_02227f90(char *self)
{
    // DECLS
    // ENDDECLS
    func_020109a0(self, 0x2e, 0x3, 0x0);
    func_02057d0c(func_02057cf4(func_02056fcc(self + 0x2d0, ((u32) (*(int *) (self + 0x2d4) << 4) >> 16), 0x3, 0x1000,
                                              (u16) (((u32) (*(int *) (self + 0x2d4) << 4) >> 16) - 0x1))),
                  self);
    return func_0200f328(self, 0x52);
}
