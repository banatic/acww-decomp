/* func_ov004_0220f994 @ 0x0220f994, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02032180(void *);
extern void func_ov004_0220dfe0(void *);
extern int func_ov004_0220e5c8(void *);

void func_ov004_0220f994(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_ov004_0220e5c8(self) == 0x0 && *(u8 *) (self + 0x78c) == 0x0) {
        func_02032180(self + 0x62c);
        func_ov004_0220dfe0(self + 0x62c);
        return;
    }
}
