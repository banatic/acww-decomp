/* func_ov004_022287b4 @ 0x022287b4, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_02228850(void *, int, int);

void func_ov004_022287b4(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if ((u32) (*(int *) (self + 0x7f0) - 0x29) > (u32) 0x1) {
        if (*(int *) (self + 0x7f0) == 0x2c) {
            *(u16 *) (self + 0xc84) = a1;
        } else {
            func_ov004_02228850(self, 0x6, a1);
        }
    }
}
