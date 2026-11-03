/* snowman_5: 13 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221b064 @ 0x0221b064, 0x110 bytes, Thumb
 * func_ov003_0221af94 @ 0x0221af94, 0xd0 bytes, Thumb
 * func_ov003_0221ac70 @ 0x0221ac70, 0x324 bytes, Thumb
 * func_ov003_0221ac24 @ 0x0221ac24, 0x4c bytes, Thumb
 * func_ov003_0221ac18 @ 0x0221ac18, 0xc bytes, Thumb
 * func_ov003_0221abf8 @ 0x0221abf8, 0x20 bytes, Thumb
 * func_ov003_0221a8e8 @ 0x0221a8e8, 0x310 bytes, Thumb
 * func_ov003_0221a8d4 @ 0x0221a8d4, 0x14 bytes, Thumb
 * func_ov003_0221a8c4 @ 0x0221a8c4, 0xe bytes, Thumb
 * func_ov003_0221a8ac @ 0x0221a8ac, 0x18 bytes, Thumb
 * func_ov003_0221a888 @ 0x0221a888, 0x24 bytes, Thumb
 * func_ov003_0221a860 @ 0x0221a860, 0x26 bytes, Thumb
 * func_ov003_0221a7a0 @ 0x0221a7a0, 0xc0 bytes, Thumb
 */

#include "types.h"

typedef struct Vec48 {
    int data[12];
} Vec48;

typedef struct UnkStruct_0221b064 {
    char pad_00[0x8];
    int unk_08;
    char pad_0C[0x5c - 0xc];
    char unk_5C[0x198 - 0x5c];
    Vec48 unk_198;
    char pad_1C8[0x234 - 0x1c8];
    Vec48 unk_234;
    char pad_264[0x26c - 0x264];
    int unk_26C;
    char pad_270[0x2f8 - 0x270];
    char sub[0x308 - 0x2f8];
    char unk_308[1];
} UnkStruct_0221b064;

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned int unk_5C;
    unsigned char pad_60[0x64 - 0x60];
    unsigned int unk_64;
    unsigned char pad_68[0x26c - 0x68];
    unsigned int unk_26C;
    unsigned char pad_270[0x2a4 - 0x270];
    unsigned char unk_2A4[4];
    unsigned char pad_2A8[0x2b4 - 0x2a8];
    unsigned int unk_2B4;
    unsigned char pad_2B8[0x2bc - 0x2b8];
    unsigned int unk_2BC;
    unsigned char pad_2C0[0x2e0 - 0x2c0];
    unsigned char unk_2E0;
    unsigned char pad_2E1[0x2ec - 0x2e1];
    unsigned int unk_2EC;
    unsigned char pad_2F0[0x328 - 0x2f0];
    unsigned char unk_328[4];
    unsigned char pad_32C[0x36a - 0x32c];
    unsigned char unk_36A;
    unsigned char pad_36B[0x378 - 0x36b];
    unsigned short unk_378;
} UnkStruct_0221af94;

typedef struct {
    int x;
    int y;
    int z;
} Vec;

typedef struct {
    u8 pad_00[0x34];
    int unk_34;
    u8 pad2[0x44 - 0x38];
} UnkStruct_0221ac70;

typedef struct {
    u8 pad_00[0x8];
    int unk_08; // 0x08
    u8 pad_0C[0x5c - 0xc];
    Vec pos;    // 0x5c
    Vec unk_68; // 0x68
    u8 pad2[0x26c - 0x74];
    int unk_26C;               // 0x26c
    int unk_270;               // 0x270
    u8 unk_274[0x278 - 0x274]; // 0x274
    int unk_278;               // 0x278
    u8 pad_27C[0x284 - 0x27c];
    u8 unk_284; // 0x284
    u8 pad_285[0x2a4 - 0x285];
    u8 unk_2A4[0x2ec - 0x2a4]; // 0x2a4
    int unk_2EC;               // 0x2ec
    int unk_2F0;               // 0x2f0
    int unk_2F4;               // 0x2f4
    u8 pad_2F8[0x328 - 0x2f8];
    u8 unk_328[0x369 - 0x328]; // 0x328
    u8 unk_369;                // 0x369
    u8 pad_36A[0x378 - 0x36a];
    union {
        u16 u;
        struct {
            u16 : 4;
            u16 b4 : 1;
            u16 b5 : 1;
            u16 b6 : 1;
            u16 : 3;
            u16 b10 : 1;
            u16 : 5;
        } bits;
    } unk_378; // 0x378
    u8 pad_37A[0x39c - 0x37a];
    int unk_39C; // 0x39c
    int unk_3A0; // 0x3a0
} UnkStruct_0221ac70_2;

typedef struct {
    u32 x;
    u32 y;
    u32 z;
} Vec_0221ac24;

typedef struct {
    u8 pad_00[0x5c];
    u32 a;
    u32 b;
    u32 c;
    u8 pad_68[0x2e8 - 0x68];
    u8 byte;
    u8 pad_2E9[0x378 - 0x2e9];
    union {
        u16 u;
        struct {
            u16 : 6;
            u16 b6 : 1;
            u16 : 3;
            u16 b10 : 1;
            u16 : 5;
        } bits;
    } flags;
} UnkStruct_0221ac24;

struct UnkStruct_0221abf8 {
    char pad_00[0x39c];
    int unk_39C;
};

typedef struct {
    u8 pad_00[0x5c];
    int px; // 0x5c
    int py; // 0x60
    int pz; // 0x64
    u8 pad_68[0x26c - 0x68];
    int unk_26C; // 0x26c
    u8 pad_270[0x2b4 - 0x270];
    int unk_2B4; // 0x2b4
    u8 pad_2B8[0x2bc - 0x2b8];
    int unk_2BC; // 0x2bc
    u8 pad_2C0[0x2e0 - 0x2c0];
    u8 unk_2E0; // 0x2e0
    u8 pad_2E1[0x2f0 - 0x2e1];
    int unk_2F0; // 0x2f0
    int unk_2F4; // 0x2f4
    u8 pad_2F8[0x328 - 0x2f8];
    u8 unk_328[0x374 - 0x328]; // 0x328
    int unk_374;               // 0x374
    union {
        u16 u;
        struct {
            u16 : 7;
            u16 b7 : 1;
            u16 : 8;
        } bits;
    } unk_378; // 0x378
    u8 pad_37A[0x394 - 0x37a];
    short unk_394; // 0x394
    u8 pad_396[0x39c - 0x396];
    int unk_39C; // 0x39c
    int unk_3A0; // 0x3a0
} UnkStruct_0221a8e8;

typedef struct {
    u8 pad_00[0x5c];
    int px;
    int py;
    int pz;
    u8 pad_68[0x8e - 0x68];
    short unk_8E;
} UnkStruct_0221a8e8_2;

struct UnkStruct_ov003 {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
};

typedef struct {
    char pad_00[8];
    unsigned int unk_08;
    char pad_0C[0x60 - 0xc];
    int unk_60;
    char pad_64[0x26c - 0x64];
    int unk_26C;
    char pad_270[0x378 - 0x270];
    unsigned short a : 2;
    unsigned short b : 2;
    unsigned short c : 12;
} UnkStruct_0221a7a0;

extern short FX_SinCosTable_[];
extern int data_021fbdd0;
extern void func_020eabc8(int *vec, int val);
extern void func_0209a204(int *vec, void *a, void *b);
extern void func_0209a3c8(void *a);
extern void func_01ffd070(void *dst, void *a, void *b);
extern int func_0203f8d0(void *a, void *b);
extern void func_020e96c8(void *dst, int a, int b, int c);
extern void func_020e9774(void *dst, int val);
extern void func_0209a2ec(void *a, void *b);
extern void MTX_Concat43(void *a, void *b, void *c);
extern int func_02089cc0(void *a, int b);
extern int func_020044c0(void *a, int b, int c, int d);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern int VEC_Mag(Vec *);
extern int func_020e8ed8(int, int);
extern void func_020eaca0(Vec *, Vec *, Vec *);
extern void func_02031288(void *, Vec *, Vec *, int, int, UnkStruct_0221ac70_2 *, int);
extern void func_02089c20(void *, UnkStruct_0221ac70_2 *, int, int, int, int, int, int, int);
extern void func_02089fc8(void *);
extern int func_02034270(UnkStruct_0221ac70 *, Vec *, int, int);
extern void func_0203423c(UnkStruct_0221ac70 *);
extern int func_ov003_0221a35c(void *obj, int value);
extern UnkStruct_0221a8e8_2 *func_020961a8(int);
extern int func_020b6660(void);
extern void func_020e8a94(short *, int, int, int);
extern u32 func_020ea990(void *, void *);
extern int func_020e8b4c(int, int);
extern void func_020e8b60(int *, int, int, int);
extern int func_020ea9c8(Vec *);
extern int func_020044b0(void *, int, int, int);
extern int func_020b0594(int a, int b, int *c, int *d, int *e, int f, int g, int h);
extern unsigned char data_021f3b56[];

int func_ov003_0221a8d4(int *p);

void func_ov003_0221b064(UnkStruct_0221b064 *self, int param1, int param2)
{
    int vec0[3];
    int vec1[4];
    int arr1c[3];
    int arr28[3];
    Vec48 vec34;
    char arr64[0x30];
    int ret1;
    int idx1;
    int idx2;
    int k1;
    int k2;
    int tmp;

    if (param1 != 0) {
        idx2 = ((unsigned short) param2) >> 4;
        k2 = idx2 << 1;
        vec0[0] = FX_SinCosTable_[k2 + 1];
        vec0[1] = 0;
        vec0[2] = -FX_SinCosTable_[k2];

        idx1 = ((unsigned short) (param1 >> 1)) >> 4;
        k1 = idx1 << 1;
        func_020eabc8(vec0, FX_SinCosTable_[k1]);

        vec1[0] = vec0[0];
        vec1[1] = vec0[1];
        vec1[2] = vec0[2];
        vec1[3] = FX_SinCosTable_[k1 + 1];

        func_0209a204(vec1, &self->sub, &self->sub);

        if ((data_021fbdd0 & 7) == self->unk_08) {
            func_0209a3c8(&self->sub);
        }
    }

    func_01ffd070(arr28, &self->unk_5C, &self->unk_308);

    tmp = arr28[1] + self->unk_26C;
    arr28[1] = tmp;
    arr28[1] = tmp - 0x400;

    ret1 = func_0203f8d0(arr1c, arr28);
    func_020e96c8((void *) &vec34, arr1c[0], arr1c[1], arr1c[2]);
    func_020e9774((void *) &vec34, ret1);

    func_0209a2ec(&self->sub, (void *) arr64);
    MTX_Concat43((void *) arr64, (void *) &vec34, (void *) &vec34);

    self->unk_198 = vec34;
    self->unk_234 = vec34;
}

void func_ov003_0221af94(UnkStruct_0221af94 *self)
{
    if (self->unk_2E0 != 0) {
        if ((((unsigned int) self->unk_378 << 0x16) >> 0x1f) == 0) {
            self->unk_5C += self->unk_2B4;
            self->unk_64 += self->unk_2BC;
        }
        if (func_02089cc0(&self->unk_2A4, 4) != 0 && (int) self->unk_26C < 0xa00) {
            if (self->unk_36A == 0) {
                func_020044c0(&self->unk_328, 0x81c, 0x7f, 0);
            }
            self->unk_36A = 1;
        } else {
            self->unk_36A = 0;
        }
    } else {
        self->unk_36A = 0;
    }

    {
        int q = FX_Div(self->unk_26C - 0x800, 0xc00);
        int m = FX_MulFunc(q, 0x10cd);
        self->unk_2EC = (unsigned int) (m + 0xdec) << 2;
    }
}

void func_ov003_0221ac70(UnkStruct_0221ac70_2 *a)
{
    Vec v;
    UnkStruct_0221ac70 w2;
    int k;
    u32 hi;
    int lo;
    int st;
    int wm;
    int spd;
    int t2;
    int t14;
    int m;
    int ang;
    int d;
    int f;
    int r;
    int ok;
    int ok2;

    k = a->unk_378.bits.b4 != 0 ? 0xb : 0;
    if (a->unk_3A0 == 0 && a->unk_39C == 0) {
        a->pos.y -= 0x200;
    }
    func_02031288(a->unk_274, &a->pos, &a->unk_68, 0, a->unk_270, a, k);

    hi = a->unk_284;
    if (hi > a->unk_369) {
        if (a->unk_3A0 == 0 && a->unk_39C == 0) {
            func_020044c0(a->unk_328, 0x81d, 0x7f, 0);
        }
    }
    a->unk_369 = (u8) hi;

    lo = 0x20;
    if (a->unk_378.bits.b5 != 0) {
        lo |= 2;
    }
    st = 0x12;
    wm = (u8) a->unk_08;
    if (a->unk_39C == 0xb) {
        st = 0x11;
    }

    spd = FX_Div(0x41000, 0x64000);
    if (a->unk_26C < 0xa00) {
        spd = 0x1000;
    } else if (a->unk_26C < 0xe00) {
        spd = FX_Div((0x64 - ((0x23 * FX_Div(a->unk_26C - 0xa00, 0x400)) >> 12)) << 12, 0x64000);
    }
    d = a->unk_26C;
    t2 = FX_MulFunc(d, spd);
    func_02089c20(a->unk_2A4, a, t2, d * 2, lo, 0x2fc, st, wm, a->unk_2EC);
    func_02089fc8(a->unk_2A4);

    func_020eaca0(&v, &a->pos, &a->unk_68);
    m = VEC_Mag(&v);
    ang = (short) ((FX_Div(m, FX_MulFunc(0x323d, a->unk_26C)) >> 1) << 4);
    t14 = func_020e8ed8(v.x, v.z);

    if (func_ov003_0221a8d4((int *) a) != 0) {
        f = VEC_Mag(&v);
        if (f == 0) {
            a->unk_2F0 = 0;
            a->unk_2F4 = 0;
        } else {
            ok = 0;
            if (a->unk_3A0 == 0 && a->unk_39C == 1) {
                ok = 1;
            }
            if (ok != 0) {
                r = f - FX_Div(0x2000, 0xa5000);
            } else if (a->unk_3A0 == 0 && a->unk_39C == 5) {
                r = f - 0x155;
            } else {
                wm = a->unk_278;
                if ((wm & 1) != 0) {
                    if (a->unk_378.bits.b6 != 0) {
                        r = f - 0x155;
                    } else {
                        r = f - 0x28;
                    }
                } else if ((wm & 2) != 0) {
                    r = f - 0xaa;
                } else {
                    r = f - FX_Div(0x2000, 0xa0000);
                }
            }
            if (r < 0) {
                r = 0;
            }
            if (r > 0x400) {
                r = 0x400;
            }
            f = FX_Div(r, f);
            a->unk_2F0 = FX_MulFunc(v.x, f);
            a->unk_2F4 = FX_MulFunc(v.z, f);
        }
    } else {
        a->unk_2F0 = 0;
        a->unk_2F4 = 0;
    }

    func_02034270(&w2, &a->pos, 0, 0);
    if (w2.unk_34 == 3) {
        if (a->unk_378.bits.b10 == 0) {
            a->unk_26C = FX_MulFunc(a->unk_26C, (m >> 7) + 0x1000);
            if (a->unk_26C > 0x1400) {
                a->unk_26C = 0x1400;
            }
        }
    } else {
        ok2 = 0;
        if (a->unk_3A0 == 0 && a->unk_39C == 2) {
            ok2 = 1;
        }
        if (ok2 == 0) {
            if (a->unk_3A0 != 0 || a->unk_39C != 6) {
                a->unk_26C = FX_MulFunc(a->unk_26C, 0x1000 - (m >> 9));
                if (a->unk_26C < 0x800) {
                    a->unk_26C = 0x800;
                }
            }
        }
    }
    func_ov003_0221b064((UnkStruct_0221b064 *) a, ang, t14);
    func_0203423c(&w2);
}

int func_ov003_0221ac24(UnkStruct_0221ac24 *p, Vec_0221ac24 *q)
{
    if (p->flags.bits.b10 == 0 && p->flags.bits.b6 == 0 && p->byte == 0) {
        p->a = q->x;
        p->b = q->y;
        p->c = q->z;
        p->flags.u |= 0x400;
        return 1;
    }
    return 0;
}

int func_ov003_0221ac18(char *param0)
{
    return *(int *) (param0 + 0x26c);
}

int func_ov003_0221abf8(void *object, int flag)
{
    struct UnkStruct_0221abf8 *obj = object;
    if (obj->unk_39C < 7) {
        return func_ov003_0221a35c(obj, 3);
    }
    return 0;
}

int func_ov003_0221a8e8(UnkStruct_0221a8e8 *a, Vec *outPos, short *outAngle, int *outDist, int e, int f6)
{
    int t1;
    int dx;
    int dz;
    short ang[2];
    Vec vv[2];
    Vec v3;
    Vec v4;
    UnkStruct_0221a8e8_2 *ent;
    u32 dist;
    int savedX;
    int savedZ;
    Vec *ep;
    int q;
    int u;
    int tz;
    short d;
    short d2;
    short lim;

    ent = func_020961a8(4);
    if (func_020b6660() == 0) {
        return 0;
    }
    if (ent == 0) {
        return 0;
    }
    if (a->unk_3A0 != 0 || a->unk_39C != 0) {
        return 0;
    }
    if (a->unk_26C < 0xa00) {
        return 0;
    }
    if (e > 0xc32) {
        e = 0xc32;
    }

    if (a->unk_2E0 != 0) {
        a->px += a->unk_2B4;
        a->pz += a->unk_2BC;
        a->unk_378.u |= 0x200;
    }

    ang[0] = (short) f6;
    if (a->unk_378.bits.b7 != 0) {
        ang[0] = a->unk_394;
        func_020e8a94(ang, f6, 5, 0x2000);
    }

    savedX = a->unk_2F0;
    savedZ = a->unk_2F4;
    if (a->unk_378.bits.b7 == 0) {
        a->unk_2F0 = savedX >> 4;
        a->unk_2F4 = a->unk_2F4 >> 4;
    }

    t1 = FX_MulFunc(FX_MulFunc(e, 0x1b6), a->unk_374);
    dx = FX_MulFunc(t1, FX_SinCosTable_[((u16) ang[0] >> 4) * 2]);
    dz = FX_MulFunc(t1, FX_SinCosTable_[((u16) ang[0] >> 4) * 2 + 1]);
    a->unk_2F0 += dx;
    a->unk_2F4 += dz;
    a->px += a->unk_2F0;
    a->pz += a->unk_2F4;

    ang[1] = ent->unk_8E;
    func_020e8a94(&ang[1], f6, 8, 0x2000);

    ep = (Vec *) &ent->px;
    vv[0].x = ep->x;
    vv[0].y = ep->y;
    vv[0].z = ep->z;
    vv[1].x = vv[0].x + dx;
    vv[1].y = vv[0].y;
    vv[1].z = vv[0].z + dz;

    dist = (u32) func_020e8ed8(a->px - vv[1].x, a->pz - vv[1].z);
    if (func_020ea990((char *) a + 0x68, &vv[1]) > (u32) (a->unk_26C + 0x1000)) {
        a->px -= a->unk_2F0;
        a->pz -= a->unk_2F4;
        a->unk_2F0 = savedX;
        a->unk_2F4 = savedZ;
        return 0;
    }

    d = func_020e8b4c(dist, f6);
    lim = a->unk_378.bits.b7 != 0 ? 0x471c : 0x1000;
    if (d > lim) {
        a->px -= a->unk_2F0;
        a->pz -= a->unk_2F4;
        a->unk_2F0 = savedX;
        a->unk_2F4 = savedZ;
        return 0;
    }

    d2 = func_020e8b4c(ang[1], ang[0]);
    if (d2 > 0x471c) {
        a->px -= a->unk_2F0;
        a->pz -= a->unk_2F4;
        a->unk_2F0 = savedX;
        a->unk_2F4 = savedZ;
        return 0;
    }

    func_020eaca0(&v3, (Vec *) &a->px, &vv[1]);
    *outAngle = (short) func_020e8ed8(v3.x, v3.z);
    outPos->x = vv[1].x;
    outPos->y = vv[1].y;
    outPos->z = vv[1].z;
    a->unk_378.u |= 0x40;
    a->unk_394 = ang[0];
    func_020044b0(a->unk_328, 0x820, 0x7f, 0);
    q = FX_Div(a->unk_26C - 0xa00, 0xa00);
    u = FX_MulFunc(0xc00, 0x1000 - q) + 0x200;
    func_020e8b60(&a->unk_374, 0x1000, u, 0x1000);
    tz = a->unk_2F4;
    v4.x = a->unk_2F0;
    v4.y = 0;
    v4.z = tz;
    *outDist = func_020ea9c8(&v4) >> 1;
    return 1;
}

int func_ov003_0221a8d4(int *p)
{
    if (p[0xE7] < 7) {
        return 1;
    }
    return 0;
}

int func_ov003_0221a8c4(struct UnkStruct_ov003 *self)
{
    return self->unk_08 < 2;
}

int func_ov003_0221a8ac(void *argument0)
{
    if (func_ov003_0221a8c4((struct UnkStruct_ov003 *) argument0) == 0) {
        return 1;
    }
    return 0;
}

int func_ov003_0221a888(int *this)
{
    int result;
    int tmp;

    if (func_ov003_0221a8ac(this) != 0) {
        tmp = this[2] - 2;
        if ((tmp & 1) != 0) {
            result = 0;
        } else {
            result = 1;
        }
    } else {
        result = 0;
    }
    return result;
}

int func_ov003_0221a860(int a)
{
    if (func_ov003_0221a8ac((void *) a)) {
        if (func_ov003_0221a888((int *) a)) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}

void func_ov003_0221a7a0(UnkStruct_0221a7a0 *self)
{
    int r;
    int v10, v14, v18;

    if (func_ov003_0221a8c4((struct UnkStruct_ov003 *) self) != 0) {
        func_ov003_0221a35c(self, 0);
        return;
    }
    r = func_ov003_0221a860((int) self);
    self->a = (self->unk_08 - 2) >> 1;
    if (func_020b0594((unsigned int) data_021f3b56, self->a, &v10, &v14, &v18, 0, 0, 0) == 0) {
        return;
    }
    self->b = v18;
    if (r != 0) {
        self->unk_26C = v14;
        func_ov003_0221a35c(self, 9);
    } else {
        self->unk_26C = v10;
        self->unk_60 = v14 * 2 - (v14 >> 3) - (v10 >> 3) - 0x400;
        func_ov003_0221a35c(self, 0xb);
    }
}
