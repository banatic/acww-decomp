/* func_ov004_0222bd40 @ 0x0222bd40, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0222bdf0(void *, int, int, int);

void func_ov004_0222bd40(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x7f0) == 0x8) {
        *(u16 *) (self + 0xc84) = a1;
    } else {
        func_ov004_0222bdf0(self, 0x0, 0x6, a1);
    }
}
