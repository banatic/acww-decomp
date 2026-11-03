/* town_insect_moves: 6 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0223126c @ 0x0223126c, 0x1b0 bytes, Thumb
 * func_ov003_02231104 @ 0x02231104, 0x168 bytes, Thumb
 * func_ov003_0223108c @ 0x0223108c, 0x78 bytes, Thumb
 * func_ov003_02230f88 @ 0x02230f88, 0x104 bytes, Thumb
 * func_ov003_02230f60 @ 0x02230f60, 0x28 bytes, Thumb
 * func_ov003_02230e18 @ 0x02230e18, 0x148 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern void *func_020961a8(int n);
extern int func_ov003_0223141c(void *p);
extern int func_ov003_02234d70(void *self);
extern int func_020ea990(void *a, void *b);
extern void func_02056fcc(void *p, int a, int b, int c, int e);
extern void func_020550e4(void *p, int a);
extern void func_ov003_0223597c(Vec3 *d, int ang);
extern int func_020644cc(int a);
extern int FX_MulFunc(int a, int b);
extern int FX_Div(int a, int b);
extern void *func_0209d088(void *p);
extern void NNS_G3dMdlSetMdlAlpha(void *mdl, int a, int b);
extern void func_ov003_02232f78(void *self, short *pn);
extern int func_ov003_02235b54(void *self, int a, int b);
extern void func_ov003_02234cc4(void *self);
extern void func_ov003_022353a4(void *self, int a, int b);
extern int func_ov003_02232598(void *self, int a);
extern void VEC_Add(int *a, int *b, int *c);

void func_ov003_0223126c(char *self, u16 *out)
{
    void *t = func_020961a8(4);
    char *s = self + 0x204;
    int d;
    int st;
    u16 v;
    int c;

    if (func_ov003_0223141c(s) == 0) {
        *(u8 *) (self + 0x254) = 0xfe;
    }
    *(u8 *) (self + 0x24a) = 0;
    func_ov003_02234d70(self);
    if (t == 0) {
        return;
    }

    d = func_020ea990((char *) t + 0x5c, s);
    c = *(u8 *) (self + 0x254);
    if (d <= 0xccd) {
        *(u8 *) (self + 0x251) = 9;
        *out = 0;
        return;
    }

    st = *(s8 *) (self + 0x24d);
    if ((u8) (s8) (st - 0xe) <= 1) {
        if (c > 0x14) {
            v = (u16) (*(int *) (self + 0xf4) >> 12);
            func_02056fcc(self + 0xec, 9, 1, 0x1000, v);
            *(u8 *) (self + 0x252) = 0x3c;
            return;
        }
        if (*(u8 *) (self + 0x252) != 0) {
            *(u8 *) (self + 0x252) = *(u8 *) (self + 0x252) - 1;
            return;
        }
        if (d < *(int *) (self + 0x224)) {
            v = (u16) (*(int *) (self + 0xf4) >> 12);
            if (v == 0) {
                func_02056fcc(self + 0xec, 4, 1, 0x1000, 0);
                return;
            }
            if (v > 4) {
                func_02056fcc(self + 0xec, 4, 3, 0x1000, v);
            }
            return;
        }
        v = (u16) (*(int *) (self + 0xf4) >> 12);
        if (v != 0) {
            func_02056fcc(self + 0xec, 0, 3, 0x1000, v);
        }
        return;
    }
    if (st != 0x1a) {
        return;
    }
    if (c > 0x14) {
        v = (u16) (*(int *) (self + 0xf4) >> 12);
        if (v == 2) {
            func_020550e4(self + 0x50, 1);
            return;
        }
        if (v != 1) {
            return;
        }
        func_020550e4(self + 0x50, 0);
        *(u8 *) (self + 0x251) = 0x13;
        *(u8 *) (self + 0x252) = 0x3c;
        return;
    }
    {
        int w = *(int *) (self + 0xf4) >> 12;
        if ((u16) w == 0 && *(u8 *) (self + 0x252) == 0) {
            func_020550e4(self + 0x50, 1);
            return;
        }
        if ((u16) w == 1) {
            func_020550e4(self + 0x50, 2);
            return;
        }
        if (*(u8 *) (self + 0x252) != 0) {
            *(u8 *) (self + 0x252) = *(u8 *) (self + 0x252) - 1;
        }
    }
}

void func_ov003_02231104(unsigned char *self)
{
    Vec3 *hi;
    Vec3 *lo;
    Vec3 v[2];
    short ang;
    unsigned char flag;
    Vec3 *p;

    hi = (Vec3 *) (self + 0x1bc);
    lo = (Vec3 *) (self + 0x1b0);
    ang = *(short *) (self + 0x23a);
    flag = self[0x24b];
    v[0].x = 0;
    v[0].y = 0;
    v[0].z = 0;
    p = (Vec3 *) (self + 0x204);
    v[1].x = p->x;
    v[1].y = p->y;
    v[1].z = p->z;
    if (func_020644cc(0x64) > 0x50) {
        if (self[0x24f] % 0x14 == 0) {
            if (flag == 0) {
                flag = 1;
            } else {
                flag = 0;
            }
            self[0x24b] = flag;
        }
        if (flag != 0) {
            if (*(signed char *) (self + 0x24d) == 0x33) {
                ang = (short) (ang + (short) *(int *) (self + 0x21c));
            } else {
                ang = (short) (ang + 0xaaa);
            }
        } else {
            if (*(signed char *) (self + 0x24d) == 0x33) {
                ang = (short) (ang + 0xaaa);
            } else {
                ang = (short) (ang - (short) *(int *) (self + 0x21c));
            }
        }
    }
    func_ov003_0223597c(&v[0], ang);
    *(short *) (self + 0x23a) = ang;
    p->z = p->z + FX_Div(FX_MulFunc(self[0x257] << 12, v[0].z), 0x20000);
    p->x = p->x + FX_Div(FX_MulFunc(self[0x257] << 12, v[0].x), 0x20000);
    if (p->x < lo->x || p->x > hi->x) {
        p->x = v[1].x;
    }
    if (p->z < lo->z || p->z > hi->z) {
        p->z = v[1].z;
    }
    if (*(signed char *) (self + 0x24d) != 0x33) {
        if (p->z != v[1].z) {
            p->y = p->y - (p->z - v[1].z);
        }
        if (p->y < lo->y && p->y > hi->y) {
            p->y = v[1].y;
        }
    }
}

void func_ov003_0223108c(char *self)
{
    int *v = (int *) (self + 0x204);
    if (func_020644cc(2) == 0) {
        v[0] += FX_Div(0x7000, 0x10000);
        v[1] = FX_Div(0xc000, 0x10000);
        v[2] += FX_Div(0x3000, 0x10000);
    } else {
        v[0] -= FX_Div(0x7000, 0x10000);
        v[1] = FX_Div(0xc000, 0x10000);
        v[2] += FX_Div(0x3000, 0x10000);
    }
}

void func_ov003_02230f88(char *self)
{
    int *p;
    int *a;
    int *b;

    p = (int *) (self + 0x204);
    a = (int *) (self + 0x1b0);
    b = (int *) (self + 0x1bc);
    if (*(signed char *) (self + 0x24d) == 0x33) {
        a[0] = p[0] - FX_Div(0x6000, 0x10000);
        a[1] = FX_Div(0xa000, 0x10000);
        a[2] = p[2] - FX_Div(0x4000, 0x10000);
        b[0] = p[0] + FX_Div(0x6000, 0x10000);
        b[1] = FX_Div(0xc000, 0x10000);
        b[2] = p[2] + FX_Div(0x4000, 0x10000);
    } else if (*(signed char *) (self + 0x24d) == 0x19) {
        a[0] = p[0] - 0x6000;
        a[2] = p[2] + 0x6000;
        b[0] = p[0] + 0x6000;
        b[2] = p[2] - 0x6000;
    } else {
        a[0] = p[0] - FX_Div(0x9000, 0x10000);
        a[1] = FX_Div(0x9000, 0x10000);
        a[2] = p[2] - FX_Div(0x2000, 0x10000);
        b[0] = p[0] + FX_Div(0x9000, 0x10000);
        b[1] = 0x1000;
        b[2] = p[2] + FX_Div(0x5000, 0x10000);
    }
}

void func_ov003_02230f60(unsigned char *p)
{
    p[0x250] = 4;
    NNS_G3dMdlSetMdlAlpha(func_0209d088(p + 0x130), 0, 0);
}

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
            func_ov003_0223597c((Vec3 *) v, *(short *) (self + 0x23a));
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
            func_ov003_02230f60((unsigned char *) self);
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
