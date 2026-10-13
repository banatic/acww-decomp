/* func_ov004_02216f50 @ 0x02216f50, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_02217124(void *, int);

void func_ov004_02216f50(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x860) == 0x2) {
        func_ov004_02217124(self, 0x4);
    }
}
