/* func_ov003_0222ba8c @ 0x0222ba8c, 0x80 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off

extern int func_ov003_0222791c(int a, int b);
extern int func_ov003_0222793c(int a, int b);

void func_ov003_0222ba8c(char *self)
{
    *(short *) (self + 0x138) += (short) func_ov003_0222791c(0, 0x2aa8);
    *(int *) (self + 0x13c) = 0;
    *(u16 *) (self + 0x140) = (u8) func_ov003_0222793c(1, 3);
    *(short *) (self + 0x142) = (short) func_ov003_0222791c(0xaaa, 0x2000);
    *(u8 *) (self + 0x210) = func_ov003_0222791c(0, 2) ? 1 : 0;
    *(u8 *) (self + 0x200) = 1;
}
