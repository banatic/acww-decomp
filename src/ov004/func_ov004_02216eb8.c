/* func_ov004_02216eb8 @ 0x02216eb8, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0203e020(void *, int);

void func_ov004_02216eb8(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x860) == 0x0) {
        func_0203e020(self, *(u8 *) (self + 0x860));
    }
}
