/* func_ov003_02230e18 @ 0x02230e18, 0x148 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov003_02232f78(void *self, short *pn);
extern void func_020550e4(void *p, int a);
extern int func_ov003_02235b54(void *self, int a, int b);
extern void func_ov003_0223597c(int *v, int a);
extern int FX_MulFunc(int a, int b);
extern void func_02056fcc(void *p, int a, int b, int c, int d);
extern void func_ov003_02234cc4(void *self);
extern void func_ov003_022353a4(void *self, int a, int b);
extern int func_ov003_02232598(void *self, int a);
extern void func_ov003_02230f60(void *self);
extern void VEC_Add(int *a, int *b, int *c);

void func_ov003_02230e18(char *self, short *pn)
{
    int v[3];
    int *p;
    u32 fld;
    short n;
    s8 k;

    if (*(s8 *) (self + 0x24d) != 0x1a) {
        p = (int *) (self + 0x204);
        if (func_ov003_02235b54(self, 0x50, 0xe38) == 0) {
            func_ov003_0223597c(v, *(short *) (self + 0x23a));
            if (*(u8 *) (self + 0x251) == 0xb) {
                v[0] = FX_MulFunc(v[0], 0xa000);
                v[2] = FX_MulFunc(v[2], 0xa000);
            } else {
                v[0] = FX_MulFunc(v[0], 0xf000);
                v[2] = FX_MulFunc(v[2], 0xf000);
            }
        } else {
            v[0] = 0;
            v[2] = 0;
        }
        n = *pn;
        v[1] = n * ((n + 0xc) << 1);
        k = *(s8 *) (self + 0x24d);
        if ((u8) (s8) (k - 0xe) <= 1) {
            if (((u32) * (int *) (self + 0xf0) << 4) >> 16 != 0xb) {
                func_02056fcc(self + 0xec, 0xb, 0, 0x1000, 9);
            } else if (((u32) * (int *) (self + 0xf4) << 4) >> 16 < 9) {
                *(int *) (self + 0xf4) = 0x9000;
            }
        } else {
            func_ov003_02234cc4(self);
        }
        if (*pn == 0) {
            func_ov003_022353a4(self, 1, 0);
        }
        if (func_ov003_02232598(self, 1) != 0) {
            func_ov003_02230f60(self);
        }
        VEC_Add(p, v, p);
    } else {
        func_ov003_02232f78(self, pn);
        fld = ((u32) * (int *) (self + 0xf4) << 4) >> 16;
        if (fld == 0) {
            func_020550e4(self + 0x50, 1);
        } else if (fld == 1) {
            func_020550e4(self + 0x50, 2);
        }
    }
}
