/* func_ov004_02213270 @ 0x02213270, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0220fdc8(void *self, int parameter1, int parameter2);
extern void *func_ov004_0220fde0(void *self);
extern int func_ov004_0223a750(void *p);
extern void func_0200408c(void *p, int a);
extern u16 data_ov004_0224fd38;

int func_ov004_02213270(char *self, int arg1, int arg2)
{
    int r;

    func_ov004_0220fdc8(self, arg1, arg2);
    r = func_ov004_0223a750(func_ov004_0220fde0(self));
    if (r != data_ov004_0224fd38) {
        func_0200408c(self + 0x844, r);
    }
    return 1;
}
