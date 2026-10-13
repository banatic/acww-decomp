/* func_ov004_0222b2a4 @ 0x0222b2a4, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02056f94(void *);
extern int func_ov004_0222bdf0(void *, int, int, int);

void func_ov004_0222b2a4(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_02056f94(self + 0x2d0) != 0x0 && func_ov004_0222bdf0(self, 0x0, 0x6, -0x1) != 0x0) {
        *(u8 *) (self + 0x8ea) = 0x0;
        return;
    }
}
