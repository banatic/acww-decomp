/* func_ov002_0220b7ec @ 0x0220b7ec, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov002_0220b6f4(void *);

int func_ov002_0220b7ec(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b6f4(self);
    *(u8 *) (self + 0x118) = 0x2;
    return 0x118;
}
