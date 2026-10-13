/* func_ov002_02209178 @ 0x02209178, 0x24 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0200277c(int);
extern void func_ov002_02208df8(void *);

void func_ov002_02209178(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x17) = 0x0;
    if (*(u8 *) (self + 0x16) != 0x0) {
        func_0200277c(*(u8 *) (self + 0x1a));
        *(u8 *) (self + 0x16) = 0x0;
    }
    func_ov002_02208df8(self);
}
