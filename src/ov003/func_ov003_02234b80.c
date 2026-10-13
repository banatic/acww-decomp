/* func_ov003_02234b80 @ 0x02234b80, 0x144 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov003_02235b54(void *self, int a, int b);
extern void func_ov003_022349a0(void *self);
extern void func_ov003_022355d4(void *self);
extern void func_02056fcc(void *p, int a, int b, int c, int d);
extern void func_ov003_022348dc(void *self, int a);
extern int func_ov003_022350cc(void *self);
extern int func_ov003_02235834(void *self, int a, int b);

void func_ov003_02234b80(char *self)
{
    short n;
    short v;
    int *s;
    int *d;

    n = *(short *) (self + 0x232);
    if (n > 0x8c) {
        *(u8 *) (self + 0x251) = 9;
    } else if (func_ov003_02235b54(self, 0x50, 0xe38) != 0) {
        *(short *) (self + 0x232) = n + 1;
    } else {
        *(short *) (self + 0x232) = 0;
    }
    switch (*(u8 *) (self + 0x251)) {
        case 0:
            func_ov003_022349a0(self);
            break;
        case 6:
            func_ov003_022355d4(self);
            break;
        case 9:
        case 0xb:
            if (((u32) * (int *) (self + 0xf0) << 4) >> 16 > 9) {
                func_02056fcc(self + 0xec, 9, 0, 0x1000, 0);
            }
            func_ov003_022348dc(self, 0x1ccd);
            break;
        case 7:
            *(u8 *) (self + 0x251) = 0;
            *(short *) (self + 0x23a) = *(short *) (self + 0x23a) + *(short *) (self + 0x240);
            v = *(short *) (self + 0x23a);
            if (func_ov003_02235834(self, v, func_ov003_022350cc(self)) != 0) {
                s = (int *) (self + 0x204);
                d = (int *) (self + 0x1c8);
                d[0] = s[0];
                d[1] = s[1];
                d[2] = s[2];
            }
            break;
        case 0x13:
            *(u8 *) (self + 0x24a) = 0;
            *(u8 *) (self + 0x251) = 0;
            v = *(short *) (self + 0x23a);
            if (func_ov003_02235834(self, v, func_ov003_022350cc(self)) != 0) {
                s = (int *) (self + 0x204);
                d = (int *) (self + 0x1c8);
                d[0] = s[0];
                d[1] = s[1];
                d[2] = s[2];
            }
            break;
    }
}
