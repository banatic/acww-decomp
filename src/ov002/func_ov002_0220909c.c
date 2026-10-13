/* func_ov002_0220909c @ 0x0220909c, 0x12 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov002_0220909c(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x1e) != 0x0) {
        *(u8 *) (self + 0x1e) = (*(u8 *) (self + 0x1e) - 0x1);
        return 0x0;
    }
    return 0x1;
}
