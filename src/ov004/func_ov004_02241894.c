/* func_ov004_02241894 @ 0x02241894, 0xa8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_02241680(void *self, void *p);
extern void func_ov004_0224173c(void *self, void *p);
extern void func_ov004_02241588(void *self, void *p);
extern void func_ov004_022417f8(void *self);
extern int func_020644cc(int);
extern u8 data_ov004_02259a24;

void func_ov004_02241894(char *self)
{
    switch (*(short *) (self + 0x172)) {
        case 3:
            func_ov004_02241588(self, self + 0x168);
            return;
        case 2:
            func_ov004_0224173c(self, self + 0x168);
            return;
        case 1:
            func_ov004_02241680(self, self + 0x168);
            return;
    }

    if (*(signed char *) (self + 0x196) == 9) {
        func_ov004_022417f8(self);
        return;
    }
    if (*(u8 *) (self + 0x22) != 0) {
        if ((int) data_ov004_02259a24 % 0x14 != 0) {
            return;
        }
        if (func_020644cc(0x64) < 0x46) {
            return;
        }
    } else {
        if ((int) data_ov004_02259a24 % 0x28 != 0) {
            return;
        }
        if (func_020644cc(0x64) < 0x55) {
            return;
        }
    }
    if (func_020644cc(0x64) < 0x32) {
        *(short *) (self + 0x172) = 3;
    } else {
        *(short *) (self + 0x172) = 2;
    }
}
