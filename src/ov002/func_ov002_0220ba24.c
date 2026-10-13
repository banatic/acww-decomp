/* func_ov002_0220ba24 @ 0x0220ba24, 0x2c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02066a04(void *);
extern void func_ov002_02207e40(void *);

void *func_ov002_0220ba24(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov002_02207e40(self);
    func_02066a04(self + 0xd0);
    *(u8 *) (self + 0x118) = 0x3;
    *(u8 *) (self + 0x119) = 0x0;
    return self;
}
