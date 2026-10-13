/* func_ov004_0221c39c @ 0x0221c39c, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 data_020c80f8;
extern void func_02019c90(void *p, int a, int b, u16 c);
extern void func_ov004_0221c844(void *self, int a);

void func_ov004_0221c39c(char *self)
{
    if (*(u8 *) (self + 0xa53) != 0) {
        *(u8 *) (self + 0xa53) = *(u8 *) (self + 0xa53) - 1;
    }

    switch (*(u8 *) (self + 0xa53)) {
        case 0x14:
            func_02019c90(self + 0x564, 1, 3, data_020c80f8);
            break;
        case 1:
            func_02019c90(self + 0x564, 1, 0, data_020c80f8);
            break;
        case 0:
            func_ov004_0221c844(self, 0);
            break;
    }
}
