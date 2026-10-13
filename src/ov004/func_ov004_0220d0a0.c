/* func_ov004_0220d0a0 @ 0x0220d0a0, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0220d220(char *p, int a, int b, int c);
extern int data_ov004_0224fdf8[];

int func_ov004_0220d0a0(char *self, int a1, int a2)
{
    unsigned i;
    u8 *flag;
    int v;

    *(u8 *) (self + 0x54) = 0;
    flag = (u8 *) (self + 0x54);
    for (i = 0; i < 3; i++) {
        v = *flag | func_ov004_0220d220(self + 0x1c * i, a1, data_ov004_0224fdf8[i], a2);
        *flag = (u8) ((v != 0) ? 1 : 0);
    }
    return *(u8 *) (self + 0x54);
}
