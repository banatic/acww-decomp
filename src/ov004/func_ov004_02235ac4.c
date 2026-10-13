/* func_ov004_02235ac4 @ 0x02235ac4, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char *data_ov004_022594d4[];

void func_ov004_02235ac4(char *self)
{
    u8 i;
    *(u8 *) (self + 0x1ea) = 0;
    *(u8 *) (self + 0x1c9) = 0;
    *(s16 *) (self + 0x1ec) = *(s16 *) (self + 0x1c0);
    i = *(u8 *) (self + 0x1e8);
    if (i != *(volatile int *) (self + 0x15c)) {
        char *e = data_ov004_022594d4[i];
        if (e != 0) {
            *(u8 *) (e + 0x1c9) = 0;
        }
        *(u8 *) (self + 0x1e8) = (u8) * (volatile int *) (self + 0x15c);
        *(u8 *) (self + 0x1e9) = (u8) * (volatile int *) (self + 0x15c);
    }
}
