/* museum_insect_motions_7: 33 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02244fb8 @ 0x02244fb8, 0x14 bytes, Thumb
 * func_ov004_02244f90 @ 0x02244f90, 0x28 bytes, Thumb
 * func_ov004_02244f48 @ 0x02244f48, 0x48 bytes, Thumb
 * func_ov004_02244f20 @ 0x02244f20, 0x28 bytes, Thumb
 * func_ov004_02244e94 @ 0x02244e94, 0x8c bytes, Thumb
 * func_ov004_02244e38 @ 0x02244e38, 0x5a bytes, Thumb
 * func_ov004_02244d58 @ 0x02244d58, 0xe0 bytes, Thumb
 * func_ov004_02244c40 @ 0x02244c40, 0x118 bytes, Thumb
 * func_ov004_02244c20 @ 0x02244c20, 0x20 bytes, Thumb
 * func_ov004_02244be0 @ 0x02244be0, 0x40 bytes, Thumb
 * func_ov004_02244ae4 @ 0x02244ae4, 0xfc bytes, Thumb
 * func_ov004_022449ec @ 0x022449ec, 0xf8 bytes, Thumb
 * func_ov004_0224497c @ 0x0224497c, 0x70 bytes, Thumb
 * func_ov004_02244904 @ 0x02244904, 0x78 bytes, Thumb
 * func_ov004_0224489c @ 0x0224489c, 0x68 bytes, Thumb
 * func_ov004_022447c0 @ 0x022447c0, 0xdc bytes, Thumb
 * func_ov004_02244774 @ 0x02244774, 0x4c bytes, Thumb
 * func_ov004_02244764 @ 0x02244764, 0x10 bytes, Thumb
 * func_ov004_02244658 @ 0x02244658, 0x10c bytes, Thumb
 * func_ov004_02244620 @ 0x02244620, 0x38 bytes, Thumb
 * func_ov004_0224457c @ 0x0224457c, 0xa4 bytes, Thumb
 * func_ov004_022444f0 @ 0x022444f0, 0x8c bytes, Thumb
 * func_ov004_022442b4 @ 0x022442b4, 0x23c bytes, Thumb
 * func_ov004_02244224 @ 0x02244224, 0x90 bytes, Thumb
 * func_ov004_0224412c @ 0x0224412c, 0xf8 bytes, Thumb
 * func_ov004_02244094 @ 0x02244094, 0x98 bytes, Thumb
 * func_ov004_02243fec @ 0x02243fec, 0xa8 bytes, Thumb
 * func_ov004_02243f0c @ 0x02243f0c, 0xe0 bytes, Thumb
 * func_ov004_02243e04 @ 0x02243e04, 0x108 bytes, Thumb
 * func_ov004_02243cb0 @ 0x02243cb0, 0x154 bytes, Thumb
 * func_ov004_02243c30 @ 0x02243c30, 0x80 bytes, Thumb
 * func_ov004_02243c04 @ 0x02243c04, 0x2c bytes, Thumb
 * func_ov004_02243bb0 @ 0x02243bb0, 0x54 bytes, Thumb
 */

#include "types.h"

#define B(o) (*(u8 *) (self + (o)))
#define C(o) (*(signed char *) (self + (o)))
#define S(o) (*(short *) (self + (o)))
#define W(o) (*(int *) (self + (o)))
#define V(o) ((Vec *) (self + (o)))

typedef struct {
    long x, y, z;
} UnkStruct_02244f48;

typedef struct {
    unsigned int a : 12;
    unsigned int b : 16;
    unsigned int c : 4;
} BF;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02244e38 {
    char unk_00[0x58];
    int xmin;
    int zmin;
    int xmax;
    int zmax;
} UnkStruct_02244e38;

typedef struct UnkStruct_02244d58 {
    char unk_00[0x50];
    unsigned char unk_50;
    char unk_51[0x54 - 0x51];
    int unk_54;
    char unk_58[0xa8 - 0x58];
    int unk_A8;
    char unk_AC[0x168 - 0xac];
    short unk_168;
    char unk_16A[0x172 - 0x16a];
    short unk_172;
    int unk_174;
    char unk_178[0x192 - 0x178];
    short unk_192;
    char unk_194[0x2c8 - 0x194];
    Vec3 pos;
} UnkStruct_02244d58;

struct UnkStruct_02244be0 {
    u8 pad_00[0x24];
    u8 sub[0x196 - 0x24];
    signed char id;
};

typedef struct {
    int x, y, z;
} Vec;

typedef struct UnkStruct_0224497c {
    char unk_00[0x54];
    int unk_54;
    char unk_58[0xa8 - 0x58];
    int unk_A8;
    char unk_AC[0x2c8 - 0xac];
    Vec3 pos;
} UnkStruct_0224497c;

typedef struct UnkStruct_02244904_2 {
    char unk_00[0x54];
    int unk_54;
    char unk_58[0x9a - 0x58];
    unsigned char unk_9A;
    char unk_9B[1];
    short unk_9C;
    short unk_9E;
    char unk_A0[0xa8 - 0xa0];
    int unk_A8;
    char unk_AC[0x172 - 0xac];
    short unk_172;
    int unk_174;
    char unk_178[0x2c8 - 0x178];
    Vec3 pos;
} UnkStruct_02244904_2;

typedef struct {
    Vec3 v;
    char unk_0C[0x14 - 0x0c];
    unsigned char unk_14;
    char unk_15[7];
} UnkStruct_02244904;

typedef struct UnkStruct_0224489c {
    char unk_00[0x40];
    Vec3 tgt;
    char unk_4C[0x192 - 0x4c];
    short ang;
    char unk_194[0x2c8 - 0x194];
    Vec3 pos;
} UnkStruct_0224489c;

typedef struct {
    Vec position;
    int value;
    int distance;
    unsigned char present;
} Sample;

typedef struct UnkStruct_0224457c {
    char unk_00[0x4c];
    int unk_4C;
    char unk_50[0x170 - 0x50];
    unsigned char unk_170;
} UnkStruct_0224457c;

typedef struct UnkStruct_022444f0 {
    char unk_00[0x54];
    int unk_54;
    char unk_58[0xa8 - 0x58];
    int unk_A8;
    char unk_AC[0x16a - 0xac];
    short unk_16A;
    char unk_16C[0x170 - 0x16c];
    unsigned char unk_170;
    char unk_171[0x2c8 - 0x171];
    Vec3 pos;
} UnkStruct_022444f0;

typedef struct UnkStruct_02244224 {
    char unk_00[0x40];
    Vec3 tgt;
    char unk_4C[0xae - 0x4c];
    unsigned char unk_AE;
    char unk_AF[0x172 - 0xaf];
    short unk_172;
    int unk_174;
    char unk_178[0x192 - 0x178];
    short ang;
    char unk_194[0x196 - 0x194];
    signed char unk_196;
    char unk_197[0x2c8 - 0x197];
    Vec3 pos;
} UnkStruct_02244224;

typedef struct UnkStruct_02244094 {
    char unk_00[0x34];
    Vec3 tgt;
    char unk_40[0x4c - 0x40];
    int unk_4C;
    char unk_50[0xa8 - 0x50];
    int unk_A8;
    char unk_AC[0x16c - 0xac];
    int unk_16C;
    unsigned char unk_170;
    char unk_171[0x172 - 0x171];
    short unk_172;
    char unk_174[0x192 - 0x174];
    short ang;
    char unk_194[0x2c8 - 0x194];
    Vec3 pos;
} UnkStruct_02244094;

typedef struct UnkStruct_02243fec {
    char unk_00[0x34];
    Vec3 dst;
    char unk_40[0x9a - 0x40];
    unsigned char unk_9A;
    char unk_9B[0xa4 - 0x9b];
    unsigned char unk_A4;
    char unk_A5[0xac - 0xa5];
    short unk_AC;
    char unk_AE[0x168 - 0xae];
    short unk_168;
    char unk_16A[0x172 - 0x16a];
    short unk_172;
    char unk_174[0x192 - 0x174];
    short ang;
    char unk_194[0x196 - 0x194];
    signed char unk_196;
    char unk_197[0x2c8 - 0x197];
    Vec3 pos;
} UnkStruct_02243fec;

typedef struct UnkStruct_02243e04 {
    char unk_00[0x20];
    unsigned char unk_20;
    char unk_21[1];
    unsigned char unk_22;
    char unk_23[0x34 - 0x23];
    Vec3 unk_34;
    char unk_40[0x98 - 0x40];
    short unk_98;
    char unk_9A[0x9c - 0x9a];
    short unk_9C;
    char unk_9E[0xa4 - 0x9e];
    unsigned char unk_A4;
    char unk_A5[0xac - 0xa5];
    short unk_AC;
    char unk_AE[0x168 - 0xae];
    short unk_168;
    char unk_16A[0x172 - 0x16a];
    short unk_172;
    char unk_174[0x192 - 0x174];
    short unk_192;
    char unk_194[0x2c8 - 0x194];
    Vec3 pos;
} UnkStruct_02243e04;

typedef struct UnkStruct_02243bb0 {
    char unk_00[0x98];
    short unk_98;
    signed char unk_9A;
    char unk_9B[0x168 - 0x9b];
    short unk_168;
    char unk_16A[0x172 - 0x16a];
    short unk_172;
} UnkStruct_02243bb0;

extern void func_020ea6e0(void *p, int a);
extern int func_020644cc(int a);
extern short FX_SinCosTable_[];
extern int func_02034270(void *w, Vec3 *v, int a, int b);
extern int func_020341c8(void *w, int a);
extern void func_0203423c(void *w);
extern void VEC_Subtract(Vec3 *d, Vec3 *a, Vec3 *b);
extern void func_ov004_02241b5c(Vec3 *d, Vec3 *a, int k);
extern void VEC_Add(Vec3 *d, Vec3 *a, Vec3 *b);
extern void func_020550e4(void *, int);
extern void func_02056fcc(void *, unsigned int, unsigned char, unsigned int, unsigned short);
extern unsigned char data_ov004_02259a24;
extern void func_020042a0(void *p, int a);
extern void func_02004290(void *p, int a);
extern int FX_MulFunc(int, int);
extern int FX_Div(int numer, int denom);
extern int func_0200322c(Vec3 *a, Vec3 *b);
extern int func_020ea990(Vec3 *a, Vec3 *b);
extern int func_020e8870(short *, int, int);
extern unsigned char *func_020961a8(int);
extern int func_020e91ac(Vec3 *a, Vec3 *b, int c, int d, int e);
extern short func_ov004_0224105c(int);
extern int func_020e908c(Vec3 *a, Vec3 *b, int c, int d, int e);
extern int func_020e8bb0(int *a, int b, int c, int d, int e);
extern int func_ov004_02245174(UnkStruct_02243fec *self);
extern int func_ov004_02245188(void *);
extern void func_ov004_02243af4(UnkStruct_02243bb0 *self, short *n);
extern void func_ov004_022439ec(UnkStruct_02243bb0 *self, short *n);

int func_ov004_02244c20(char *self);
int func_ov004_02244ae4(int kind, int variant);
int func_ov004_02244904(UnkStruct_02244904_2 *self);
void func_ov004_0224489c(UnkStruct_0224489c *self, short *da, int *dist, Vec3 *t);
int func_ov004_02244658(unsigned char *self, Sample *sample);
void func_ov004_0224457c(UnkStruct_0224457c *self);
void func_ov004_022444f0(UnkStruct_022444f0 *self, short *p);
void func_ov004_02244224(UnkStruct_02244224 *self);
void func_ov004_0224412c(unsigned char *self);
void func_ov004_02244094(UnkStruct_02244094 *self);
void func_ov004_02243fec(UnkStruct_02243fec *self);
int func_ov004_02243f0c(unsigned char *self);
void func_ov004_02243cb0(unsigned char *self);
void *func_ov004_02243c30(void *self, short *out);
void func_ov004_02243c04(char *self);

void func_ov004_02244fb8(int *p, int a)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0x29;
    func_020ea6e0(p, a);
}

short func_ov004_02244f90(void)
{
    unsigned char v = (unsigned char) func_020644cc(0x10);
    int r = v;
    if (v > 8) {
        r = -(v - 8);
    }
    return (short) (0xaaa * r);
}

void func_ov004_02244f48(UnkStruct_02244f48 *out, UnkStruct_02244f48 *base, int ang, long r)
{
    long z;
    int k;
    k = ((int) (unsigned short) ang >> 4) * 2;
    z = base->z + (long) FX_MulFunc((long) r, (long) (FX_SinCosTable_[k + 1]));
    out->x = base->x + (long) FX_MulFunc((long) r, (long) FX_SinCosTable_[k]);
    out->y = 0;
    out->z = z;
}

void func_ov004_02244f20(char *self)
{
    char *p = self + 0xb0;
    if (((BF *) (p + 0xa4))->b == 1) {
        func_020550e4((void *) p, 2);
    } else {
        func_020550e4((void *) p, 1);
    }
}

int func_ov004_02244e94(Vec3 *a, Vec3 *b)
{
    Vec3 v1;
    char w1[0x40];
    Vec3 v2;
    char w2[0x40];
    int r, f, t;

    r = 1;
    t = b->z;
    v1.x = a->x;
    v1.y = 0;
    v1.z = t;
    func_02034270(w1, &v1, 0, 0);
    if (func_020341c8(w1, 0) > 0x200) {
        f = 1;
    } else {
        f = 0;
    }
    func_0203423c(w1);
    if (f != 0) {
        a->x = b->x;
        r = 0;
    }
    t = a->z;
    v2.x = b->x;
    v2.y = 0;
    v2.z = t;
    func_02034270(w2, &v2, 0, 0);
    if (func_020341c8(w2, 0) > 0x200) {
        f = 1;
    } else {
        f = 0;
    }
    func_0203423c(w2);
    if (f != 0) {
        a->z = b->z;
        r = 0;
    }
    return r;
}

int func_ov004_02244e38(UnkStruct_02244e38 *self, Vec3 *p)
{
    unsigned char f;
    int *hi, *lo;

    hi = &self->xmax;
    lo = (int *) ((int) self + 0x58);
    f = 0;
    if (p->x < self->xmin) {
        p->x = self->xmin;
        f = 1;
    } else if (p->x > hi[0]) {
        p->x = hi[0];
        f |= 2;
    }
    if (p->z < lo[1]) {
        p->z = lo[1];
        f |= 4;
    } else if (p->z > hi[1]) {
        p->z = hi[1];
        f |= 8;
    }
    return f;
}

void func_ov004_02244d58(UnkStruct_02244d58 *self)
{
    short sh;
    int n;
    Vec3 w;
    Vec3 *p;
    int r;

    if (func_ov004_02244c20((char *) self) != 0) {
        p = &self->pos;
        func_ov004_0224489c((UnkStruct_0224489c *) self, &sh, &n, &w);
        if (n <= 0x400 && p->y <= w.y + 0x200 && p->y >= w.y - 0x200) {
            self->unk_172 = 6;
            self->unk_174 = (short) (0x14 * (func_020644cc(0xa) + 0xa));
            self->unk_168 = 0;
        } else {
            r = self->unk_50;
            if (func_020644cc(0x64) > r - 0x14) {
                if (n <= 0x3000) {
                    self->unk_54 = w.y;
                } else {
                    self->unk_54 = self->unk_A8;
                }
                self->unk_192 = (short) (sh + self->unk_192);
                VEC_Subtract(&w, p, &w);
                func_ov004_02241b5c(&w, &w, 1);
                VEC_Add(p, &w, p);
            }
        }
    } else {
        self->unk_54 = self->unk_A8;
    }
}

void func_ov004_02244c40(unsigned char *self)
{
    unsigned char kind = self[0x196];
    func_ov004_02244904((UnkStruct_02244904_2 *) self);
    if (!(func_ov004_02244c20((char *) self) && self[0x22]) && !self[0x9a]) {
        if (kind == 10 || kind == 51) {
            if ((unsigned short) (*(unsigned int *) (self + 0x154) >> 12) != 0) {
                func_020550e4(self + 0xb0, 0);
            }
        } else if ((unsigned short) (*(unsigned int *) (self + 0x150) >> 12) < 12) {
            func_02056fcc(self + 0x14c, 17, 1, 0x1000, 9);
        } else if ((unsigned short) (*(unsigned int *) (self + 0x154) >> 12) == 16) {
            if ((self[0x22] || data_ov004_02259a24 % 10 == 0) && func_020644cc(100) > 95) {
                func_02056fcc(self + 0x14c, 17, 1, 0x1000, 9);
            }
        }
    } else {
        *(short *) (self + 0x172) = 25;
        *(int *) (self + 0x54) = *(int *) (self + 0xa8);
        *(int *) (self + 0x174) = (func_020644cc(10) + 16) * 20;
        if (kind != 10 && kind != 51) {
            func_02056fcc(self + 0x14c, 9, 0, *(unsigned int *) (self + 0x4c), 0);
        } else {
            func_020550e4(self + 0xb0, 1);
        }
    }
}

int func_ov004_02244c20(char *self)
{
    // DECLS
    // ENDDECLS
    if ((short) *(int *) (self + 0x174) > 0x0) {
        *(int *) (self + 0x174) = ((short) *(int *) (self + 0x174) - 0x1);
        return 0x0;
    }
    return 0x1;
}

int func_ov004_02244be0(struct UnkStruct_02244be0 *self, int mode)
{
    int r;

    r = func_ov004_02244ae4(self->id, mode);
    if (r >= 0) {
        if (mode == 1) {
            func_020042a0(&self->sub, r);
        } else {
            func_02004290(&self->sub, r);
        }
        return 1;
    }
    return 0;
}

int func_ov004_02244ae4(int kind, int variant)
{
    switch (kind) {
        case 10:
            return 0x831;
        case 51:
            return 0x823;
        case 29:
            return 0x825;
        case 27:
            return 0x826;
        case 28:
            return 0x82c;
        case 16:
            return 0x822;
        case 17:
            return 0x827;
        case 18:
            return 0x82e;
        case 19:
            return 0x824;
        case 50:
            return 0x828;
        case 30:
            if (variant == 0) {
                return 0x829;
            }
            return 0x82a;
        case 54:
            return 0x833;
        case 55:
            return 0x835;
        case 52:
            switch (variant) {
                case 0:
                    return 0x225;
                case 1:
                    return 0x226;
            }
            break;
    }
    return -1;
}

void func_ov004_022449ec(unsigned char *self, int step, int period, unsigned int threshold)
{
    short angle = *(short *) (self + 0x192);
    unsigned char direction = self[0xae];
    unsigned char random = (unsigned char) func_020644cc(100);
    Vec *position = (Vec *) (self + 0x2c8);
    Vec offset;
    if (data_ov004_02259a24 % period == 0 && random > threshold) {
        if (!direction) {
            direction = 1;
        } else {
            direction = 0;
        }
        self[0xae] = direction;
    }
    if (random > self[0x50]) {
        if (direction) {
            angle += step;
        } else {
            angle -= step;
        }
    }
    func_ov004_02244fb8((int *) (&offset), angle);
    *(short *) (self + 0x192) = angle;
    if (self[0x9a]) {
        position->x += FX_MulFunc(FX_MulFunc(0x1800, *(int *) (self + 0x16c) << 12), offset.x);
        position->z += FX_MulFunc(FX_MulFunc(0x1800, *(int *) (self + 0x16c) << 12), offset.z);
    } else {
        position->x += FX_MulFunc(*(int *) (self + 0x16c) << 12, offset.x);
        position->z += FX_MulFunc(*(int *) (self + 0x16c) << 12, offset.z);
    }
}

void func_ov004_0224497c(UnkStruct_0224497c *self, int ang, int c, int d)
{
    int v;
    Vec3 *p;

    p = &self->pos;
    v = FX_Div(FX_SinCosTable_[((unsigned short) ang >> 4) << 1], d);
    if (self->unk_54 != self->unk_A8) {
        c = FX_MulFunc(c, 0x800);
    }
    if ((v > 0 && p->y + v < c + self->unk_54) || (v < 0 && p->y + v > self->unk_54 - c)) {
        p->y = p->y + v;
    }
}

int func_ov004_02244904(UnkStruct_02244904_2 *self)
{
    UnkStruct_02244904 s;
    int r;

    r = func_ov004_02244658((unsigned char *) self, (Sample *) (&s));
    if (s.unk_14 != 0 && self->unk_9A == 0 && self->unk_9C >= self->unk_9E) {
        *(short *) ((char *) self + 0xac) = (short) func_0200322c(&s.v, &self->pos);
        self->unk_174 = (func_020644cc(4) + 0xa) * 0x14;
        self->unk_172 = 7;
        self->unk_9A = 1;
        self->unk_54 = self->unk_A8;
    }
    return r;
}

void func_ov004_0224489c(UnkStruct_0224489c *self, short *da, int *dist, Vec3 *t)
{
    Vec3 *p, *s;
    short ang;

    p = &self->pos;
    s = &self->tgt;
    t->x = self->tgt.x;
    t->y = s->y;
    t->z = s->z;
    ang = self->ang;
    *da = (short) (func_0200322c(p, t) - ang);
    if (*da > 0x38e) {
        *da = 0x38e;
    } else if (*da < -0x38e) {
        *da = -0x38e;
    }
    *dist = func_020ea990(t, p);
}

short func_ov004_022447c0(short ang, int mode)
{
    short orig;
    unsigned char r;

    orig = ang;
    r = (unsigned char) func_020644cc(0x64);
    if (mode == 3) {
        ang = (short) (ang + 0x8000);
        if (r < 5) {
            ang = (short) (ang + 0x2aaa);
        } else if (r < 0xa) {
            ang = (short) (ang - 0x2aaa);
        }
    } else if ((mode == 1 && (ang < -0x4000 || (ang >= 0 && ang < 0x4000))) ||
               (mode == 2 && (ang > 0x4000 || (ang <= 0 && ang > -0x4000)))) {
        ang = (short) (-ang);
    } else if (ang >= 0) {
        ang = (short) (0x8000 - ang);
    } else {
        ang = (short) (-0x8000 - ang);
    }
    if (r > 0x50) {
        if (ang - orig >= 0) {
            ang = (short) (ang + 0x1554);
        } else {
            ang = (short) (ang - 0x1554);
        }
    }
    if (ang == orig) {
        if (ang >= 0) {
            ang = (short) (ang + 0xaaa);
        } else {
            ang = (short) (ang - 0xaaa);
        }
    }
    return ang;
}

void func_ov004_02244774(char *self, int a, int b)
{
    short t = *(short *) (self + 0x192);
    if (func_020e8870(&t, *(short *) (self + 0xac), 0xe38) != 0) {
        *(short *) (self + 0x172) = (short) b;
        *(char *) (self + 0x170) = (char) a;
    }
    *(short *) (self + 0x192) = t;
}

int func_ov004_02244764(char *self)
{
    // DECLS
    char frame[0x1c];
    // ENDDECLS
    return func_ov004_02244658((unsigned char *) self, (Sample *) frame);
}

int func_ov004_02244658(unsigned char *self, Sample *sample)
{
    short amount = *(short *) (self + 0x9c);
    short before = amount;
    short threshold = *(short *) (self + 0x9e);
    unsigned char *other = func_020961a8(4);
    if (other) {
        Vec *p;
        sample->present = 1;
        sample->value = *(int *) (other + 0x98);
        p = (Vec *) (other + 0x5c);
        sample->position.x = p->x;
        sample->position.y = p->y;
        sample->position.z = p->z;
        sample->distance = func_020ea990((Vec3 *) ((Vec *) (self + 0x2c8)), (Vec3 *) (&sample->position));
        if (sample->distance < 0x2000) {
            amount += 25;
        } else if (sample->distance > *(int *) (self + 0xa0) || sample->value == 0) {
            --amount;
        } else if (sample->value <= 1000) {
            ++amount;
        } else if (sample->value <= 1100) {
            amount += 3;
        } else if (sample->value <= 1168) {
            amount += 5;
        } else if (sample->value == 1169) {
            amount += 8;
        } else {
            amount += 15;
        }
        if (amount < 0) {
            amount = 0;
        } else if (amount > 255) {
            amount = 255;
        }
        *(short *) (self + 0x9c) = (unsigned char) amount;
        if (threshold <= amount) {
            if (threshold > before) {
                return 1;
            }
            return 3;
        } else if (threshold > amount && threshold <= before) {
            return 2;
        }
    } else {
        sample->present = 0;
        return -1;
    }
    return 0;
}

void func_ov004_02244620(char *self)
{
    switch (*(short *) (self + 0x172)) {
        case 0:
            func_ov004_0224457c((UnkStruct_0224457c *) self);
            break;
        case 6:
            func_ov004_02244c40((unsigned char *) self);
            break;
        default:
            *(char *) (self + 0x9a) = 0;
            *(short *) (self + 0x172) = 0;
            *(short *) (self + 0x9c) = 0;
            break;
    }
}

void func_ov004_0224457c(UnkStruct_0224457c *self)
{
    Vec3 *q;
    short *h;
    int v;
    char *base;

    q = (Vec3 *) ((char *) self + 0x2c8);
    h = (short *) ((char *) self + 0x168);
    v = *h;
    v = (0x44 - v * 5) * v;
    base = (char *) self + 0xb0;
    if ((((unsigned long) *(unsigned long *) (base + 0xa0) << 4) >> 16) > 9) {
        func_02056fcc(base + 0x9c, 9, 0, self->unk_4C, 0);
    }
    if (self->unk_170 != 0 && v >= 0) {
        v = FX_MulFunc(v, 0x2000);
    } else if (v < -0x333) {
        v = -0x333;
    }
    q->y = q->y + v;
    func_ov004_022444f0((UnkStruct_022444f0 *) self, h);
    *h = (short) (*h + 4);
    func_ov004_02244d58((UnkStruct_02244d58 *) self);
    func_ov004_022449ec((unsigned char *) self, 0xaaa, 0x14, 0x3c);
}

void func_ov004_022444f0(UnkStruct_022444f0 *self, short *p)
{
    int lim, base;
    unsigned char f;
    Vec3 *q;

    lim = 0x300;
    base = self->unk_A8;
    f = self->unk_170;
    q = &self->pos;
    if (base != self->unk_54) {
        base = self->unk_54;
    }
    lim = lim + base;
    if (self->unk_16A < *p) {
        *p = 0;
        if (f != 0) {
            *p = 0;
            self->unk_16A = 0x10;
        } else {
            *p = 8;
            self->unk_16A = 0x14;
        }
    }
    if (f != 0 && q->y > lim) {
        self->unk_170 = 0;
    } else if (q->y < base) {
        if (q->y > base - 0x320) {
            q->y = base;
        }
        self->unk_170 = 1;
    }
}

void func_ov004_022442b4(char *self)
{
    u8 state = (u8) S(0x172);
    if (state != 25) {
        func_ov004_02244f20(self);
    }
    switch (state) {
        case 19:
            func_ov004_02244774(self, 0, 5);
            break;
        case 3:
        case 15:
            func_ov004_02244774(self, 0, 4);
            break;
        case 4:
            if (func_ov004_02244c20(self) && func_ov004_02243f0c((unsigned char *) self) < 0x5000) {
                S(0xac) = func_0200322c((Vec3 *) (V(0x2c8)), (Vec3 *) (V(0x40)));
                S(0x172) = 14;
                if (C(0x196) != 23) {
                    S(0x168) = (func_020644cc(5) + 2) * 10;
                }
            } else {
                func_ov004_02244094((UnkStruct_02244094 *) self);
            }
            func_ov004_02243fec((UnkStruct_02243fec *) self);
            break;
        case 5:
            func_ov004_02244224((UnkStruct_02244224 *) self);
            break;
        case 11:
        case 12:
        case 13:
        case 14:
            func_ov004_0224412c((unsigned char *) self);
            break;
        case 7: {
            int heading;
            S(0x172) = 15;
            S(0x9c) = 0;
            W(0x174) = 160;
            B(0x9a) = 0;
            B(0xae) = 0;
            heading = S(0xac);
            func_ov004_02244f48((UnkStruct_02244f48 *) (V(0x34)), (UnkStruct_02244f48 *) (V(0x2c8)), heading, (B(0xa4) + func_020644cc(3)) << 12);
            S(0xac) = func_0200322c((Vec3 *) (V(0x2c8)), (Vec3 *) (V(0x34)));
            break;
        }
        default:
            if (B(0x20)) {
                S(0x172) = 7;
            } else if (B(0xae)) {
                if ((*(u8 *) &data_ov004_02259a24) % 20 == 0) {
                    u8 choice = func_020644cc(100);
                    if ((((u32) W(0x154) << 4) >> 16) == 0 && choice > 92) {
                        func_020550e4(self + 0xb0, 2);
                    } else if (choice > 50) {
                        func_020550e4(self + 0xb0, 0);
                    }
                } else if ((((u32) W(0x154) << 4) >> 16) != 0) {
                    func_ov004_02244f20(self);
                }
                func_ov004_02244904((UnkStruct_02244904_2 *) self);
                if (B(0x22) && func_ov004_02244c20(self)) {
                    B(0xae) = 0;
                    S(0x172) = 11;
                    W(0x174) = 160;
                    if (C(0x196) == 23) {
                        S(0x168) = 0;
                    } else {
                        S(0x168) = (func_020644cc(5) + 2) * 10;
                    }
                }
            } else {
                S(0x172) = 11;
                if (C(0x196) == 23) {
                    S(0x168) = 0;
                } else {
                    S(0x168) = (func_020644cc(5) + 2) * 10;
                }
            }
            break;
    }
    B(0x20) = 0;
}

void func_ov004_02244224(UnkStruct_02244224 *self)
{
    Vec3 *p, *q;
    int m, k;

    p = &self->pos;
    q = &self->tgt;
    switch (self->unk_196) {
        case 0x15:
            k = 0x148;
            m = 0x40;
            break;
        case 0x16:
            k = 0x19a;
            m = 0x49;
            break;
        default:
            k = 0x19a;
            m = 0x4e;
            break;
    }
    if (func_020e91ac(p, q, m, 0x1000, k) == 0) {
        self->unk_172 = 0x19;
        self->unk_174 = (func_020644cc(5) + 5) * 0x14;
        self->unk_AE = 1;
    } else {
        self->ang = (short) func_0200322c(p, q);
    }
}

void func_ov004_0224412c(unsigned char *self)
{
    short *timer = (short *) (self + 0x168);
    Vec *position = (Vec *) (self + 0x2c8);
    if (*timer <= 0) {
        short mode = *(short *) (self + 0x172);
        if ((unsigned short) (short) (mode - 12) <= 1) {
            *(short *) (self + 0x172) = 15;
        } else if (mode == 14) {
            *(short *) (self + 0x172) = 19;
        } else {
            int angle;
            if (*(signed char *) (self + 0x196) == 23) {
                // Snapshot before the random call, as the ROM does.
                int previous = *(short *) (self + 0x192);
                int delta = func_ov004_0224105c(4);
                *(short *) (self + 0xac) = delta + previous;
            } else {
                // Snapshot before the random call, as the ROM does.
                int previous = *(short *) (self + 0x192);
                int delta = func_ov004_0224105c(12);
                *(short *) (self + 0xac) = delta + previous;
            }
            *(short *) (self + 0x172) = 3;
            angle = *(short *) (self + 0xac);
            func_ov004_02244f48((UnkStruct_02244f48 *) ((Vec *) (self + 0x34)), (UnkStruct_02244f48 *) position, angle, (self[0xa4] + func_020644cc(3)) << 12);
            *(short *) (self + 0xac) = func_0200322c((Vec3 *) ((Vec *) (self + 0x2c8)), (Vec3 *) ((Vec *) (self + 0x34)));
        }
    } else {
        if (*timer % 10 < 5) {
            if (position->y < *(int *) (self + 0xa8) + 0x800) {
                position->y += 0x80;
            }
        } else {
            if (position->y > *(int *) (self + 0xa8) - 0x1000) {
                position->y -= 0x80;
            }
        }
        --*timer;
    }
}

void func_ov004_02244094(UnkStruct_02244094 *self)
{
    Vec3 *p, *q;
    int n;

    q = &self->tgt;
    p = &self->pos;
    n = self->unk_16C;
    if (func_020e908c(p, q, n, 0x1000, self->unk_4C) == 0) {
        self->unk_172 = 0x19;
    } else {
        self->ang = (short) func_0200322c(p, q);
    }
    if (self->unk_170 != 0) {
        func_020e8bb0(&p->y, self->unk_A8, n, 0x1000, 0xcd);
    } else {
        if (func_020e8bb0(&p->y, self->unk_A8 - 0x1000, n, 0x1000, 0xcd) == 0) {
            self->unk_170 = 1;
        }
    }
}

void func_ov004_02243fec(UnkStruct_02243fec *self)
{
    int m;
    short d;
    int k;

    m = func_ov004_02245174(self);
    if (m != 0) {
        self->unk_AC = func_ov004_022447c0(self->ang, m);
        d = self->unk_AC;
        k = func_020644cc(3);
        func_ov004_02244f48((UnkStruct_02244f48 *) (&self->dst), (UnkStruct_02244f48 *) (&self->pos), d, (self->unk_A4 + k) << 12);
        self->unk_AC = (short) func_0200322c(&self->pos, &self->dst);
        if (self->unk_9A != 0) {
            self->unk_172 = 0xf;
        } else {
            self->unk_172 = 0xc;
            if (self->unk_196 == 0x17) {
                self->unk_168 = 0;
            } else {
                self->unk_168 = (short) ((func_020644cc(5) + 2) * 0xa);
            }
        }
    }
}

int func_ov004_02243f0c(unsigned char *self)
{
    Vec3 a;
    Vec3 b;
    int t;
    int u;
    int pz;
    Vec3 *q;
    volatile int v[11];
    int px;
    unsigned char *s;
    int u2;
    int db;
    int da;
    int t2;
    Vec3 *p;

    s = self;
    p = (Vec3 *) (s + 0x2c8);
    switch (*(signed char *) (s + 0x196)) {
        case 0x15:
            a.x = 0x16c00;
            v[0] = 0x1400;
            a.z = 0xd200;
            b.x = 0x1a600;
            v[1] = 0x1400;
            b.z = 0x13c00;
            break;
        case 0x16:
            a.x = 0x13200;
            v[0] = 0x1400;
            a.z = 0x10d00;
            b.x = 0x16600;
            v[1] = 0x1400;
            b.z = 0x14200;
            break;
        default:
            a.x = 0x17800;
            v[0] = 0x1400;
            a.z = 0x12200;
            b.x = 0x12b00;
            v[1] = 0x1a00;
            b.z = 0xda00;
            break;
    }
    px = p->x;
    v[3] = px;
    t = px - a.x;
    if (t < 0) {
        t = -t;
    }
    pz = p->z;
    v[2] = pz;
    u = pz - a.z;
    if (u < 0) {
        u = -u;
    }
    da = t + u;
    t2 = v[3] - b.x;
    if (t2 < 0) {
        t2 = -t2;
    }
    u2 = v[2] - b.z;
    if (u2 < 0) {
        u2 = -u2;
    }
    db = t2 + u2;
    if (da < db) {
        q = (Vec3 *) (s + 0x40);
        q->x = a.x;
        q->y = v[0];
        q->z = a.z;
        return da;
    }
    q = (Vec3 *) (s + 0x40);
    q->x = b.x;
    q->y = v[1];
    q->z = b.z;
    return db;
}

void func_ov004_02243e04(UnkStruct_02243e04 *self)
{
    short *p;
    short *q;
    int a, b, c;

    switch (self->unk_172) {
        case 3:
        case 0xf:
            func_ov004_02244774((char *) self, 1, 4);
            break;
        case 4:
            func_ov004_02243cb0((unsigned char *) self);
            break;
        default:
            p = &self->unk_168;
            if (self->unk_22 != 0) {
                func_ov004_02243c04((char *) self);
            }
            if ((int) func_ov004_02243c30((void *) self, p) != 0) {
                break;
            }
            q = &self->unk_98;
            if (func_ov004_02244764((char *) self) == 1) {
                *p = (short) (5 * *q);
            } else if (self->unk_22 == 0 && *p == 0) {
                *q = (short) (5 * *q);
            }
            *p = (short) (*p + 1);
            if (*p >= *q || self->unk_20 != 0) {
                a = self->unk_192;
                c = (int) func_ov004_0224105c(0xc);
                self->unk_AC = (short) (c + a);
                b = self->unk_AC;
                func_ov004_02244f48((UnkStruct_02244f48 *) (&self->unk_34), (UnkStruct_02244f48 *) (&self->pos), b, (self->unk_A4 + func_020644cc(3)) << 12);
                self->unk_AC = (short) func_0200322c(&self->pos, &self->unk_34);
                self->unk_172 = 3;
                *p = 0;
                self->unk_9C = 0;
            }
            break;
    }
    self->unk_20 = 0;
}

void func_ov004_02243cb0(unsigned char *self)
{
    Vec *origin, *position;
    int speed;
    // One frame preserves the ROM height/old-position offsets around the ground query.
    struct {
        int height;
        Vec old;
        int ground[16];
    } frame;
    origin = (Vec *) (self + 0x34);
    position = (Vec *) (self + 0x2c8);
    frame.old.x = position->x;
    frame.old.y = position->y;
    frame.old.z = position->z;
    speed = *(int *) (self + 0x16c);
    if (!func_ov004_02245188(self) || self[0x20]) {
        if (func_020e908c((Vec3 *) position, (Vec3 *) origin, speed, 0x1000, 0x333)) {
            if (func_ov004_02244e38((UnkStruct_02244e38 *) self, (Vec3 *) position)) {
                position->x = frame.old.x;
                position->y = frame.old.y;
                position->z = frame.old.z;
                origin->x = position->x;
                origin->y = position->y;
                origin->z = position->z;
            } else {
                *(short *) (self + 0x192) = (short) func_0200322c((Vec3 *) position, (Vec3 *) origin);
            }
        }
    } else {
        origin->x = position->x;
        origin->y = position->y;
        origin->z = position->z;
    }
    if (self[0x170]) {
        if (!func_020e8bb0(&position->y, 0x1400, speed, 0x1000, 0xcd)) {
            self[0x170] = 0;
        }
    } else {
        func_02034270(frame.ground, (Vec3 *) position, 0, 1);
        frame.height = func_020341c8(frame.ground, 0);
        func_0203423c(frame.ground);
        if (!func_020e8bb0(&position->y, frame.height, speed, 0x1000, 0x266)) {
            *(short *) (self + 0x98) = (func_020644cc(9) + 2) * 20;
            *(short *) (self + 0x172) = 25;
            func_020550e4(self + 0xb0, 0);
            origin->x = position->x;
            origin->y = position->y;
            origin->z = position->z;
            if (self[0x9a]) {
                *(short *) (self + 0x9c) = (unsigned char) (*(short *) (self + 0x9e) - 10);
                self[0x9a] = 0;
            }
        }
    }
}

void *func_ov004_02243c30(void *self, short *out)
{
    void *p = (void *) func_ov004_02245188(self);
    int t;
    short m;
    if (p != 0) {
        *(short *) ((char *) self + 0xac) = (short) func_ov004_022447c0(*(short *) ((char *) self + 0x192), (int) p);
        m = *(short *) ((char *) self + 0xac);
        t = func_020644cc(3);
        func_ov004_02244f48((UnkStruct_02244f48 *) ((char *) self + 0x34), (UnkStruct_02244f48 *) ((char *) self + 0x2c8), m, (*((unsigned char *) self + 0xa4) + t) << 12);
        *(short *) ((char *) self + 0xac) = (short) func_0200322c((Vec3 *) ((char *) self + 0x2c8), (Vec3 *) ((char *) self + 0x34));
        *(short *) ((char *) self + 0x172) = 0xf;
        *(int *) ((char *) self + 0x4c) += 1;
        *out = 0;
    }
    return p;
}

void func_ov004_02243c04(char *self)
{
    switch (*(signed char *) (self + 0x196)) {
        case 0x1b:
        case 0x1c:
        case 0x1d:
            if (*(short *) (self + 0x9c) < 5) {
                func_ov004_02244be0((struct UnkStruct_02244be0 *) self, 0);
            }
            break;
    }
}

void func_ov004_02243bb0(UnkStruct_02243bb0 *self)
{
    short *p;
    short v;
    switch (self->unk_172) {
        case 3:
        case 0xf:
            func_ov004_02243af4(self, &self->unk_168);
            break;
        case 4:
            func_ov004_022439ec(self, &self->unk_168);
            break;
        default:
            p = &self->unk_98;
            v = self->unk_98;
            if (v <= 0) {
                self->unk_172 = 3;
            } else {
                *p = v - 1;
            }
            self->unk_9A = 0;
            break;
    }
}
