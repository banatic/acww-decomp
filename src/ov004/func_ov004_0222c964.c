/* func_ov004_0222c964 @ 0x0222c964, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02055060(void *, int, int, int, int, int);
extern int func_ov004_0222c2dc(void *, int);
extern int func_ov004_0222c3c4(void *, int);

int func_ov004_0222c964(char *self)
{
    // DECLS
    // ENDDECLS
    func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 0x2), 0x1, 0x1000, 0x0, 0x0);
    func_ov004_0222c2dc(self + 0x250, 0x4d9);
    *(u8 *) (self + 0x374) = 0x0;
    return 0x1;
}
