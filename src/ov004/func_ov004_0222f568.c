/* func_ov004_0222f568 @ 0x0222f568, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0222f6e8(void *, int);

void func_ov004_0222f568(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x24c) == 0x2) {
        func_ov004_0222f6e8(self, 0x4);
    }
}
