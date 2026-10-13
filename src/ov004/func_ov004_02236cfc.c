/* func_ov004_02236cfc @ 0x02236cfc, 0x110 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_02239424(void *a, void *b, void *c, int d);
extern int FX_MulFunc(int a, int b);
extern int _s32_div_f(int a, int b);
extern s16 FX_SinCosTable_[];

void func_ov004_02236cfc(char *self)
{
    // DECLS
    int v;
    // ENDDECLS

    func_ov004_02239424(self + 0x1c0, self + 0x1a8, self + 0x1fc, 0x1600);
    v = *(int *) (self + 0x20c);
    *(int *) (self + 0x1a8) += FX_MulFunc(v, FX_SinCosTable_[((int) *(u16 *) (self + 0x1c0) >> 4) << 1]);
    *(int *) (self + 0x1b0) += FX_MulFunc(v, FX_SinCosTable_[(((int) *(u16 *) (self + 0x1c0) >> 4) << 1) + 1]);
    *(s16 *) (self + 0x208) = (s16) (*(s16 *) (self + 0x208) + 0x2000);
    v = _s32_div_f(7 * v, 10);
    *(int *) (self + 0x1a8) += FX_MulFunc(v, FX_SinCosTable_[((int) *(u16 *) (self + 0x208) >> 4) << 1]);
    *(int *) (self + 0x1b0) += FX_MulFunc(v, FX_SinCosTable_[((int) *(u16 *) (self + 0x208) >> 4) << 1]);
    if (*(int *) (self + 0x158) >= *(u8 *) (self + 0x210)) {
        *(int *) (self + 0x158) = 0;
        *(u8 *) (self + 0x21c) = 5;
        *(int *) (self + 0x218) >>= 1;
        *(int *) (self + 0x110) = *(int *) (self + 0x218);
    }
}
