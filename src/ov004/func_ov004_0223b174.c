/* func_ov004_0223b174 @ 0x0223b174, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_020551e0(void *);

void *func_ov004_0223b174(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self) = 0x0;
    func_020551e0(self + 0x2c);
    return self;
}
