/* func_ov004_0223b18c @ 0x0223b18c, 0x2a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_02055210(void *);

void *func_ov004_0223b18c(char *self)
{
    // DECLS
    // ENDDECLS
    func_02055210(self + 0x2c);
    *(void **) (self + 0x10) = 0x0;
    *(void **) (self + 0x24) = 0x0;
    *(void **) (self + 0x28) = 0x0;
    *(void **) (self + 0x18) = 0x0;
    *(void **) (self + 0x1c) = 0x0;
    *(void **) (self + 0x20) = 0x0;
    *(void **) (self + 0x14) = 0x0;
    *(u8 *) (self) = 0x0;
    *(void **) (self + 0x4) = 0x0;
    *(void **) (self + 0x8) = 0x0;
    *(void **) (self + 0xc) = 0x0;
    return self;
}
