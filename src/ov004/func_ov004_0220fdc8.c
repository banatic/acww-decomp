/* func_ov004_0220fdc8 @ 0x0220fdc8, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov004_0220fdc8(char *self, int a1, int a2)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x77c) = a2;
    *(u8 *) (self + 0x77d) = 0x0;
    return 0x1;
}
