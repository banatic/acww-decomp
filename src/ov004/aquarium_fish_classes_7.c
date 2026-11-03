/* aquarium_fish_classes_7: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02238fe4 @ 0x02238fe4, 0x3e bytes, Thumb
 * func_ov004_02238fb4 @ 0x02238fb4, 0x30 bytes, Thumb
 * func_ov004_02238f70 @ 0x02238f70, 0x44 bytes, Thumb
 */

#include "types.h"

extern void func_ov004_02238f14(void *);
extern void func_ov004_02238eb0(void *);
extern char *data_ov004_022594d4[];

void func_ov004_02238f70(char *self);

void func_ov004_02238fe4(short *out, u8 *flag, int *ctr, int lim, int mul)
{
    int v;
    if (*flag != 0) {
        *ctr = *ctr + 1;
    } else {
        *ctr = *ctr - 1;
    }
    v = (short) (*ctr * mul);
    if (v >= lim) {
        v = lim;
        *flag = 0;
    } else if (v <= 0) {
        v = 0;
        *flag = 1;
    }
    *out = v;
}

void func_ov004_02238fb4(char *self)
{
    switch (*(u8 *) (self + 0x281)) {
        case 1:
            func_ov004_02238f70((char *) self);
            break;
        case 2:
            func_ov004_02238f14(self);
            break;
        case 3:
            func_ov004_02238eb0(self);
            break;
    }
}

void func_ov004_02238f70(char *self)
{
    char *p = data_ov004_022594d4[*(u8 *) (self + 0x1e8)];
    if (p != 0) {
        *(short *) (self + 0x282) = *(short *) (p + 0x1c0) + 0x4000;
    }
    *(char *) (self + 0x281) = 2;
    *(int *) (self + 0x158) = 0;
}
