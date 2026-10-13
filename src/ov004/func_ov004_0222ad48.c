/* func_ov004_0222ad48 @ 0x0222ad48, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02056f94();
extern int func_ov004_0222bdf0();

int func_ov004_0222ad48(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_02056f94(self + 0x2d0);
    if (v1 != 0x0) {
        return func_ov004_0222bdf0(self, *(u8 *) (self + 0x7de), 0x6, -0x1);
    }
    return v1;
}
