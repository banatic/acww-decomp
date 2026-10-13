/* func_ov004_02228bac @ 0x02228bac, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0200f328(void *, int);
extern void func_020109a0(void *, int, int, int);

int func_ov004_02228bac(char *self)
{
    // DECLS
    // ENDDECLS
    *(u16 *) (self + 0x7d4) = (*(short *) (self + 0x8e) - 0x4000);
    func_020109a0(self, 0x26, 0x0, 0x0);
    return func_0200f328(self, 0x4c9);
}
