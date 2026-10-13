/* func_ov004_0223d054 @ 0x0223d054, 0xe bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov004_0223d054(char *self)
{
    // DECLS
    // ENDDECLS
    return *(int *) (self + ((*(u8 *) (self + 0xc) & 0x1) << 2) + 0x14);
}
