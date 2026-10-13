/* func_ov097_022a28e4 @ 0x022a28e4, 0x70 bytes, Thumb, module ov097
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov097_022a27c0(u8 *self, u16 arg);
extern void func_ov002_02208d4c(void *p, int a, int b);

void func_ov097_022a28e4(u8 *self, u16 arg)
{
    volatile u16 id;

    if (func_ov097_022a27c0(self, arg) == 0) {
        return;
    }
    id = arg;
    {
        unsigned int ok = 0;
        u16 hi = id;
        u16 lo = id;
        if (lo >= 0x1144 && hi <= 0x1187) {
            ok = 1;
        }
        if (ok > 0) {
            func_ov002_02208d4c(self + 0x294c, 0xc, 0x13);
        } else if (hi >= 0x1100 && hi <= 0x1143) {
            func_ov002_02208d4c(self + 0x294c, 0xb, 0x12);
        }
    }
}
