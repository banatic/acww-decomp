/* func_ov003_022319bc @ 0x022319bc, 0x134 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern void func_ov003_0223597c(int *v, int a);
extern void func_ov003_022353a4(void *self, int a, int b);
extern int func_ov003_02235b54(void *self, int a, int b);
extern void VEC_Add(int *a, int *b, int *c);
extern void func_02056fcc(void *p, int a, int b, int c, int d);
extern void func_020550e4(void *p, int a);
extern int func_ov003_02232598(void *self, int a);
extern void func_ov003_02230f60(void *self);

void func_ov003_022319bc(char *self, short *pn)
{

    s8 k;
    int t;
    int *p;
    int v[3];
    int fld;
    char *o;

    p = (int *) (self + 0x204);
    fld = ((u32) * (int *) (self + 0xf4) << 4) >> 16;
    k = *(s8 *) (self + 0x24d);
    t = FX_Div(*pn << 12, 0x4000);
    o = self + 0x50;
    func_ov003_0223597c(v, *(short *) (self + 0x23a));
    if (*pn == 0) {
        func_ov003_022353a4(self, 1, 0);
    }
    v[1] = FX_MulFunc(FX_MulFunc(0x100, t), t);
    if (func_ov003_02235b54(self, 0x50, 0xe38) == 0) {
        v[0] = v[0] << 4;
        v[2] = v[2] << 4;
    }
    VEC_Add(p, v, p);
    *pn = *pn + 1;
    if (k == 0x14) {
        if (((u32) * (int *) (o + 0xa0) << 4) >> 16 < 0x18) {
            func_02056fcc(o + 0x9c, 0x1a, 0, 0x1000, 0x18);
        } else if (((u32) * (int *) (o + 0xa4) << 4) >> 16 < 0x18) {
            *(int *) (o + 0xa4) = 0x18000;
        }
    } else if (*(s8 *) (self + 0x24d) == 9) {
        if (*(u8 *) (o + 0xb0) != 0) {
            func_02056fcc(o + 0x9c, 9, 0, 0x1000, 0);
        }
    } else {
        func_020550e4(o, (u16) (fld == 1 ? 2 : 1));
    }
    if (func_ov003_02232598(self, 1) != 0) {
        func_ov003_02230f60(self);
    }
}
