/* func_ov004_0222b1d8 @ 0x0222b1d8, 0x22 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02077910(void *, int);
extern void func_020779b8(void *, int, int, int);

void func_ov004_0222b1d8(char *self, int a1, int a2, int a3)
{
    // DECLS
    char frame[0x4];
    // ENDDECLS
    func_020779b8(self, a1, a2, a3);
    func_02077910(self + 0x5, a3);
    *(u8 *) (self + 0x7) = *(u8 *) (frame + 0x10);
}
