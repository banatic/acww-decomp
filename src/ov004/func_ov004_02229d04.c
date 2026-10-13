/* func_ov004_02229d04 @ 0x02229d04, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020109a0(void *, int, int, int);

int func_ov004_02229d04(char *self)
{
    // DECLS
    // ENDDECLS
    func_020109a0(self, 0x1d, 0x3, 0x0);
    *(u8 *) (self + 0x7d4) = 0x0;
    return 0x7d4;
}
