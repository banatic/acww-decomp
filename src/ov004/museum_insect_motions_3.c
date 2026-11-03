/* museum_insect_motions_3: 8 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02242334 @ 0x02242334, 0x13c bytes, Thumb
 * func_ov004_022422fc @ 0x022422fc, 0x38 bytes, Thumb
 * func_ov004_02242228 @ 0x02242228, 0xd4 bytes, Thumb
 * func_ov004_02242180 @ 0x02242180, 0xa8 bytes, Thumb
 * func_ov004_02242078 @ 0x02242078, 0x108 bytes, Thumb
 * func_ov004_02241f88 @ 0x02241f88, 0xf0 bytes, Thumb
 * func_ov004_02241e88 @ 0x02241e88, 0x100 bytes, Thumb
 * func_ov004_02241d20 @ 0x02241d20, 0x168 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02242228 {
    char unk_00[0x168];
    short unk_168;
    char unk_16A[0x172 - 0x16a];
    short unk_172;
    char unk_174[0x192 - 0x174];
    short unk_192;
    char unk_194[0x2c8 - 0x194];
    Vec3 pos;
} UnkStruct_02242228;

typedef struct UnkStruct_02242078 {
    short ang;
    short pad_02;
    Vec3 v;
    char unk_10[0x18 - 0x10];
    unsigned char flag;
} UnkStruct_02242078;

typedef struct UnkStruct_02242078_2 {
    char unk_00[0x98];
    short unk_98;
    char unk_9A[0x192 - 0x9a];
    short unk_192;
    char unk_194[2];
    signed char unk_196;
    char unk_197[0x2c8 - 0x197];
    Vec3 pos;
} UnkStruct_02242078_2;

struct UnkStruct_02241e88 {
    char unk_00[0xc];
    int unk_0C;
    char p1[4];
    u8 unk_14;
    char p2[7];
};

extern void *func_ov004_0223ee38(void);
extern int func_0200322c(void *a, void *b);
extern int func_020ea990(void *a, void *b);
extern int FX_MulFunc(int a, int b);
extern int func_020644cc(int k);
extern void func_ov004_02242a9c(void *self, int a, int b);
extern int func_ov004_02244c20(void *self);
extern unsigned char data_ov004_02259a24;
extern const short FX_SinCosTable_[];
extern void func_ov004_02244fb8(Vec3 *d, int a);
extern void func_020eac34(Vec3 *d, Vec3 *s, int k);
extern void VEC_Subtract(Vec3 *d, Vec3 *a, Vec3 *b);
extern void *func_ov004_02241ba8(void *self);
extern int func_ov004_02244e38(void *self, void *v);
extern short func_ov004_022447c0(int a, void *t);
extern short func_ov004_0224105c(int a);
extern int func_ov004_02244658(UnkStruct_02242078_2 *self, Vec3 *v);
extern int func_020e8870(short *cur, int target, int step);
extern void func_02056fcc(char *p, int a, int b, int c, int d);
extern void func_020550e4(char *p, int a);
extern char *func_ov004_0223edd8(void);
extern int func_020e8bb0(int *p, int a, int b, int c, int d);
extern int func_ov004_0221b1cc(void);
extern void func_020eaca0(int *v, void *p, void *q);
extern int func_020ea838(int *v);
extern int func_020ea90c(int *a, int *b);
extern const short data_02139d9c[];
extern void func_ov004_02244f20(void *self);
extern int func_ov004_02244be0(void *self, int k);

void func_ov004_02241d20(void *self, void *arg);

void func_ov004_02242334(void *self)
{
    void *other;
    int *A, *B;
    char *C;
    int t, dist;
    int m;
    short *D;
    int v;
    unsigned char f;
    int q;

    other = func_ov004_0223ee38();
    A = (int *) ((char *) self + 0x2c8);
    B = (int *) ((char *) other + 0x2c8);
    C = (char *) self;
    C = (char *) ((int) C + 0x34);
    m = func_0200322c(B, A);
    D = (short *) ((char *) self + 0x168);
    v = *(int *) ((char *) self + 0x4c);
    if (data_ov004_02259a24 % 0xa == 0) {
        if (func_020644cc(0x64) > 0x32) {
            *((unsigned char *) self + 0x170) = 1;
        } else {
            *((unsigned char *) self + 0x170) = 0;
        }
    }
    f = *((unsigned char *) self + 0x170);
    if (f != 0 && v < 0x1554) {
        m = (short) (m + 0xb6);
        v += 0xb6;
    } else if (f == 0 && v > 0) {
        m = (short) (m - 0xb6);
        v -= 0xb6;
    } else if (f != 0) {
        *((unsigned char *) self + 0x170) = 0;
    } else {
        *((unsigned char *) self + 0x170) = 1;
    }
    dist = func_020ea990(C, B);
    t = ((int) (unsigned short) m >> 4) * 2;
    A[0] = B[0] + FX_MulFunc(FX_SinCosTable_[t], dist);
    A[2] = B[2] + FX_MulFunc(FX_SinCosTable_[t + 1], dist);
    *(short *) ((char *) other + 0x192) = (short) m;
    q = func_0200322c(A, B);
    *(short *) ((char *) self + 0x192) = (short) q;
    func_ov004_02242a9c(self, q, *D);
    *(int *) ((char *) self + 0x4c) = v;
    *D = (short) (*D + 1);
    if (func_ov004_02244c20(self) != 0) {
        *(short *) ((char *) self + 0x172) = 0x19;
        *D = 0;
    }
}

void func_ov004_022422fc(char *self)
{
    if (func_ov004_02244c20(self) != 0) {
        *(short *) (self + 0x172) = 0x19;
        *(int *) ((char *) func_ov004_0223ee38() + 0x15c) = 0x1000;
        *(short *) (self + 0x168) = 0;
    }
}

void func_ov004_02242228(UnkStruct_02242228 *self)
{
    UnkStruct_02242228 *o;
    int t1, t2;
    Vec3 a;
    Vec3 b;
    Vec3 c;
    Vec3 d;
    Vec3 *p, *q;
    short *n;

    o = (UnkStruct_02242228 *) func_ov004_0223ee38();
    p = &self->pos;
    q = &o->pos;
    n = &self->unk_168;
    if (func_020ea990((void *) p, (void *) q) < 0x2000) {
        t1 = func_0200322c((void *) q, (void *) p);
        o->unk_192 = (short) t1;
        func_ov004_02244fb8(&a, t1);
        func_ov004_02242a9c((void *) o, t1, *n);
        t2 = func_0200322c((void *) p, (void *) q);
        self->unk_192 = (short) t2;
        func_ov004_02244fb8(&b, t2);
        func_ov004_02242a9c((void *) self, t2, *n);
        func_020eac34(&c, &b, 0x4000);
        VEC_Subtract(p, &c, p);
        func_020eac34(&d, &a, 0x4000);
        VEC_Subtract(q, &d, q);
        *n = (short) (*n + 1);
    } else if (func_ov004_02244c20((void *) self) != 0) {
        self->unk_172 = 0x19;
        *n = 0;
    }
}

void func_ov004_02242180(char *self)
{
    void *t = func_ov004_02241ba8(self);
    if (func_ov004_02244e38(self, self + 0x2c8) != 0) {
        *(short *) (self + 0x172) = 3;
    } else if (func_ov004_02244c20(self) != 0) {
        if (t != 0) {
            *(short *) (self + 0xac) = func_ov004_022447c0(*(short *) (self + 0x192), t);
        } else {
            *(short *) (self + 0xac) = func_ov004_0224105c(0x10);
        }
        *(u8 *) (self + 0x9a) = 0;
        *(short *) (self + 0x172) = 0x19;
        if (*(u8 *) (self + 0x22) != 0) {
            *(int *) (self + 0x174) = (short) (0x14 * (func_020644cc(6) + 1));
        } else {
            *(int *) (self + 0x174) = (short) (0x14 * (func_020644cc(0x1e) + 5));
        }
    }
}

int func_ov004_02242078(UnkStruct_02242078_2 *self)
{
    UnkStruct_02242078 info;
    int rc, ang, v;
    Vec3 *p;
    short *t;
    char *b;

    rc = func_ov004_02244658(self, &info.v);
    p = &self->pos;
    t = &self->unk_98;
    if (info.flag != 0) {
        if (rc == 3 || *t != 0) {
            ang = func_0200322c((void *) p, (void *) (&info.v));
            info.ang = self->unk_192;
            b = (char *) self + 0xb0;
            func_020e8870(&info.ang, ang, 0x38e);
            self->unk_192 = info.ang;
            if (self->unk_196 == 0x37) {
                v = *(int *) (b + 0xa0) >> 12;
                if ((unsigned short) v < 0xb && (unsigned short) (*(int *) (b + 0xa4) >> 12) <= 2) {
                    func_02056fcc(b + 0x9c, 0xb, 1, 0x1000, 3);
                } else if ((unsigned short) v < 0xe && (unsigned short) (*(int *) (b + 0xa4) >> 12) < 0xa) {
                    func_02056fcc(b + 0x9c, 0xe, 0, 0x1000, 0xa);
                } else if ((unsigned short) (*(int *) (b + 0xa4) >> 12) == 0xd && (unsigned short) v > 0xa) {
                    func_020550e4(b, 0xa);
                }
            }
            if (*t > 0) {
                *t = (short) (*t - 1);
            } else {
                *t = 0x3c;
            }
            return 1;
        }
    }
    return 0;
}

void func_ov004_02241f88(char *self)
{
    char *o;
    u8 c = *(u8 *) (self + 0x196);
    int tmp;
    int v;
    if (c == 0x23) {
        o = func_ov004_0223edd8();
    }
    switch (*(short *) (self + 0x172)) {
        case 4:
            tmp = *(int *) (self + 0x15c);
            if (func_020e8bb0(&tmp, 0x1000, 0x66, 0x1000, 0x29) == 0) {
                *(short *) (self + 0x172) = 5;
            }
            *(int *) (self + 0x15c) = tmp;
            break;
        case 5:
            if (func_ov004_02244c20(self) != 0) {
                *(short *) (self + 0x172) = 0x19;
                *(int *) (self + 0x15c) = 0;
                if (c == 0x23) {
                    v = (short) (0x14 * (func_020644cc(3) + 2));
                    if (*(u8 *) (self + 0x22) == 0) {
                        v = (short) (3 * v);
                    }
                    *(int *) (self + 0x174) = v;
                    *(short *) (o + 0x98) = (short) v;
                } else {
                    *(int *) (self + 0x174) = *(short *) (self + 0x98);
                }
            }
            break;
        default:
            if (func_ov004_02244c20(self) != 0) {
                *(short *) (self + 0x172) = 4;
                if (c == 0x23) {
                    v = (short) (0x14 * (func_020644cc(9) + 2));
                    *(int *) (self + 0x174) = v;
                    *(short *) (o + 0x98) = (short) v;
                } else if (*(short *) (self + 0x98) > 0) {
                    *(int *) (self + 0x174) = *(short *) (self + 0x98);
                }
            }
            break;
    }
}

void func_ov004_02241e88(char *self)
{
    struct UnkStruct_02241e88 s;
    short t;
    u8 b;
    int r = func_ov004_02244658((UnkStruct_02242078_2 *) self, (Vec3 *) (&s));
    if (*(short *) (self + 0x9c) > 0x50) {
        *(short *) (self + 0x9c) = 0x50;
    }
    switch (*(short *) (self + 0x172)) {
        case 4:
            func_ov004_02241d20(self, (void *) (&s));
            break;
        case 3:
            t = *(short *) (self + 0x192);
            if (func_020e8870(&t, *(short *) (self + 0xac), 0x2000) != 0) {
                *(short *) (self + 0x172) = 4;
            }
            *(short *) (self + 0x192) = t;
            break;
        default:
            if (r == 3) {
                *(short *) (self + 0xac) = (short) func_0200322c(&s, self + 0x2c8);
                *(int *) (self + 0x174) = 0x14 * (func_020644cc(4) + 2);
                *(short *) (self + 0x172) = 3;
            } else if (func_ov004_02244c20(self) != 0) {
                *(short *) (self + 0x172) = 4;
                *(int *) (self + 0x174) = 0x14 * (func_020644cc(4) + 1);
            }
            break;
    }

    if (*(int *) (self + 0x4c) == 0) {
        b = s.unk_14;
        if (b != 0 && b > 0 && s.unk_0C > 0 && *(short *) (self + 0x98) == 0) {
            if (func_020ea990(&s, self + 0x2c8) < 0xe66) {
                func_ov004_0221b1cc();
                *(int *) (self + 0x4c) = 1;
            }
        }
    }
}

void func_ov004_02241d20(void *self, void *arg)
{
    int a, b;
    short s;
    int v1[3], v2[3];
    short *cnt = (short *) ((char *) self + 0x98);
    int *m = (int *) ((char *) self + 0x2c8);
    int t;

    a = (int) func_ov004_02241ba8(self);
    s = *(short *) ((char *) self + 0x192);
    func_020eaca0(v1, arg, (char *) self + 0x2c8);
    func_ov004_02244fb8((Vec3 *) v2, s);
    func_020ea838(v2);
    func_020ea838(v1);
    b = func_020ea90c(v2, v1);
    if (*((unsigned char *) arg + 0x14) != 0 && b > 0) {
        if (func_020ea990(m, arg) < 0x1800) {
            if (b > data_02139d9c[1]) {
                *cnt = (short) (*cnt + 1);
            }
        } else if (func_020ea990(m, arg) < 0x2800 && a == 0) {
            func_020e8870(&s, func_0200322c(arg, m), 0xaaa);
            *(short *) ((char *) self + 0x192) = s;
        }
    }
    if (*cnt > 0) {
        t = *cnt << 12;
        m[1] = FX_MulFunc(0x99a - FX_MulFunc(0xcd, t), t);
        if (m[1] < 3) {
            m[1] = 3;
            *cnt = 0;
        } else {
            *cnt = (short) (*cnt + 1);
        }
        func_ov004_02244f20(self);
        func_ov004_02244be0(self, 1);
    } else {
        func_ov004_02244be0(self, 0);
        if ((((unsigned int) *(int *) ((char *) self + 0x154) << 4) >> 16) != 0) {
            func_020550e4((char *) ((char *) self + 0xb0), 0);
        }
    }
    if (func_ov004_02244c20(self) != 0 && *cnt == 0) {
        *(int *) ((char *) self + 0x174) = 0x14 * (func_020644cc(0xa) + 3);
        *(short *) ((char *) self + 0x172) = 0x19;
    }
}
