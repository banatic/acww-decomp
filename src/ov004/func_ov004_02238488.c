/* func_ov004_02238488 @ 0x02238488, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov004_02238488(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x158) >= *(u8 *) (self + 0x20c)) {
        *(u8 *) (self + 0x20e) = 0x3;
        *(void **) (self + 0x158) = 0x0;
    }
    *(int *) (self + 0x110) = *(int *) (self + 0x208);
}
