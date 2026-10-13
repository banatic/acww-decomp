/* func_ov004_0221b020 @ 0x0221b020, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020b6590(int);
extern void func_020b7d84(int, void *, void *, int, int, int);
extern int func_ov004_0221ae00(void *);

int func_ov004_0221b020(char *self)
{
    // DECLS
    // ENDDECLS
    func_020b7d84(func_020b6590(func_ov004_0221ae00(self)), self + 0x138, self + 0x5c, *(int *) (self + 0x158), 0x10,
                  *(u8 *) (self + 0x154));
    return 0x1;
}
