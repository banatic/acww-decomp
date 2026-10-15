/* func_020a1f4c @ 0x020a1f4c, 0x168 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020508fc(u8 *p, int n, int v);
extern int func_020a1acc(u8 *self, int k);
extern void func_0209fafc(u8 *p);
extern void func_0209fb70(int *p);
extern int func_020a1738(int a, int *p);
extern int func_0209faf4(int *p);
extern void func_0209faf8(u8 *p, int v);
extern void func_0209fb6c(int *p);
extern int func_0209015c(u8 *p);
extern void func_02090168(u8 *p, int v);
extern int func_0208ffe8(u8 *p);
extern void func_0208fff4(u8 *p, int v);
extern int func_02098844(u8 *p, int i);
extern u8 *func_02099664(int);
extern u8 *func_02099658(int);
extern int func_02077bb8(u8 *p);
extern void func_02077bc0(u8 *p, int v);
extern int func_02077c9c(u8 *p);
extern void func_02077ca8(u8 *p, int v);
extern int func_0209faec(u8 *p);
extern void func_0209faf0(u8 *p, int v);
extern unsigned short func_02050920(u8 *p, int n);

int func_020a1f4c(u8 *self, int a)
{
    u8 *b;
    u8 *c;
    int k;
    int i;
    u8 *p;
    int loc;

    if (a == 2) {
        c = *(u8 **) (self + 0xb0);
        *(u16 *) (c + 0xc802) = (u16) func_020508fc(c, 0xc804, *(u16 *) (c + 0xc802));
    } else {
        k = 0;
        if (a == 1) {
            k = func_020a1acc(self, 0);
        }
        if (k == 3) {
            return 3;
        }
        if (k == 1) {
            return 1;
        }
        b = *(u8 **) (self + 0xb0);
        if (a == 0) {
            func_0209fafc(b + 0x173f8);
        } else if (k == 0) {
            func_0209fb70(&loc);
            func_020a1738(0, &loc);
            func_0209faf8(b + 0x173f8, func_0209faf4(&loc));
            func_0209fb6c(&loc);
        }
        p = b + 0x11c70;
        func_02090168(p, func_020508fc(p, 0x950, func_0209015c(p)));
        p = b + 0x1704c;
        func_0208fff4(p, func_020508fc(p, 0x104, func_0208ffe8(p)));
        for (i = 0; i < 4; i++) {
            p = func_02099664((int) func_02098844(b + 0x14, i));
            func_02077bc0(p, func_020508fc(p, 0x50, func_02077bb8(p)));
            p = func_02099658((int) func_02098844(b + 0x14, i));
            func_02077ca8(p, func_020508fc(p, 0x484, func_02077c9c(p)));
        }
        func_0209faf0(b + 0x173f8, func_020508fc(b, 0x173fc, func_0209faec(b + 0x173f8)));
        func_02050920(b, 0x173fc);
        func_02050920(b, 0x173fc);
    }
    self[0xa0] = 2;
    return 3;
}
