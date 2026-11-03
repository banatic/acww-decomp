/* museum_insect_motions_5: 18 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0224379c @ 0x0224379c, 0x44 bytes, Thumb
 * func_ov004_02243740 @ 0x02243740, 0x5c bytes, Thumb
 * func_ov004_02243694 @ 0x02243694, 0xac bytes, Thumb
 * func_ov004_022435e0 @ 0x022435e0, 0xb4 bytes, Thumb
 * func_ov004_02243544 @ 0x02243544, 0x9c bytes, Thumb
 * func_ov004_02243484 @ 0x02243484, 0xc0 bytes, Thumb
 * func_ov004_022433c8 @ 0x022433c8, 0xbc bytes, Thumb
 * func_ov004_02243300 @ 0x02243300, 0xc8 bytes, Thumb
 * func_ov004_02243248 @ 0x02243248, 0xb8 bytes, Thumb
 * func_ov004_02243194 @ 0x02243194, 0xb4 bytes, Thumb
 * func_ov004_022430f8 @ 0x022430f8, 0x9c bytes, Thumb
 * func_ov004_02243048 @ 0x02243048, 0xb0 bytes, Thumb
 * func_ov004_02242fe8 @ 0x02242fe8, 0x5e bytes, Thumb
 * func_ov004_02242f1c @ 0x02242f1c, 0xcc bytes, Thumb
 * func_ov004_02242e84 @ 0x02242e84, 0x98 bytes, Thumb
 * func_ov004_02242df8 @ 0x02242df8, 0x8c bytes, Thumb
 * func_ov004_02242d84 @ 0x02242d84, 0x74 bytes, Thumb
 * func_ov004_02242c64 @ 0x02242c64, 0x120 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02243740 {
    char unk_00[0x168];
    short unk_168;
} UnkStruct_02243740;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02243694 {
    char unk_00[0x40];
    Vec3 unk_40;
    char unk_4C[0x9a - 0x4c];
    unsigned char unk_9A;
    char unk_9B[0xac - 0x9b];
    short unk_AC;
    char unk_AE[0x172 - 0xae];
    short unk_172;
    char unk_174[0x192 - 0x174];
    short ang;
    char unk_194[0x196 - 0x194];
    signed char unk_196;
} UnkStruct_02243694;

typedef struct UnkStruct_022435e0 {
    char unk_00[0x196];
    signed char unk_196;
} UnkStruct_022435e0;

typedef struct UnkStruct_02243544 {
    char unk_00[0x34];
    Vec3 dst;
    char unk_40[0x98 - 0x40];
    short unk_98;
    char unk_9A[0x172 - 0x9a];
    short unk_172;
    char unk_174[0x192 - 0x174];
    short ang;
    char unk_194[0x2c8 - 0x194];
    Vec3 pos;
} UnkStruct_02243544;

typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    Vec position;
    int value, distance;
    unsigned char present;
} Sample;

typedef struct UnkStruct_02243248 {
    char unk_00[0x16c];
    int unk_16C;
    char unk_170[0x172 - 0x170];
    short unk_172;
    char unk_174[0x190 - 0x174];
    short unk_190;
    short ang;
    char unk_194[0x2c8 - 0x194];
    Vec3 pos;
} UnkStruct_02243248;

typedef struct UnkStruct_02243194 {
    char unk_00[0xac];
    short unk_AC;
    char unk_AE[0x172 - 0xae];
    short unk_172;
    int unk_174;
    char unk_178[0x192 - 0x178];
    short ang;
} UnkStruct_02243194;

typedef struct UnkStruct_022430f8 {
    char unk_00[0x50];
    unsigned char unk_50;
    char unk_51[0x192 - 0x51];
    short ang;
    char unk_194[0x196 - 0x194];
    signed char unk_196;
} UnkStruct_022430f8;

typedef struct UnkStruct_02243048 {
    char unk_00[0xac];
    short unk_AC;
    char unk_AE[0x154 - 0xae];
    unsigned long unk_154;
    char unk_158[0x168 - 0x158];
    short unk_168;
    char unk_16A[0x172 - 0x16a];
    short unk_172;
    int unk_174;
    char unk_178[0x192 - 0x178];
    short ang;
} UnkStruct_02243048;

typedef struct UnkStruct_02242e84 {
    char unk_00[0x34];
    Vec3 dir;
    char unk_40[0x4c - 0x40];
    int unk_4C;
    char unk_50[0x170 - 0x50];
    unsigned char unk_170;
} UnkStruct_02242e84;

typedef struct UnkStruct_02242d84 {
    char unk_00[0x22];
    unsigned char unk_22;
    char unk_23[0x9a - 0x23];
    unsigned char unk_9A;
    char unk_9B[0x168 - 0x9b];
    short unk_168;
    char unk_16A[0x172 - 0x16a];
    short unk_172;
} UnkStruct_02242d84;

extern void func_ov004_02241894(void *);
extern int func_ov004_02244e38(void *, void *);
extern void func_ov004_022449ec(UnkStruct_02243740 *self, int a, int b, int c);
extern void func_ov004_0224497c(UnkStruct_02243740 *self, int a, int b, int c);
extern int func_020644cc(int a);
extern int FX_Div(int a, int b);
extern void func_ov004_02241084(UnkStruct_02243694 *self);
extern void func_ov004_02244c40(UnkStruct_02243694 *self);
extern void func_ov004_02244f20(UnkStruct_022435e0 *self);
extern int func_ov004_02244904(UnkStruct_022435e0 *self);
extern void func_ov004_02244d58(UnkStruct_022435e0 *self);
extern void func_ov004_02244f48(Vec3 *out, Vec3 *base, int ang, int r);
extern void *func_020961a8(int a);
extern int func_020ea990(Vec3 *a, Vec3 *b);
extern int FX_MulFunc(int a, int b);
extern int func_020e908c(Vec *, Vec *, int, int, int);
extern int func_ov004_02244e94(Vec *, Vec *);
extern int func_ov004_02244be0(void *, int);
extern int func_020e8870(short *, int, int);
extern int func_ov004_02244c20(void *);
extern int func_ov004_02244658(void *, Sample *);
extern int func_02090c2c(int, Vec *, int, void *);
extern int func_0200322c(Vec *, Vec *);
extern void *func_0209d088(void *);
extern void NNS_G3dMdlSetMdlAlpha(void *, int, int);
extern unsigned char data_020e25d4[];
extern void func_ov004_02244fb8(Vec3 *out, int ang);
extern int func_02034270(void *w, Vec3 *v, int a, int b);
extern int func_020341c8(void *w, int a);
extern void func_0203423c(void *w);
extern int func_ov004_02241ba8(UnkStruct_02243194 *self);
extern int func_ov004_0224105c(int a);
extern unsigned char data_ov004_02259a24;
extern int func_ov004_02245174(UnkStruct_022430f8 *self);
extern int func_ov004_02245188(UnkStruct_022430f8 *self);
extern void func_020550e4(void *p, int a);
extern int func_ov004_02244764(void *self);
extern void func_02056fcc(void *p, int a, int b, int c, int d);

void func_ov004_02243740(UnkStruct_02243740 *self);
void func_ov004_022435e0(UnkStruct_022435e0 *self);
void func_ov004_02243484(unsigned char *self);
void func_ov004_02243300(unsigned char *self);
void func_ov004_02243248(UnkStruct_02243248 *self, short *p);
void func_ov004_02243194(UnkStruct_02243194 *self, short *p);
int func_ov004_02242fe8(void *self);
void func_ov004_02242f1c(unsigned char *self);
void func_ov004_02242e84(UnkStruct_02242e84 *self);
void func_ov004_02242df8(Vec3 *out, unsigned int k);
void func_ov004_02242c64(unsigned char *self);

void func_ov004_0224379c(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x22) == 0x0) {
        func_ov004_02241894(self);
        return;
    } else {
        if (*(short *) (self + 0x172) == 0x0) {
            func_ov004_02243740((UnkStruct_02243740 *) self);
            func_ov004_02244e38(self, self + 0x2c8);
        } else {
            *(u8 *) (self + 0x9a) = 0x0;
            *(u16 *) (self + 0x172) = 0x0;
        }
        return;
    }
}

void func_ov004_02243740(UnkStruct_02243740 *self)
{
    func_ov004_022449ec(self, 0x38e, 0x28, 0x50);
    self->unk_168 = (short) (self->unk_168 + (short) FX_Div(0x2000, (func_020644cc(4) + 5) << 12));
    func_ov004_0224497c(self, self->unk_168, 0x1000, (func_020644cc(4) + 0xa) << 12);
}

void func_ov004_02243694(UnkStruct_02243694 *self)
{
    Vec3 *p;

    switch (self->unk_172) {
        case 0:
            func_ov004_02244be0((void *) self, 0);
            func_ov004_022435e0((UnkStruct_022435e0 *) self);
            break;
        case 6:
            if (self->unk_196 == 0xa) {
                func_ov004_02241084(self);
            }
            func_ov004_02244c40(self);
            break;
        case 7:
            self->unk_172 = 0;
            if (self->unk_9A != 0) {
                self->ang = (short) (self->ang + self->unk_AC);
            }
            break;
        default:
            self->unk_9A = 0;
            self->unk_172 = 0;
            if (self->unk_196 == 0x33) {
                p = &self->unk_40;
                if (func_020644cc(0x64) > 0x32) {
                    p->x = 0xef00;
                    p->z = 0xc900;
                } else {
                    p->x = 0xf700;
                    p->z = 0x15200;
                }
                p->y = 0x1300;
            }
            break;
    }
}

void func_ov004_022435e0(UnkStruct_022435e0 *self)
{
    short *h;

    h = (short *) ((char *) self + 0x98);
    func_ov004_02244f20(self);
    if (func_ov004_02244904(self) == 2) {
        *((unsigned char *) self + 0x9a) = 0;
    }
    if (*((unsigned char *) self + 0x9a) != 0) {
        func_ov004_022449ec((UnkStruct_02243740 *) self, 0xaaa, 0xa, 0x46);
    } else {
        func_ov004_02244d58(self);
        func_ov004_022449ec((UnkStruct_02243740 *) self, 0xaaa, 0x14, 0x50);
    }
    if (self->unk_196 == 0x33) {
        func_ov004_0224497c((UnkStruct_02243740 *) self, *h, 0x19a, (func_020644cc(8) + 0x12) << 12);
        *h = (short) (*h + 0x1554);
    } else {
        func_ov004_0224497c((UnkStruct_02243740 *) self, *h, 0x1200, (func_020644cc(8) + 0xa) << 12);
        *h = (short) (*h + 0xaaa);
    }
}

void func_ov004_02243544(UnkStruct_02243544 *self)
{
    Vec3 *p, *q;
    unsigned char k;
    short a;
    char *o;

    if (self->unk_172 == 4) {
        func_ov004_02243484((unsigned char *) self);
    } else if (func_ov004_02244c20((void *) self) != 0) {
        o = (char *) func_020961a8(4);
        if (o != 0) {
            k = (unsigned char) (func_020644cc(0x21) + 0x10);
            p = &self->pos;
            q = (Vec3 *) (o + 0x5c);
            if (func_020ea990(q, p) > 0x6000) {
                k = (unsigned char) (k + 0x10);
            }
            self->ang = (short) func_0200322c((Vec *) p, (Vec *) q);
            a = self->ang;
            func_ov004_02244f48(&self->dst, p, a, FX_MulFunc(k << 12, 0x100));
            self->unk_98 = 1;
            self->unk_172 = 4;
        }
    }
}

void func_ov004_02243484(unsigned char *self)
{
    short *timer = (short *) (self + 0x98);
    Vec *position = (Vec *) (self + 0x2c8);
    Vec previous;
    previous.x = position->x;
    previous.y = position->y;
    previous.z = position->z;
    func_020e908c(position, (Vec *) (self + 0x34), 0xaa, 0x1000, 0x333);
    if (*(short *) (self + 0x98) > 0) {
        int t = *(short *) (self + 0x98) << 12;
        position->y = FX_MulFunc(0x99a - FX_MulFunc(123, t), t);
        if (position->y < 0) {
            unsigned char *other = (unsigned char *) func_020961a8(4);
            int spread = 20;
            if (other && func_020ea990((Vec3 *) ((Vec *) (other + 0x5c)), (Vec3 *) position) > 0x6000) {
                spread = 0;
            }
            *(int *) (self + 0x174) = (short) (func_020644cc(spread * 2 + 20) + 20) >> 1;
            *(short *) (self + 0x172) = 25;
            *timer = 0;
        } else {
            ++*timer;
        }
    }
    func_ov004_02244e94(position, &previous);
}

void func_ov004_022433c8(unsigned char *self)
{
    switch (*(short *) (self + 0x172)) {
        case 4:
            func_ov004_02244be0(self, 2);
            func_ov004_02243194((UnkStruct_02243194 *) self, (short *) (self + 0x168));
            break;
        case 5:
            func_ov004_02243248((UnkStruct_02243248 *) self, (short *) (self + 0x168));
            break;
        case 3: {
            short angle = *(short *) (self + 0x192);
            if (func_020e8870(&angle, *(short *) (self + 0xac), 0x38e)) {
                *(short *) (self + 0x172) = 4;
            }
            func_ov004_02244be0(self, 2);
            *(short *) (self + 0x192) = angle;
            break;
        }
        case 16:
            if (func_ov004_02244c20(self)) {
                Vec *source, *destination;
                *(short *) (self + 0x172) = 25;
                source = (Vec *) (self + 0x34);
                destination = (Vec *) (self + 0x2c8);
                destination->x = source->x;
                destination->y = source->y;
                destination->z = source->z;
            }
            break;
        default:
            func_ov004_02243300((unsigned char *) self);
            break;
    }
}

void func_ov004_02243300(unsigned char *self)
{
    // Declaration order recovers r4/r6/r7 without altering evaluation order.
    unsigned char before;
    Sample sample;
    int countdown;
    Vec *position;
    position = (Vec *) (self + 0x2c8);
    before = (unsigned char) *(short *) (self + 0x9c);
    func_ov004_02244658(self, &sample);
    if (sample.present) {

        if (sample.distance < 0x5000) {
            self[0x50] = 60;
        }
        countdown = self[0x50];
        if (countdown > 0) {
            func_ov004_02244be0(self, 0);
            self[0x50] = countdown - 1;
        }
        if (before > *(short *) (self + 0x9e)) {
            Vec *destination;
            Vec *source;
            *(short *) (self + 0x172) = 5;
            func_02090c2c(128, position, 0, data_020e25d4);
            *(short *) (self + 0x98) = (func_020644cc(11) + 5) * 20;
            *(short *) (self + 0x192) = func_0200322c(&sample.position, position);
            NNS_G3dMdlSetMdlAlpha(func_0209d088(self + 0x288), 0, 31);
            source = (Vec *) (self + 0x2c8);
            destination = (Vec *) (self + 0x34);
            destination->x = source->x;
            destination->y = source->y;
            destination->z = source->z;
        }
    }
}

void func_ov004_02243248(UnkStruct_02243248 *self, short *p)
{
    Vec3 d;
    char w[0x40];
    Vec3 *q;
    int spd, ok, t;

    q = &self->pos;
    spd = (self->unk_16C + 2) << 12;
    func_ov004_02244fb8(&d, self->ang);
    q->x = q->x + FX_MulFunc(spd, d.x);
    q->z = q->z + FX_MulFunc(spd, d.z);
    t = *p;
    q->y = q->y + (0x19 - t) * (t << 2);
    func_02034270(w, q, 0, 1);
    if (q->y <= func_020341c8(w, 0)) {
        ok = 1;
    } else {
        ok = 0;
    }
    func_0203423c(w);
    if (ok != 0 && *p > 0) {
        self->unk_172 = 4;
        *(short *) ((char *) self + 0x9c) = 0;
        *p = 0;
        self->unk_190 = 0;
    } else {
        *p = (short) (*p + 2);
    }
}

void func_ov004_02243194(UnkStruct_02243194 *self, short *p)
{
    short *h;
    short v;

    h = (short *) ((char *) self + 0x98);
    if (*h > 0) {
        *h = (short) (*h - 1);
        func_ov004_02241ba8(self);
        func_ov004_02244e38((void *) self, (void *) ((Vec3 *) ((char *) self + 0x2c8)));
        if (*h > 5) {
            if (data_ov004_02259a24 % 8 == 0 && func_020644cc(0x64) > 0x32) {
                v = self->ang;
                self->unk_AC = (short) (v + func_ov004_0224105c(0xc));
                self->unk_172 = 3;
            }
        } else if (*h == 5) {
            func_02090c2c(0x80, (Vec *) ((Vec3 *) ((char *) self + 0x2c8)), 0, (void *) data_020e25d4);
        }
    } else {
        self->unk_172 = 0x10;
        NNS_G3dMdlSetMdlAlpha((void *) ((int) func_0209d088((char *) self + 0x288)), 0, 0);
        self->unk_174 = 0x3c;
        *p = 0;
    }
}

int func_ov004_022430f8(UnkStruct_022430f8 *self)
{
    unsigned char s;
    int m;
    short a;

    s = self->unk_50;
    if (self->unk_196 == 0x34) {
        m = func_ov004_02245174(self);
    } else {
        m = func_ov004_02245188(self);
    }
    if (m != 0) {
        a = self->ang;
        if (m == 3) {
            if (s == 1 || s == 0xa) {
                a -= 0xaaa;
            } else {
                a += 0xaaa;
            }
        } else if (m == 1 || s == 1) {
            a -= 0x38e;
            s = 1;
        } else if (m == 2 || s == 2) {
            a += 0x38e;
            s = 2;
        }
        self->ang = a;
    } else if (s < 0xa) {
        s = (unsigned char) (0xa * s);
    }
    self->unk_50 = s;
    return m;
}

void func_ov004_02243048(UnkStruct_02243048 *self)
{
    short t;

    switch (self->unk_172) {
        case 3:
            if (func_ov004_02242fe8((void *) self) != 0) {
                t = self->ang;
                if (func_020e8870(&t, self->unk_AC, 0x38e) != 0) {
                    self->unk_172 = 4;
                }
                self->ang = t;
            }
            break;
        case 4:
            func_ov004_02242f1c((unsigned char *) self);
            break;
        default:
            if (func_ov004_02244c20((void *) self) != 0 && func_ov004_02242fe8((void *) self) != 0) {
                if (((self->unk_154 << 4) >> 16) != 1) {
                    func_020550e4((char *) self + 0xb0, 1);
                }
                self->unk_168 = 0;
                self->unk_172 = 4;
                self->unk_174 = (func_020644cc(9) + 4) * 0x14;
            }
            break;
    }
}

int func_ov004_02242fe8(void *self)
{
    unsigned char *s;
    int k;

    s = (unsigned char *) ((char *) self + 0x50);
    k = *s;
    func_ov004_02244764(self);
    if (*(short *) ((char *) self + 0x9c) < *(short *) ((char *) self + 0x9e) && k < 2) {
        func_020550e4((char *) self + 0xb0, 1);
    } else {
        if (k == 0) {
            *((char *) self + 0x50) = 0x3c;
        } else if (k > 1) {
            *((char *) self + 0x50) = (char) (k - 1);
        }
        func_020550e4((char *) self + 0xb0, 0);
        return 0;
    }
    return 1;
}

void func_ov004_02242f1c(unsigned char *self)
{
    if (func_ov004_02242fe8(self)) {
        Vec *position = (Vec *) (self + 0x2c8);
        Vec *target = (Vec *) (self + 0x34);
        if (!func_ov004_02244c20(self)) {
            if (!func_020e908c(position, target, 64, 0x1000, 41)) {
                func_ov004_02242e84((UnkStruct_02242e84 *) self);
                *(short *) (self + 0xac) = func_0200322c(position, target);
                *(short *) (self + 0x172) = 3;
            } else {
                short timer = (short) *(int *) (self + 0x174);
                *(short *) (self + 0x192) = func_0200322c(position, target);
                if (timer % 8 == 0) {
                    *(short *) (self + 0x192) += 0xaaa;
                } else if (timer % 4 == 0) {
                    *(short *) (self + 0x192) -= 0xaaa;
                }
            }
        } else {
            *(int *) (self + 0x174) = (func_020644cc(3) + 2) * 20;
            *(short *) (self + 0x172) = 25;
        }
    }
}

void func_ov004_02242e84(UnkStruct_02242e84 *self)
{
    unsigned char s, v;

    s = (unsigned char) self->unk_4C;
    if (s == 0 && self->unk_170 == 0) {
        v = 1;
        self->unk_170 = 1;
    } else if (s == 4 && self->unk_170 != 0) {
        v = 3;
        self->unk_170 = 0;
    } else if (func_020644cc(0x64) > 0x46 && s != 0 && s != 4) {
        if (self->unk_170 != 0) {
            v = s - 1;
            self->unk_170 = 0;
        } else {
            v = s + 1;
            self->unk_170 = 1;
        }
    } else {
        if (self->unk_170 != 0) {
            v = s + 1;
        } else {
            v = s - 1;
        }
    }
    self->unk_4C = v;
    func_ov004_02242df8(&self->dir, v);
}

void func_ov004_02242df8(Vec3 *out, unsigned int k)
{
    switch (k) {
        case 0:
            out->x = 0x11e00;
            out->y = 0x800;
            out->z = 0xda00;
            break;
        case 1:
            out->x = 0x12300;
            out->y = 0x800;
            out->z = 0xf400;
            break;
        case 2:
            out->x = 0x13800;
            out->y = 0x800;
            out->z = 0xf600;
            break;
        case 3:
            out->x = 0x14100;
            out->y = 0x800;
            out->z = 0xe800;
            break;
        default:
            out->x = 0x14000;
            out->y = 0x800;
            out->z = 0xd900;
            break;
    }
}

void func_ov004_02242d84(UnkStruct_02242d84 *self)
{
    if (self->unk_172 == 0) {
        func_ov004_02242c64((unsigned char *) self);
    } else if (self->unk_22 != 0) {
        self->unk_9A = 0;
        self->unk_172 = 0;
        self->unk_168 = 0;
    } else if (data_ov004_02259a24 % 0x28 == 0) {
        if (func_020644cc(0x64) > 0x50) {
            func_02056fcc((char *) self + 0x14c, 8, 1, 0x1000, 0);
        }
    }
}

void func_ov004_02242c64(unsigned char *self)
{
    unsigned char horizontal = self[0xae];
    Vec *position = (Vec *) (self + 0x2c8);
    int *origin = (int *) self;
    unsigned char vertical;
    // The ROM retains all three snapshot stores, including unused Z.
    volatile Vec old;
    int clock, distance;
    origin = (int *) ((unsigned char *) origin + 0x40);
    vertical = self[0x170];
    old.x = position->x;
    old.y = position->y;
    old.z = position->z;
    if (func_020644cc(100) > 30) {
        clock = data_ov004_02259a24;
        if (clock % 10 == 0) {
            self[0x170] = !vertical;
        } else if (clock % 5 == 0) {
            self[0xae] = !horizontal;
        }
    }
    if (horizontal) {
        position->x += 48 * *(int *) (self + 0x16c);
    } else {
        position->x -= 48 * *(int *) (self + 0x16c);
    }
    if (vertical) {
        position->y += 48 * *(int *) (self + 0x16c);
    } else {
        position->y -= 48 * *(int *) (self + 0x16c);
    }
    distance = position->x - origin[0];
    if (distance < 0) {
        distance = -distance;
    }
    if (distance > 0x1000) {
        self[0xae] = !horizontal;
        position->x = old.x;
    }
    distance = position->y - origin[1];
    if (distance < 0) {
        distance = -distance;
    }
    if (distance > 0x800) {
        self[0x170] = !vertical;
        position->y = old.y;
    }
}
