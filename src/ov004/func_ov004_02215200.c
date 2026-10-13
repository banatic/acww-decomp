/* func_ov004_02215200 @ 0x02215200, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020040a4();

int func_ov004_02215200(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x858) != 0x0) {
        return func_020040a4(self + 0x844, 0x844);
    }
    return 0x0;
}
