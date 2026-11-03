/* telephone_4: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02211b7c @ 0x02211b7c, 0x4 bytes, Thumb
 * func_ov004_02211b54 @ 0x02211b54, 0x26 bytes, Thumb
 * func_ov004_02211b40 @ 0x02211b40, 0x14 bytes, Thumb
 */

#include "types.h"

extern int func_ov004_022118bc(int a, int b);
extern const u8 data_ov004_02247684[];

int func_ov004_02211b7c(void)
{
    return 1;
}

void func_ov004_02211b54(int a, int b)
{
    switch (b) {
        case 0:
        case 1:
            func_ov004_022118bc(a, 1);
            break;
        case 8:
            func_ov004_022118bc(a, 0);
            break;
    }
}

u8 func_ov004_02211b40(void *self, unsigned int i)
{
    if (i < 4) {
        return data_ov004_02247684[i];
    }
    return 0;
}
