/* func_ov002_02209d08 @ 0x02209d08, 0x2e bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov002_02209d38(void *, int, int, int);

void func_ov002_02209d08(char *self, int a1, int a2, int a3)
{
    // DECLS
    // ENDDECLS
    if (a3 == 0x1) {
        func_ov002_02209d38(self, a1, a2, 0x1);
    } else {
        *(u8 *) (self + 0x15) = 0x3;
        *(int *) (self + 0xc) = (((a1 << 4) - *(int *) (self + 0x4)) >> 1);
        *(int *) (self + 0x10) = (((a2 << 4) - *(int *) (self + 0x8)) >> 1);
        *(u8 *) (self + 0x14) = a3;
    }
}
