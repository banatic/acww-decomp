/* func_ov004_0221c040 @ 0x0221c040, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020644cc(int);
extern void func_0206844c(int h, u8 *p, int k);
extern void func_ov004_0221c844(void *self, int a);

void func_ov004_0221c040(char *self)
{
    u8 m;
    m = (u8) (func_020644cc(2) + 0x11);
    func_0206844c(*(int *) (self + 0x8e0), &m, 0);
    func_ov004_0221c844(self, 6);
}
