/* func_ov004_022322fc @ 0x022322fc, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020b7ee8(void *);

void *func_ov004_022322fc(char *self)
{
    // DECLS
    // ENDDECLS
    func_020b7ee8(self);
    *(u8 *) (self + 0x20) = 0x0;
    return self;
}
