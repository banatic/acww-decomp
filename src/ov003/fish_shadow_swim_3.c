/* fish_shadow_swim_3: 6 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0222b9b4 @ 0x0222b9b4, 0xd8 bytes, Thumb
 * func_ov003_0222b960 @ 0x0222b960, 0x54 bytes, Thumb
 * func_ov003_0222b8fc @ 0x0222b8fc, 0x64 bytes, Thumb
 * func_ov003_0222b8bc @ 0x0222b8bc, 0x40 bytes, Thumb
 * func_ov003_0222b798 @ 0x0222b798, 0x124 bytes, Thumb
 * func_ov003_0222b794 @ 0x0222b794, 0x2 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern short FX_SinCosTable_[];
extern int FX_MulFunc(int a, int b);
extern void func_ov003_0222be78(void *p, int a, int b);
extern void func_ov003_022277fc(void *self, int a);
void func_ov003_0222803c(void *p, int k);
int func_ov003_0222793c(int a, int b);
extern int data_020c904c;
extern void func_02091278(int h, Vec3 *v, int a, int b);

void func_ov003_0222b9b4(char *self)
{

    int x;
    int h;
    int a;
    int z;
    short *pa;
    int t142;
    int t138;
    int u142;
    int u138;

    a = *(int *) (self + 0x13c) << 3;
    pa = (short *) (self + 0x142);
    *pa += 0x2000;
    t142 = FX_SinCosTable_[(*(u16 *) pa >> 4) << 1];
    t138 = FX_SinCosTable_[(*(u16 *) (self + 0x138) >> 4) << 1];
    h = a >> 2;
    x = FX_MulFunc(a, t138) + FX_MulFunc(h, t142);
    u142 = FX_SinCosTable_[(*(u16 *) (self + 0x142) >> 4) << 1];
    u138 = FX_SinCosTable_[((*(u16 *) (self + 0x138) >> 4) << 1) + 1];
    z = FX_MulFunc(a, u138) + FX_MulFunc(h, u142);
    *(int *) (self + 0x120) += x;
    *(int *) (self + 0x128) += z;
    if (*(int *) (self + 0x13c) >= 0xa) {
        func_ov003_022277fc((void *) self, 0x20);
    } else {
        func_ov003_022277fc((void *) self, 0x10);
    }
    if (a > 0x19a) {
        *(u8 *) (self + 0x200) = 2;
    }
}

void func_ov003_0222b960(void *self)
{
    func_ov003_0222be78((char *) self + 0x120, 0x19a, *(short *) ((char *) self + 0x138));
    func_ov003_022277fc(self, 0x20);
    *(u16 *) ((char *) self + 0x140) -= 1;
    if (*(u16 *) ((char *) self + 0x140) == 0) {
        *(int *) ((char *) self + 0x13c) = 0;
        *(u8 *) ((char *) self + 0x200) = 3;
    }
}

void func_ov003_0222b8fc(void *self)
{
    int d = 0x19a - (*(int *) ((char *) self + 0x13c) << 3);
    func_ov003_0222be78((char *) self + 0x120, d, *(short *) ((char *) self + 0x138));
    if (*(int *) ((char *) self + 0x13c) >= 0xa) {
        func_ov003_022277fc(self, 3);
    } else {
        func_ov003_022277fc(self, 0x10);
    }
    if (d <= 0) {
        *(int *) ((char *) self + 0x13c) = 0;
        *(u8 *) ((char *) self + 0x200) = 4;
    }
}

void func_ov003_0222b8bc(char *self)
{
    func_ov003_022277fc(self, 0xa);
    func_ov003_0222803c(self + 0x120, 0x40);
    if (func_ov003_0222793c(0, 0x64) == 1 || *(int *) (self + 0x13c) > 0x64) {
        *(u8 *) (self + 0x200) = 0;
    }
}

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
            func_ov003_022277fc((void *) self, 3);
        } else if (n >= 5) {
            func_ov003_022277fc((void *) self, 0x10);
        } else {
            func_ov003_022277fc((void *) self, 0x20);
        }
    } else {
        func_ov003_022277fc((void *) self, 0x20);
    }
    v.x = *(int *) (self + 0x120);
    v.y = *(int *) (self + 0x124);
    v.z = *(int *) (self + 0x128);
    v.y = data_020c904c;
    func_02091278(*(int *) (self + 0x204), &v, 0, 0);
}

void func_ov003_0222b794(void) {}
