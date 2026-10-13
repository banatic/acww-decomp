/* func_ov004_0223cf18 @ 0x0223cf18, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02004320(void *, int, int);

void func_ov004_0223cf18(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x1c) != 0x0) {
        func_02004320(self, a1, *(u8 *) (self + 0x1c));
    }
}
