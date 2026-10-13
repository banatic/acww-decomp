/* func_ov002_0220b29c @ 0x0220b29c, 0xe bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov002_0220b29c(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x78) = (*(u8 *) (self + 0x78) & ~a1);
}
