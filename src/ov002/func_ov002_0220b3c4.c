/* func_ov002_0220b3c4 @ 0x0220b3c4, 0x2c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02070c08(void *);
extern void *data_ov002_0220bd18;

void *func_ov002_0220b3c4(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov002_0220bd18;
    func_02070c08(self + 0x4);
    *(void **) (self + 0x70) = 0x0;
    *(u8 *) (self + 0x75) = 0x0;
    *(u8 *) (self + 0x78) = 0x0;
    return self;
}
