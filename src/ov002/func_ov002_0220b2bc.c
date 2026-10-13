/* func_ov002_0220b2bc @ 0x0220b2bc, 0x12 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov002_0220b2bc(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if ((*(u8 *) (self + 0x78) & a1) != 0x0) {
        return 0x1;
    }
    return 0x0;
}
