/* func_ov004_02236078 @ 0x02236078, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void *func_ov004_02236078(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self + 0x20c) = 0x0;
    if (*(int *) (self + 0x158) >= *(u8 *) (self + 0x203)) {
        *(void **) (self + 0x158) = 0x0;
        *(u8 *) (self + 0x1ee) = 0x2;
        return self;
    }
    return self;
}
