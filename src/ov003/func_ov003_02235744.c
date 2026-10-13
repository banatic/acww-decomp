/* func_ov003_02235744 @ 0x02235744, 0xf0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern short FX_SinCosTable_[];
extern int FX_MulFunc(int a, int b);
extern int func_020310c8(int a);
extern void func_02034270(int *st, Vec3 *v, int a, int b);
extern int func_020341c8(int *st, int a);
extern void func_0203423c(int *st);
extern void func_ov003_02235184(void *self);

int func_ov003_02235744(char *self, int ang, int n)
{

    int lim;
    u8 i;
    int sn;
    int cs;
    int *dst;
    int nlim;
    int one1;
    int one2;
    Vec3 v;
    int st[17];
    int *src;
    int flag;
    int t;
    int idx;

    idx = ((int) (u16) ang >> 4) * 2;
    sn = FX_SinCosTable_[idx];
    cs = FX_SinCosTable_[idx + 1];
    dst = (int *) (self + 0x1d4);
    src = (int *) (self + 0x204);
    lim = src[1];
    if (lim < func_020310c8(0)) {
        lim = func_020310c8(0);
    }
    i = 1;
    nlim = n + 1;
    one1 = 1;
    one2 = 1;
    for (; i < nlim; i++) {
        t = i << 12;
        v.x = src[0] + FX_MulFunc(t, sn);
        v.z = src[2] + FX_MulFunc(t, cs);
        func_02034270(st, &v, 0, 0);
        if (func_020341c8(st, one1) > lim) {
            flag = one2;
        } else {
            flag = 0;
        }
        func_0203423c(st);
        if (flag != 0) {
            break;
        }
    }
    i = i - 1;
    if (i != 0) {
        t = i << 12;
        dst[0] = src[0] + FX_MulFunc(t, sn);
        dst[2] = src[2] + FX_MulFunc(t, cs);
        func_ov003_02235184(self);
        return 1;
    }
    return 0;
}
