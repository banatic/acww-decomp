/* func_ov004_0220bf00 @ 0x0220bf00, 0xb4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0206837c(u32);
extern int func_020ab504(int);
extern int func_020984e8(void);
extern int func_020996a0(int);
extern u16 *func_020adf50(int);
extern int func_020adde4(u16);
extern void func_0206844c(u32, void *, u32);
extern u32 data_ov004_0224fbe0;

void func_ov004_0220bf00(void *self)
{
    u8 arr[4];
    u8 b = *(u8 *) ((char *) self + 0x10a);
    int r = func_020ab504(func_0206837c(*(u32 *) ((char *) self + 0x12c)));

    if (b != 0 && b != 7) {
        return;
    }

    switch (r) {
        case 0:
            if (func_020adde4(*(u16 *) func_020adf50(func_020996a0(func_020984e8()))) == 0) {
                arr[0] = 1;
                func_0206844c(*(u32 *) ((char *) self + 0x12c), &arr[0], data_ov004_0224fbe0);
            } else {
                arr[1] = 2;
                func_0206844c(*(u32 *) ((char *) self + 0x12c), &arr[1], data_ov004_0224fbe0);
            }
            break;
        case 1:
            arr[2] = 6;
            func_0206844c(*(u32 *) ((char *) self + 0x12c), &arr[2], data_ov004_0224fbe0);
            break;
        case 2:
            arr[3] = 4;
            func_0206844c(*(u32 *) ((char *) self + 0x12c), &arr[3], data_ov004_0224fbe0);
            break;
    }
}
