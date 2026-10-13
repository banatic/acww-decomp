/* func_ov004_0223cf68 @ 0x0223cf68, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02004328(void *, int);

void func_ov004_0223cf68(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x1c) != 0x0) {
        func_02004328(self, *(u8 *) (self + 0x1c));
        *(u8 *) (self + 0x1c) = 0x0;
    }
}
