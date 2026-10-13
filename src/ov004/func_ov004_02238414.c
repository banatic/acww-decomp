/* func_ov004_02238414 @ 0x02238414, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void *func_ov004_02238414(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self + 0x110) = 0x0;
    if (*(int *) (self + 0x158) >= *(u8 *) (self + 0x20d)) {
        *(u8 *) (self + 0x20e) = 0x0;
        *(void **) (self + 0x158) = 0x0;
        return self;
    }
    return self;
}
