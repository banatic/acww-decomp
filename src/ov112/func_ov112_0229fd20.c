/* func_ov112_0229fd20 @ 0x0229fd20, 0x130 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0206de88(void *a, void *b, void *c, int d, int e, int f, int g);
extern int func_ov112_0229fe70(u8 *self, int a);
extern void func_020a8c1c(void *q);
extern void func_02070870(void *q, void *p, int d, int t, int u);
extern void func_02070a54(void *a, void *b, int c, int d, int e);
extern void func_ov112_0229fcd4(u8 *self);
extern void func_ov112_0229fe60(u8 *self, int a);
extern void func_ov112_0229f488(u8 *self);

void func_ov112_0229fd20(u8 *self)
{
    u16 buf[0x10];
    int *pa;
    u8 *q;
    int i;
    int flag;
    int d;
    int t, u;

    func_0206de88(self + 0xc4, self + 0x6c50, self + 0x94, 0x60, 0x10, 0xa0, 6);
    if (func_ov112_0229fe70(self, 0x10) != 0) {
        flag = 0;
    } else if (func_ov112_0229fe70(self, 0x400) != 0) {
        flag = 0;
    } else {
        flag = 1;
    }
    buf[0] = 0;
    for (i = 0; i < 6; i++) {
        pa = (int *) (self + i * 4 + 0x6c50);
        d = *(int *) (self + (i + 1) * 4 + 0x6c50) - *(int *) (self + i * 4 + 0x6c50);
        q = self + 0x3fac + i * 0x6c;
        func_020a8c1c(q);
        if (d != 0) {
            if (i == 0) {
                t = 0;
            } else {
                t = flag;
            }
            if (i == *(int *) (self + 0x94)) {
                u = 1;
            } else {
                u = 0;
            }
            func_02070870(q, self + 0xc4 + *pa * 2, d, t, u);
        } else if (flag != 0 && i == *(int *) (self + 0x94)) {
            func_02070870(q, buf, 1, flag, 1);
        }
    }
    for (i = 0; i < 6; i++) {
        func_02070a54(self + 0x3fac + i * 0x6c, self + 0x4e50 + i * 0x500, 0x14, 0xe, 0xd);
    }
    func_ov112_0229fcd4(self);
    func_ov112_0229fe60(self, 4);
    func_ov112_0229f488(self);
}
