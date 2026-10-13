/* func_ov004_0220d9a4 @ 0x0220d9a4, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0220d938(void *);

void *func_ov004_0220d9a4(char *self)
{
    // DECLS
    // ENDDECLS
    *(u16 *) (self + 0x2) = 0xfff1;
    func_ov004_0220d938(self);
    return self;
}
