/* func_ov004_0221bad0 @ 0x0221bad0, 0x128 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0221b98c(void *self);
extern void *func_020e98b4(int size);
extern u8 *data_ov004_02257918;

int func_ov004_0221bad0(char *self)
{
    unsigned i;
    int n;
    u8 *table;

    if (func_ov004_0221b98c(self) == 0) {
        n = *(int *) (self + 0x168);
        *(u16 **) (self + 0x164) = (u16 *) func_020e98b4(n << 1);
        if (*(void **) (self + 0x164) != 0) {
            switch (*(int *) (self + 0x15c)) {
                case 0:
                    for (i = 0; i < *(unsigned *) (self + 0x168); i++) {
                        table = data_ov004_02257918;
                        (*(u16 **) (self + 0x164))[i] = (table[i] < 0x38) ? (u16) (table[i] + 0x12b0) : 0x12b0;
                    }
                    return 1;
                case 1:
                    for (i = 0; i < *(unsigned *) (self + 0x168); i++) {
                        table = data_ov004_02257918;
                        (*(u16 **) (self + 0x164))[i] = (table[i] < 0x38) ? (u16) (table[i] + 0x12e8) : 0x12e8;
                    }
                    return 1;
                case 2:
                    for (i = 0; i < *(unsigned *) (self + 0x168); i++) {
                        table = data_ov004_02257918;
                        (*(u16 **) (self + 0x164))[i] = (table[i] < 0x14) ? table[i] * 4 + 0x3894 : 0x3894;
                    }
                    return 1;
                case 3:
                    for (i = 0; i < *(unsigned *) (self + 0x168); i++) {
                        table = data_ov004_02257918;
                        (*(u16 **) (self + 0x164))[i] = (table[i] < 0x34) ? table[i] * 4 + 0x450c : 0x450c;
                    }
                    return 1;
                default:
                    return 0;
            }
        }
        return 0;
    }
    return 1;
}
