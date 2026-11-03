/* room_object_02251690: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022132bc @ 0x022132bc, 0x38 bytes, Thumb
 * func_ov004_022132a4 @ 0x022132a4, 0x18 bytes, Thumb
 * func_ov004_02213270 @ 0x02213270, 0x34 bytes, Thumb
 */

#include "types.h"

extern void func_02004044(void *dst, int *v);
extern void func_0200403c(void *);
extern int func_ov004_0220fdc8(void *self, int parameter1, int parameter2);
extern void *func_ov004_0220fde0(void *self);
extern int func_ov004_0223a750(void *p);
extern void func_0200408c(void *p, int a);
extern u16 data_ov004_0224fd38;

int func_ov004_022132bc(char *self)
{
    int t[3];

    t[0] = *(int *) (self + 0x7b8);
    t[1] = *(int *) (self + 0x7bc);
    t[2] = *(int *) (self + 0x7c0);
    func_02004044(self + 0x844, t);
    return 1;
}

int func_ov004_022132a4(char *self)
{
    // DECLS
    // ENDDECLS
    func_0200403c(self + 0x844);
    return 0x1;
}

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
