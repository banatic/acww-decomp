/* func_ov004_0221bce0 @ 0x0221bce0, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0221b4e4(void);
extern int func_ov004_0221b98c(void *self);
extern int func_020b6590(void);
extern void func_020b7d84(int a, void *b, void *c, int d, int e, int f);

int func_ov004_0221bce0(char *self)
{
    func_ov004_0221b4e4();
    if (!func_ov004_0221b98c(self)) {
        func_020b7d84(func_020b6590(), self + 0x138, self + 0x5c, 0xc00, 0xe, *(u8 *) (self + 0x154));
    }
    return 1;
}
