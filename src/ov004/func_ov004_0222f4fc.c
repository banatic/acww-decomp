/* func_ov004_0222f4fc @ 0x0222f4fc, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0203e020(void *);

void func_ov004_0222f4fc(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x24c) == 0x0) {
        func_0203e020(self);
    }
}
