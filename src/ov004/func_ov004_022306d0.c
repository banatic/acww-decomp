/* func_ov004_022306d0 @ 0x022306d0, 0x80 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02055060(void *, int, int, int, int, int);
extern void func_02056478(void *, int, int, int, int);
extern int func_ov004_0222c3a4(void *, int);
extern int func_ov004_0222c3c4(void *);

int func_ov004_022306d0(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x6d4) = 0x1;
    *(u8 *) (self + 0x6b0) = 0x0;
    *(u8 *) (self + 0x6b1) = 0x1;
    *(u8 *) (self + 0x6b2) = 0x0;
    func_02055060(self + 0x400, func_ov004_0222c3c4(self + 0x600), 0x1, 0x1000, 0x0, 0x0);
    func_02056478(self + 0x6b4, func_ov004_0222c3a4(self + 0x55c, 0x0), 0x1, 0x1000, 0x0);
    return 0x1;
}
