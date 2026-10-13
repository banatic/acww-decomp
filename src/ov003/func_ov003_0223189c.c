/* func_ov003_0223189c @ 0x0223189c, 0x120 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov003_022353a4(void *self, int a, int b);
extern int func_ov003_02232598(void *self, int a);
extern void func_ov003_02230f60(void *self);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern void func_02056fcc(void *p, int a, int b, int c, int d);
extern void func_ov003_02234cc4(void *self);

void func_ov003_0223189c(char *self, short *pn)
{
    int *p;
    s8 k;
    int t;

    p = (int *) (self + 0x204);
    k = *(s8 *) (self + 0x24d);
    if (k != 0x10 && k != 0x11 && k != 0x12 && k != 0x13) {
        func_ov003_022353a4(self, 0, 1);
    }
    if (*(short *) (self + 0x23a) >= 0) {
        p[0] = p[0] + 0x200;
    } else {
        p[0] = p[0] - 0x200;
    }
    if (func_ov003_02232598(self, 1) != 0) {
        func_ov003_02230f60(self);
        return;
    }
    t = FX_Div(*pn << 12, 0x4000);
    p[1] = p[1] + FX_MulFunc(FX_MulFunc(0x100, t), t);
    *pn = *pn + 1;
    if (*(u8 *) (self + 0x251) == 0xb && (*(short *) (self + 0x23a) == 0x6001 || *(short *) (self + 0x23a) == -0x6001)) {
        p[2] = p[2] - 0x100;
    } else {
        p[2] = p[2] + 0x100;
    }
    if (k == 0x14) {
        if (((u32) * (int *) (self + 0xf0) << 4) >> 16 < 0x18) {
            func_02056fcc(self + 0xec, 0x1a, 0, 0x1000, 0x18);
        } else if (((u32) * (int *) (self + 0xf4) << 4) >> 16 < 0x18) {
            *(int *) (self + 0xf4) = 0x18000;
        }
    } else {
        func_ov003_02234cc4(self);
    }
}
