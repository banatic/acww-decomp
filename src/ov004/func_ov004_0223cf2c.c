/* func_ov004_0223cf2c @ 0x0223cf2c, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02004330(void *, int, int);

void func_ov004_0223cf2c(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x1c) != 0x0) {
        func_02004330(self, a1, *(u8 *) (self + 0x1c));
    }
}
