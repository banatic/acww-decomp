/* func_ov004_02227580 @ 0x02227580, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020109a0(void *, int, int, unsigned short d);

void func_ov004_02227580(char *self, void *message, int previous)
{
    // DECLS
    // ENDDECLS
    func_020109a0(self, 0x40, 0x0, 0x0);
    *(u8 *) (self + 0x8e9) = 0x0;
    return;
}
