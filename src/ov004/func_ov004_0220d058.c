/* func_ov004_0220d058 @ 0x0220d058, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0220d208(char *p, int a, int b, int c);

int func_ov004_0220d058(char *self, int a1, int a2, int a3)
{
    int r = 0;
    char *p;

    if (*(u8 *) (self + 0x54) != 0) {
        for (p = self; p < self + 0x54; p += 0x1c) {
            r |= func_ov004_0220d208(p, a1, a2, a3);
            r = (r != 0) ? 1 : 0;
        }
    }
    return r;
}
