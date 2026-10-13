/* func_ov004_0220d300 @ 0x0220d300, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0220e5c8();

int func_ov004_0220d300(char *self, int a1)
{
    // DECLS
    int v1;
    u8 v2;
    // ENDDECLS
    v1 = func_ov004_0220e5c8(a1, a1);
    if (v1 == 0x0) {
        v2 = *(u8 *) (self + 0x1);
        *(u8 *) (self) = v2;
        return v2;
    }
    return v1;
}
