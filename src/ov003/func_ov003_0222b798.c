/* func_ov003_0222b798 @ 0x0222b798, 0x124 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern short FX_SinCosTable_[];
extern int data_020c904c;
extern int FX_MulFunc(int a, int b);
extern void func_ov003_022277fc(char *self, int k);
extern void func_02091278(int h, Vec3 *v, int a, int b);

void func_ov003_0222b798(char *self)
{
    Vec3 v;
    // P
    int spd;
    int dx;
    int half;
    int dz;
    short *h;
    // /P
    spd = *(int *) (self + 0x13c) << 7;
    if (spd > 0x215) {
        spd = 0x215;
    }
    h = (short *) (self + 0x142);
    *h = *(short *) (self + 0x142) + 0x2000;
    {
        int sa = FX_SinCosTable_[(((u16) *h) >> 4) * 2];
        int sb = FX_SinCosTable_[((*(u16 *) (self + 0x138)) >> 4) * 2];
        half = spd >> 5;
        dx = FX_MulFunc(spd, sb) + FX_MulFunc(half, sa);
    }
    {
        int sa = FX_SinCosTable_[((*(u16 *) (self + 0x142)) >> 4) * 2];
        int cb = FX_SinCosTable_[((*(u16 *) (self + 0x138)) >> 4) * 2 + 1];
        dz = FX_MulFunc(spd, cb) + FX_MulFunc(half, sa);
    }
    *(int *) (self + 0x120) = *(int *) (self + 0x120) + dx;
    *(int *) (self + 0x128) = *(int *) (self + 0x128) + dz;
    if (*(u8 *) (self + 0x7f)) {
        int n = *(int *) (self + 0x13c);
        if (n >= 0xa) {
            func_ov003_022277fc(self, 3);
        } else if (n >= 5) {
            func_ov003_022277fc(self, 0x10);
        } else {
            func_ov003_022277fc(self, 0x20);
        }
    } else {
        func_ov003_022277fc(self, 0x20);
    }
    v.x = *(int *) (self + 0x120);
    v.y = *(int *) (self + 0x124);
    v.z = *(int *) (self + 0x128);
    v.y = data_020c904c;
    func_02091278(*(int *) (self + 0x204), &v, 0, 0);
}
