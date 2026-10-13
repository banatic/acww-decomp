/* func_ov004_0223d044 @ 0x0223d044, 0xe bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov004_0223d044(char *self)
{
    // DECLS
    // ENDDECLS
    return *(int *) (self + ((*(u8 *) (self + 0xc) & 0x1) << 2) + 0x1c);
}
