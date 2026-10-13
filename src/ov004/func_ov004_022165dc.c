/* func_ov004_022165dc @ 0x022165dc, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020356c4(int a, u16 b, int c, int d);
extern void func_02060b34(u16 *p);

void func_ov004_022165dc(char *self, unsigned k)
{
    u16 t;

    if (*(u8 *) (self + 0x844) == 0 && k < 0x46) {
        func_020356c4(0x11, (u16) (k + 0xb0), 0x7f, 0);
        t = k < 0x46 ? (u16) (0x1323 + k) : 0x1323;
        func_02060b34(&t);
        *(u8 *) (self + 0x844) = 1;
    }
}
