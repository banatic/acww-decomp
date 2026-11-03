/* chest_4: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022176e4 @ 0x022176e4, 0x4 bytes, Thumb
 * func_ov004_022176c0 @ 0x022176c0, 0x24 bytes, Thumb
 * func_ov004_022176ac @ 0x022176ac, 0x14 bytes, Thumb
 */

#include "types.h"

extern int func_ov004_0220ce20(char *self);
extern const u8 data_ov004_02247680[];

int func_ov004_022176e4(void)
{
    return 1;
}

int func_ov004_022176c0(char *self)
{
    int r;
    if (func_ov004_0220ce20(self) != 0 && *(int *) (self + 0x864) == 0) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}

u8 func_ov004_022176ac(void *self, unsigned int i)
{
    if (i < 4) {
        return data_ov004_02247680[i];
    }
    return 0;
}
