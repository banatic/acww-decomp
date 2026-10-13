/* func_ov004_02215228 @ 0x02215228, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020040ac(void *, int, int);

void func_ov004_02215228(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x858) != 0x0) {
        func_020040ac(self + 0x844, a1, 0x844);
    }
}
