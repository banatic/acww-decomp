/* func_ov004_02237d04 @ 0x02237d04, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_022354e0(void *);

void func_ov004_02237d04(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x1e8) = *(int *) (self + 0x15c);
    *(u8 *) (self + 0x1c7) = 0x0;
    func_ov004_022354e0(self);
}
