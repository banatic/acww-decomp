/* func_ov002_02209c08 @ 0x02209c08, 0x38 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02070c2c(void *);
extern void *data_ov002_0220bba8;

void *func_ov002_02209c08(char *self)
{
    // DECLS
    // ENDDECLS
    func_02070c2c(self);
    *(void **) (self) = &data_ov002_0220bba8;
    *(u8 *) (self + 0x6e) = 0x3;
    *(u16 *) (self + 0x6c) = 0x0;
    *(u8 *) (self + 0x6f) = 0x1;
    *(u8 *) (self + 0x70) = 0x9;
    return self;
}
