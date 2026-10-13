/* func_ov004_02239700 @ 0x02239700, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_02239790(void *, int, int, int);

void func_ov004_02239700(char *self)
{
    // DECLS
    // ENDDECLS
    if ((u32) (*(int *) (self + 0x15c) - 0x2d) <= (u32) 0x1) {
        func_ov004_02239790(self, *(int *) (self + 0x224), *(int *) (self + 0x1cc), *(int *) (self + 0x228));
    } else {
        if (*(u8 *) (self + 0x1e8) == *(int *) (self + 0x15c)) {
            func_ov004_02239790(self, *(int *) (self + 0x224), *(int *) (self + 0x1cc), *(int *) (self + 0x228));
        } else {
            func_ov004_02239790(self, 0x7b, 0x5000, *(int *) (self + 0x228));
        }
    }
}
