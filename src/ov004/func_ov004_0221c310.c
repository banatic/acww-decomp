/* func_ov004_0221c310 @ 0x0221c310, 0x7c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020644cc(int);
extern int func_02019c90(void *p, int a, int b, int c);
extern int func_ov004_0221c844(void *self, int a);
extern u16 data_020c80f8;

void func_ov004_0221c310(char *self)
{
    if (*(u8 *) (self + 0xa53) != 0) {
        *(u8 *) (self + 0xa53) = (u8) (*(u8 *) (self + 0xa53) - 1);
    }
    switch (*(u8 *) (self + 0xa53)) {
        case 0x28:
            if (func_020644cc(2) == 0) {
                func_02019c90(self + 0x564, 1, 0xa, data_020c80f8);
            } else {
                func_02019c90(self + 0x564, 1, 0x17, data_020c80f8);
            }
            break;
        case 1:
            func_02019c90(self + 0x564, 1, 0, data_020c80f8);
            break;
        case 0:
            func_ov004_0221c844(self, 0);
            break;
    }
}
