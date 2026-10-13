/* func_ov004_022151d8 @ 0x022151d8, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0200409c();

int func_ov004_022151d8(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x858) != 0x0) {
        return func_0200409c(self + 0x844, 0x844);
    }
    return -0x1;
}
