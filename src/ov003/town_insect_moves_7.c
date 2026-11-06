/* town_insect_moves_7: 27 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02235990 @ 0x02235990, 0xe4 bytes, Thumb
 * func_ov003_0223597c @ 0x0223597c, 0x14 bytes, Thumb
 * func_ov003_02235950 @ 0x02235950, 0x2c bytes, Thumb
 * func_ov003_02235934 @ 0x02235934, 0x1c bytes, Thumb
 * func_ov003_02235834 @ 0x02235834, 0x100 bytes, Thumb
 * func_ov003_02235744 @ 0x02235744, 0xf0 bytes, Thumb
 * func_ov003_022356ec @ 0x022356ec, 0x58 bytes, Thumb
 * func_ov003_022355d4 @ 0x022355d4, 0x118 bytes, Thumb
 * func_ov003_02235518 @ 0x02235518, 0xbc bytes, Thumb
 * func_ov003_02235454 @ 0x02235454, 0xc4 bytes, Thumb
 * func_ov003_022353e0 @ 0x022353e0, 0x74 bytes, Thumb
 * func_ov003_022353a4 @ 0x022353a4, 0x3c bytes, Thumb
 * func_ov003_0223522c @ 0x0223522c, 0x178 bytes, Thumb
 * func_ov003_022351c4 @ 0x022351c4, 0x68 bytes, Thumb
 * func_ov003_02235184 @ 0x02235184, 0x40 bytes, Thumb
 * func_ov003_02235130 @ 0x02235130, 0x54 bytes, Thumb
 * func_ov003_022350cc @ 0x022350cc, 0x64 bytes, Thumb
 * func_ov003_0223506c @ 0x0223506c, 0x60 bytes, Thumb
 * func_ov003_02234e28 @ 0x02234e28, 0x244 bytes, Thumb
 * func_ov003_02234dac @ 0x02234dac, 0x7c bytes, Thumb
 * func_ov003_02234d70 @ 0x02234d70, 0x3c bytes, Thumb
 * func_ov003_02234cf0 @ 0x02234cf0, 0x80 bytes, Thumb
 * func_ov003_02234cc4 @ 0x02234cc4, 0x2a bytes, Thumb
 * func_ov003_02234b80 @ 0x02234b80, 0x144 bytes, Thumb
 * func_ov003_022349a0 @ 0x022349a0, 0x1e0 bytes, Thumb
 * func_ov003_02234984 @ 0x02234984, 0x1c bytes, Thumb
 * func_ov003_022348dc @ 0x022348dc, 0xa8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02235834;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_022353e0;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02234e28;

typedef struct {
    short lo, hi;
} UnkStruct_02234dac;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02234d70;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_022349a0;

typedef struct {
    char pad_00[0x244];
    short t;
} UnkStruct_02234984;

extern short FX_SinCosTable_[];
extern void func_020ea6e0(void *p, int a);
extern void func_0204f818(int *a, int *b, int c);
extern int func_02031b5c(int a, int b);
extern UnkStruct_02235834 *data_020ccf94;
extern int func_02073dd4(void *a, int b);
extern int FX_MulFunc(int a, int b);
extern int func_020310c8(int a);
extern int func_02034270(int *st, Vec3 *v, int a, int b);
extern int func_020341c8(int *st, int a);
extern void func_0203423c(int *st);
extern void func_020550e4(void *p, int a);
extern void func_ov003_02231104(void *self);
extern int func_ov003_0223141c(void *p);
extern void func_02056fcc(void *p, int a, int b, int c, int d);
extern int func_020644cc(int n);
extern int func_02049d78(void *o);
extern int func_02049ec4(void *o);
extern void func_020042a0(void *p, int a);
extern int func_020912d4(int a, Vec3 *v, int b, int c);
extern int func_ov003_02219d8c(void *a, int b);
extern void func_02004290(void *a, int b);
extern void *func_0200322c(void *a, void *argument1);
extern int func_020e8870(short *a, void *b, int c);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *c);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *c);
extern void func_ov003_022321b8(Vec3 *dst, const Vec3 *src, int t);
extern int func_020a7278(void);
extern int func_020961a8(int a);
extern void func_020eaca0(Vec3 *d, Vec3 *a, Vec3 *b);
extern int func_020ea9c8(Vec3 *a);
extern int func_020e908c(Vec3 *a, Vec3 *b, int c, int d, int e);
extern int _ffix(int f);
extern short func_ov003_0223418c(int ang, int a);
extern int func_ov003_02233c70(int a, int b);
extern int FX_Div(int num, int den);
extern int func_ov003_02233e4c(void *a, void *b);
extern void func_ov068_0226fe28(void *a, void *b);
extern int func_ov003_02235b54(void *self, int a, int b);
extern void func_ov003_0222d518(unsigned char *self, int a);
extern int func_ov068_022715a0(unsigned char *self, short *p, Vec3 *v);
extern int func_ov068_022701b0(unsigned char *self, short *ang);
extern void func_ov003_02234840(unsigned char *self, short *p);
extern void func_ov068_0226fea4(unsigned char *self, short *ang, int a, int b, int c, int d);
extern int func_ov003_02232598(void *a, int b);
extern void func_ov003_02230f60(void *a);

int func_ov003_02235744(char *self, int ang, int n);
int func_ov003_0223522c(int k, int b);
void func_ov003_02235184(char *self);
int func_ov003_02234d70(void *self);
void func_ov003_02234cf0(char *self, const int *v);
void func_ov003_022349a0(unsigned char *self);
int func_ov003_02234984(UnkStruct_02234984 *s);
void func_ov003_022348dc(char *self, int t);

int func_ov003_02235990(char *self, int r, int d)
{
    int *src;
    int *dst;
    short h;
    int i;
    int j;

    src = (int *) (self + 0x204);
    if (*(signed char *) (self + 0x24d) == 0x35) {
        h = *(short *) (self + 0x23c);
    } else {
        h = *(short *) (self + 0x23a);
    }
    dst = (int *) (self + 0x1ec);
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    i = ((u16) (short) (h + d) >> 4) * 2;
    *(int *) (self + 0x1ec) += FX_SinCosTable_[i] * r / 0x64;
    dst[2] += FX_SinCosTable_[i + 1] * r / 0x64;
    dst[3] = src[0];
    dst[4] = src[1];
    dst[5] = src[2];
    j = ((u16) (short) (h - d) >> 4) * 2;
    dst[3] += FX_SinCosTable_[j] * r / 0x64;
    dst[5] += FX_SinCosTable_[j + 1] * r / 0x64;
    return 1;
}

void func_ov003_0223597c(int *p, int a)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0x29;
    func_020ea6e0(p, a);
}

int func_ov003_02235950(int p)
{
    int x = 0;
    int y = 0;

    func_0204f818(&x, &y, p);
    if (func_02031b5c(x, y) != 0) {
        return 1;
    }
    return 0;
}

void func_ov003_02235934(u8 *self, int a)
{
    int v;

    v = *(int *) (self + 0x21c) & 0xf;
    if (v > a) {
        *(self + 0x251) = 9;
    }
}

int func_ov003_02235834(char *self, int ang, int d)
{
    int *dst;
    int *src;
    int idx;

    switch (*(signed char *) (self + 0x24d)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 0x25:
            return func_ov003_02235744((char *) self, ang, (u8) (d >> 12));
        case 0x1e:
        case 0x31:
            return func_ov003_02235744((char *) self, ang, (u8) (d >> 12));
        case 0xc:
        case 0xd:
        case 0x1b:
        case 0x1c:
        case 0x1d:
            if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
                return func_ov003_02235744((char *) self, ang, (u8) (d >> 12));
            }
            break;
    }
    dst = (int *) (self + 0x1d4);
    src = (int *) (self + 0x204);
    idx = ((int) (u16) ang >> 4) * 2;
    dst[0] = src[0] + FX_MulFunc(d, FX_SinCosTable_[idx]);
    dst[2] = src[2] + FX_MulFunc(d, FX_SinCosTable_[idx + 1]);
    return 1;
}

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
        func_ov003_02235184((char *) self);
        return 1;
    }
    return 0;
}

void *func_ov003_022356ec(const int *p)
{
    void *best = 0;
    int bestd = 0x0fffffff;
    unsigned char i = 0;
    // dx/dz are declared at function scope; o and q stay in the loop body.
    int dx, dz;
    do {
        void *o = (void *) func_020961a8(i);
        if (o != 0) {
            int *q = (int *) ((char *) o + 0x5c);
            dx = p[0] - *(int *) ((char *) o + 0x5c);
            if (dx < 0) {
                dx = -dx;
            }
            dz = p[2] - q[2];
            if (dz < 0) {
                dz = -dz;
            }
            if (dx + dz < bestd) {
                bestd = dx + dz;
                best = o;
            }
        }
        i = (unsigned char) (i + 1);
    } while (i < 4);
    return best;
}

void func_ov003_022355d4(char *self)
{
    s8 k;
    u32 v;

    func_ov003_02234d70(self);
    if (func_ov003_02234984((UnkStruct_02234984 *) self) == 0) {
        k = *(s8 *) (self + 0x24d);
        if (k == 0xa || k == 0x33) {
            if (((u32) * (int *) (self + 0xf4) << 4) >> 16 != 0) {
                func_020550e4(self + 0x50, 0);
            }
            func_ov003_02231104(self);
        } else if (k != 0x33) {
            if (func_ov003_0223141c(self + 0x204) == 0) {
                *(u8 *) (self + 0x254) = 0xfe;
            }
            if (((u32) * (int *) (self + 0xf0) << 4) >> 16 < 0xc) {
                func_02056fcc(self + 0xec, 0x11, 1, 0x1000, 9);
            } else if (((u32) * (int *) (self + 0xf4) << 4) >> 16 == 0x10) {
                if (func_020644cc(0x64) > 0x5f) {
                    func_02056fcc(self + 0xec, 0x11, 1, 0x1000, 9);
                }
            }
        }
    } else {
        *(u8 *) (self + 0x251) = 0x13;
        *(int *) (self + 0x220) = *(int *) (self + 0x228);
        *(short *) (self + 0x244) = (func_020644cc(6) + 7) * 0x14;
        k = *(s8 *) (self + 0x24d);
        if (k != 0xa && k != 0x33) {
            func_02056fcc(self + 0xec, 9, 0, *(int *) (self + 0x21c), 0);
        } else {
            func_020550e4(self + 0x50, 1);
        }
    }
}

int func_ov003_02235518(int a, void *o)
{
    int c;
    int b;

    c = func_02049d78(o);
    b = func_02049ec4(o);
    if (a == 0xf) {
        if (b == 0 || b == 3) {
            if (c == 2) {
                return 1;
            }
        } else if (b != 5) {
            if (b == 4 || c == 1) {
                return 1;
            }
        }
    } else if (a == 3) {
        if (b == 0) {
            if (c == 5 || c == 6) {
                return 1;
            }
        } else if (b == 1) {
            if (c == 4 || c == 6) {
                return 1;
            }
        } else if (b == 2) {
            if (c == 6) {
                return 1;
            }
        } else if (b == 3) {
            if (c == 6 || c == 7 || c == 8) {
                return 1;
            }
        }
    } else if (a == 2) {
        if (b == 0) {
            if (c == 1 || c == 4) {
                return 1;
            }
        } else if (b == 1) {
            if (c == 3) {
                return 1;
            }
        } else if (b == 2) {
            if (c == 2 || c == 4) {
                return 1;
            }
        } else if (b == 3) {
            if (c == 1 || c == 4) {
                return 1;
            }
        }
    }
    return 0;
}

int func_ov003_02235454(char *self)
{
    Vec3 v;
    int st[17];
    int *p;

    p = (int *) (self + 0x204);
    v.x = p[0];
    v.y = p[1];
    v.z = p[2];
    func_02034270(st, &v, 0, 1);
    if (st[12] != 0) {
        v.y = st[15] + 0x100;
        func_020042a0(self + 0x174, 0x7e5);
        switch (*(signed char *) (self + 0x24d)) {
            case 0xc:
            case 0xd:
            case 0x1e:
            case 0x1f:
                func_020912d4(0x13, &v, 0, 0);
                break;
            case 0x36:
            case 0x37:
                func_020912d4(0x14, &v, 0, 0);
                break;
            default:
                func_020912d4(0x12, &v, 0, 0);
                break;
        }
        func_0203423c(st);
        return 1;
    }
    func_0203423c(st);
    return 0;
}

int func_ov003_022353e0(char *self, void *ctx)
{
    // i is declared before p.
    signed char i;
    signed char *p = (signed char *) (self + 0x24e);
    if (*p <= 0) {
        if (func_02073dd4((*(UnkStruct_022353e0 **) &data_020ccf94), (*(UnkStruct_022353e0 **) &data_020ccf94)->unk_64)) {
            for (i = 0; i < 4; i++) {
                *p = (signed char) func_ov003_02219d8c(ctx, i);
                if (*p > 0) {
                    break;
                }
            }
        } else {
            *p = (signed char) func_ov003_02219d8c(ctx, 4);
        }
    }
    if (*p > 0) {
        *p = (signed char) (*p - 1);
        if (*p == 0) {
            return 1;
        }
    }
    return 0;
}

void func_ov003_022353a4(char *self, int b, int c)
{
    int k = func_ov003_0223522c(*(signed char *) (self + 0x24d), b);
    if (k >= 0) {
        if (c) {
            func_02004290(self + 0x174, k);
        } else {
            func_020042a0(self + 0x174, k);
        }
    }
}

int func_ov003_0223522c(int k, int b)
{
    switch (k) {
        case 51:
            return 0x823;
        case 11:
        case 58:
            if (b == 0) {
                return 0x830;
            }
            return 0x837;
        case 54:
            if (b == 1) {
                return 0x834;
            }
            return 0x833;
        case 55:
            if (b == 1) {
                return 0x836;
            }
            return 0x835;
        case 10:
            return 0x831;
        case 50:
            return 0x828;
        case 29:
            return 0x825;
        case 27:
            return 0x826;
        case 28:
            return 0x82c;
        case 12:
            return 0x82b;
        case 13:
            return 0x82d;
        case 15:
        case 25:
        case 32:
        case 57:
            return 0x812;
        case 14:
        case 33:
        case 34:
        case 35:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 52:
            return 0x811;
        case 36:
        case 45:
        case 46:
        case 47:
            return 0x810;
        case 20:
            if (b != 0) {
                return 0x811;
            }
            return -1;
        case 16:
            if (b == 0) {
                return 0x822;
            }
            return 0x80f;
        case 17:
            if (b == 0) {
                return 0x827;
            }
            return 0x80f;
        case 18:
            if (b == 0) {
                return 0x82e;
            }
            return 0x80f;
        case 19:
            if (b == 0) {
                return 0x824;
            }
            return 0x80f;
        case 30:
            if (b == 0) {
                return 0x829;
            }
            return 0x82a;
    }
    return -1;
}

void func_ov003_022351c4(char *self, const Vec3 *v, int t)
{
    short a = *(short *) (self + 0x23a);
    Vec3 d;
    char *o;
    d.x = v->x;
    d.y = v->y;
    d.z = v->z;
    o = self + 0x204;
    func_020e8870(&a, func_0200322c(o, (void *) v), t);
    *(short *) (self + 0x23a) = a;
    VEC_Subtract(&d, (Vec3 *) o, &d);
    func_ov003_022321b8(&d, &d, 1);
    VEC_Add((Vec3 *) o, &d, (Vec3 *) o);
}

void func_ov003_02235184(char *self)
{
    switch (*(signed char *) (self + 0x24d)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 0x25:
            *(char *) (self + 0x253) = 0x14;
    }
}

int func_ov003_02235130(char *self)
{
    switch (*(signed char *) (self + 0x24d)) {
        case 0:
        case 1:
        case 2:
        case 3:
            return 0xccd;
        case 4:
            return 0xb33;
        case 5:
            return 0xccd;
        case 6:
            return 0xb33;
        case 7:
        case 0x25:
            return 0xccd;
    }
    return 0;
}

int func_ov003_022350cc(char *self)
{
    switch (*(signed char *) (self + 0x24d)) {
        case 0:
        case 1:
            return 0x5000;
        case 2:
        case 3:
            return 0x4600;
        case 4:
            return 0x7800;
        case 5:
        case 6:
            return 0x5000;
        case 7:
            return 0xc800;
        case 0x25:
            return 0x3c00;
    }
    return 0;
}

int func_ov003_0223506c(char *self)
{
    switch (*(signed char *) (self + 0x24d)) {
        case 0:
        case 1:
        case 2:
        case 3:
            return 0xf6;
        case 4:
            return 0x171;
        case 5:
            return 0x1ec;
        case 6:
            return 0x2b8;
        case 7:
            return 0x266;
        case 0x25:
            return 0xcd;
    }
    return 0;
}

void func_ov003_02234e28(unsigned char *self, short *p, int step, int div, unsigned char thresh, int scale)
{
    int r;
    Vec3 *v1d4;
    int k;
    int hit;
    Vec3 d;
    Vec3 w;
    Vec3 *v1c8;
    Vec3 *pos;
    int h;
    int t;
    unsigned char *pb;
    Vec3 *o;
    int c;
    int s;

    s = scale;
    v1c8 = (Vec3 *) (self + 0x1c8);
    v1d4 = (Vec3 *) (self + 0x1d4);
    pos = (Vec3 *) (self + 0x204);
    hit = func_ov003_02235b54((void *) self, 0x50, 0xe38);
    k = self[0x24b];
    r = func_020644cc(100);
    if (hit != 0) {
        *(short *) (self + 0x23a) = func_ov003_0223418c(*(short *) (self + 0x23a), hit);
        v1c8->x = pos->x;
        v1c8->y = pos->y;
        v1c8->z = pos->z;
        h = *(short *) (self + 0x23a);
        func_ov003_02235834((char *) self, h, func_ov003_022350cc((char *) self));
        return;
    }
    if (self[0x24f] % div == 0) {
        if (r > thresh) {
            self[0x24b] = (k == 0) ? 1 : 0;
        }
    }
    if (r > self[0x252]) {
        if (k != 0) {
            *p = (short) (*p + step);
            *(short *) (self + 0x23a) = *p;
        } else {
            *p = (short) (*p - step);
            *(short *) (self + 0x23a) = *p;
        }
    }
    func_ov003_0223597c((int *) (&d), *p);
    if (self[0x24a] != 0) {
        t = _ffix(0x45a00400);
        pos->x = pos->x + FX_MulFunc(FX_MulFunc(s, d.x), t);
        pos->z = pos->z + FX_MulFunc(FX_MulFunc(s, d.z), t);
    } else {
        pos->x = pos->x + FX_MulFunc(s, d.x);
        pos->z = pos->z + FX_MulFunc(s, d.z);
    }
    func_020eaca0(&w, v1c8, pos);
    c = func_020ea9c8(&w) > func_ov003_02235130((char *) self);
    if (c) {
        func_ov003_022351c4((char *) self, (const Vec3 *) v1c8, 0xaaa);
    }
    if (func_020e908c(v1c8, v1d4, 0x28, func_ov003_0223506c((char *) self) + 0x19a, func_ov003_0223506c((char *) self)) != 0) {
        return;
    }
    if (func_02073dd4((void *) ((*(UnkStruct_02234e28 **) &data_020ccf94)),
                      (*(UnkStruct_02234e28 **) &data_020ccf94)->unk_64) != 0 &&
        func_020a7278() == 0) {
        return;
    }
    pb = &self[0x253];
    if (*pb == 0) {
        h = *(short *) (self + 0x23a);
        *(short *) (self + 0x23a) = (short) (h + func_ov003_02233c70(6, 1));
        v1c8->x = pos->x;
        v1c8->y = pos->y;
        v1c8->z = pos->z;
        if (self[0x24a] != 0) {
            if (func_02073dd4((void *) ((*(UnkStruct_02234e28 **) &data_020ccf94)),
                              (*(UnkStruct_02234e28 **) &data_020ccf94)->unk_64) != 0) {
                o = (Vec3 *) func_ov003_022356ec((const int *) pos);
            } else {
                o = (Vec3 *) func_020961a8(4);
            }
            if (o != 0) {
                *(short *) (self + 0x23a) = (short) func_0200322c((void *) ((Vec3 *) ((char *) o + 0x5c)), (void *) pos);
            }
        }
        h = *(short *) (self + 0x23a);
        func_ov003_02235834((char *) self, h, func_ov003_022350cc((char *) self));
    } else {
        *pb = (unsigned char) (*pb - 1);
    }
}

void func_ov003_02234dac(char *self, int a, int lim, int den)
{
    int *v = (int *) (self + 0x204);
    int idx = (unsigned short) a;
    int step = FX_Div(((UnkStruct_02234dac *) FX_SinCosTable_)[idx >> 4].lo, den);
    if (*(int *) (self + 0x220) != *(int *) (self + 0x228)) {
        lim = FX_Div(lim, 0x2000);
    }
    if ((step > 0 && v[1] + step < lim + *(int *) (self + 0x220)) ||
        (step < 0 && v[1] + step > *(int *) (self + 0x220) - lim)) {
        v[1] += step;
    }
}

int func_ov003_02234d70(void *self)
{
    int t[3];
    int r = func_ov003_02233e4c(self, t);
    if (func_02073dd4((*(UnkStruct_02234d70 **) &data_020ccf94), (*(UnkStruct_02234d70 **) &data_020ccf94)->unk_64)) {
        func_ov003_02234cf0((char *) self, (const int *) t);
    } else {
        func_ov068_0226fe28(self, t);
    }
    return r;
}

void func_ov003_02234cf0(char *self, const int *v)
{
    int c = *(unsigned char *) (self + 0x254);
    if (func_020a7278()) {
        if (v[0] != 0 && *(unsigned char *) (self + 0x24a) == 0 && c >= *(unsigned char *) (self + 0x255)) {
            *(short *) (self + 0x240) = (short) func_0200322c((void *) v, self + 0x204);
            *(char *) (self + 0x251) = 7;
            *(char *) (self + 0x24a) = 1;
        }
    } else {
        if (*(unsigned char *) (self + 0x24a) == 0 && c >= *(unsigned char *) (self + 0x255)) {
            *(char *) (self + 0x24a) = 1;
            *(char *) (self + 0x251) = 7;
        }
    }
}

void func_ov003_02234cc4(u8 *self)
{
    if ((((unsigned int) (*(int *) (self + 0xf4)) << 4) >> 16) == 1) {
        func_020550e4((void *) (self + 0x50), 2);
    } else {
        func_020550e4((void *) (self + 0x50), 1);
    }
}

void func_ov003_02234b80(char *self)
{
    short n;
    short v;
    int *s;
    int *d;

    n = *(short *) (self + 0x232);
    if (n > 0x8c) {
        *(u8 *) (self + 0x251) = 9;
    } else if (func_ov003_02235b54(self, 0x50, 0xe38) != 0) {
        *(short *) (self + 0x232) = n + 1;
    } else {
        *(short *) (self + 0x232) = 0;
    }
    switch (*(u8 *) (self + 0x251)) {
        case 0:
            func_ov003_022349a0((unsigned char *) self);
            break;
        case 6:
            func_ov003_022355d4((char *) self);
            break;
        case 9:
        case 0xb:
            if (((u32) * (int *) (self + 0xf0) << 4) >> 16 > 9) {
                func_02056fcc(self + 0xec, 9, 0, 0x1000, 0);
            }
            func_ov003_022348dc((char *) self, 0x1ccd);
            break;
        case 7:
            *(u8 *) (self + 0x251) = 0;
            *(short *) (self + 0x23a) = *(short *) (self + 0x23a) + *(short *) (self + 0x240);
            v = *(short *) (self + 0x23a);
            if (func_ov003_02235834((char *) self, v, func_ov003_022350cc((char *) self)) != 0) {
                s = (int *) (self + 0x204);
                d = (int *) (self + 0x1c8);
                d[0] = s[0];
                d[1] = s[1];
                d[2] = s[2];
            }
            break;
        case 0x13:
            *(u8 *) (self + 0x24a) = 0;
            *(u8 *) (self + 0x251) = 0;
            v = *(short *) (self + 0x23a);
            if (func_ov003_02235834((char *) self, v, func_ov003_022350cc((char *) self)) != 0) {
                s = (int *) (self + 0x204);
                d = (int *) (self + 0x1c8);
                d[0] = s[0];
                d[1] = s[1];
                d[2] = s[2];
            }
            break;
    }
}

void func_ov003_022349a0(unsigned char *self)
{
    short ang;
    Vec3 v0c;
    Vec3 v18;
    Vec3 *pos;
    short *p242;
    int vy;
    int n;
    unsigned char *t;

    ang = *(short *) (self + 0x23a);
    pos = (Vec3 *) (self + 0x204);
    p242 = (short *) (self + 0x242);
    if (*(signed char *) (self + 0x24d) != 8) {
        if ((unsigned) (*(int *) (self + 0xf0) << 4) >> 16 > 9) {
            func_02056fcc((void *) (self + 0xec), 9, 0, *(int *) (self + 0x21c), 0);
        }
    }
    if (func_ov003_02234d70((void *) self) == 2) {
        if (*(signed char *) (self + 0x24d) != 8) {
            func_ov003_0222d518(self, *(int *) (self + 0x21c));
        } else {
            func_ov003_0222d518(self, 0x1000);
        }
        self[0x24a] = 0;
    }
    if (self[0x24a] != 0) {
        if (*(signed char *) (self + 0x24d) != 8) {
            vy = FX_MulFunc(*(int *) (self + 0x21c), 0x1333);
            if (vy != *(int *) (self + 0xfc)) {
                func_ov003_0222d518(self, vy);
            }
        } else {
            t = (unsigned char *) func_020961a8(4);
            if (t != 0) {
                func_020eaca0(&v18, pos, (Vec3 *) (t + 0x5c));
                v0c.x = v18.x;
                v0c.y = v18.y;
                v0c.z = v18.z;
                func_ov003_022321b8(&v0c, (const Vec3 *) (&v0c), 3);
                VEC_Add((const Vec3 *) pos, (const Vec3 *) (&v0c), pos);
            }
        }
    } else if (*(signed char *) (self + 0x24d) == 8) {
        if (func_ov068_022715a0(self, p242, &v0c) == 0) {
            return;
        }
    } else {
        if (*(int *) (self + 0x21c) != *(int *) (self + 0xfc)) {
            func_ov003_0222d518(self, *(int *) (self + 0x21c));
        }
        if (func_02073dd4((void *) ((*(UnkStruct_022349a0 **) &data_020ccf94)),
                          (*(UnkStruct_022349a0 **) &data_020ccf94)->unk_64) == 0) {
            func_ov068_022701b0(self, &ang);
        }
    }
    n = *p242;
    vy = 0x44 * n + -10 * (n * n) / 2;
    if (self[0x24c] != 0 && vy >= 0) {
        FX_MulFunc(vy, 0x2000);
    } else if (vy < -0x333) {
        vy = -0x333;
    }
    *p242 = (short) (*p242 + 4);
    func_ov003_02234840(self, p242);
    pos->y = pos->y + vy;
    if (*(signed char *) (self + 0x24d) == 8) {
        func_ov068_0226fea4(self, &ang, 0xaaa, 0x14, 0x3c, self[0x257] << 12);
    } else {
        func_ov003_02234e28(self, &ang, 0x38e, 0x14, 0x3c, self[0x257] << 12);
    }
}

int func_ov003_02234984(UnkStruct_02234984 *s)
{
    if (s->t > 0) {
        s->t--;
    } else {
        return 1;
    }
    return 0;
}

void func_ov003_022348dc(char *self, int t)
{
    Vec3 *v = (Vec3 *) (self + 0x204);
    short *p = (short *) (self + 0x242);
    Vec3 d;
    int n;
    int x;
    func_ov003_0223597c((int *) (&d), *(short *) (self + 0x23a));
    if (func_ov003_02232598(self, 1)) {
        func_ov003_02230f60(self);
    }
    n = *p;
    x = FX_MulFunc(t, (0x44 * n) << 12);
    x >>= FX_Div((n * n) << 12, 0x1000) + 0xc;
    d.y = x;
    if (func_ov003_02235b54(self, 0x50, 0xe38) == 0) {
        d.x = FX_MulFunc(d.x, 0x10000);
        d.z = FX_MulFunc(d.z, 0x10000);
    }
    *p = (short) (*p + 1);
    VEC_Add(v, &d, v);
}
