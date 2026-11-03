/* field_actor_states_8: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02009918 @ 0x02009918, 0x10c bytes, Thumb
 * func_02009914 @ 0x02009914, 0x2 bytes, Thumb
 * func_020097c0 @ 0x020097c0, 0x154 bytes, Thumb
 * func_02009728 @ 0x02009728, 0x98 bytes, Thumb
 * func_020096ac @ 0x020096ac, 0x7c bytes, Thumb
 * func_02009624 @ 0x02009624, 0x88 bytes, Thumb
 * func_020095f4 @ 0x020095f4, 0x2e bytes, Thumb
 * func_020095f0 @ 0x020095f0, 0x4 bytes, Thumb
 * func_020095b0 @ 0x020095b0, 0x40 bytes, Thumb
 * func_020095ac @ 0x020095ac, 0x4 bytes, Thumb
 * func_0200956c @ 0x0200956c, 0x40 bytes, Thumb
 * func_02009568 @ 0x02009568, 0x2 bytes, Thumb
 * func_02009534 @ 0x02009534, 0x34 bytes, Thumb
 * func_02009504 @ 0x02009504, 0x30 bytes, Thumb
 * func_020094e4 @ 0x020094e4, 0x20 bytes, Thumb
 * func_020094a0 @ 0x020094a0, 0x44 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02009918 {
    int a;
    int b;
    int c;
};

struct UnkStruct_02009918_2 {
    int unk_00;
    int w1;
};

struct Packed {
    u16 low : 7;
    u16 mid : 4;
    u16 high : 5;
};

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int unk_00, unk_04, unk_08, unk_0C, unk_10, unk_14;
} UnkStruct_020097c0;

typedef struct {
    char pad_00[0x5c];
    int unk_5C, unk_60, unk_64;
    char pad_68[0x8e - 0x68];
    short unk_8E;
    char pad_90[0x7d4 - 0x90];
    UnkStruct_020097c0 w;
} UnkStruct_020097c0_2;

typedef struct UnkStruct_02009728 UnkStruct_02009728;

struct UnkStruct_02009728 {
    char pad_00[0x98];
    int unk_98;
    char pad_9C[0x234 - 0x9c];
    unsigned int unk_234;
    char pad_238[0x2d4 - 0x238];
    int unk_2D4;
    char pad_2D8[0x2e0 - 0x2d8];
    int unk_2E0;
    char pad_2E4[0x704 - 0x2e4];
    int unk_704;
};

typedef struct {
    unsigned char pad_00[0x60];
    int unk_60;
    int unk_64;
} UnkStruct_020096ac;

typedef struct {
    char pad_00[0x704];
    int unk_704;
    char pad_708[0x7f0 - 0x704 - 4];
    int unk_7F0;
    char pad_7F4[0x7fc - 0x7f0 - 4];
    int unk_7FC;
} UnkStruct_02009624;

typedef struct {
    char pad_00[0xc];
    int data[4];
} UnkStruct_020095b0;

typedef struct {
    short unk_00;
    short unk_02;
} UnkStruct_02009534;

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x744];
    UnkStruct_02009534 sub;
} UnkStruct_02009534_2;

typedef struct {
    char pad_00[0x8e];
    signed short unk_8E;
    char pad_90[0x744];
    signed short unk_7D4;
} UnkStruct_02009504;

typedef struct {
    unsigned char unk_00[0xc];
    unsigned char data[3];
    unsigned char rest[0x11];
} Buffer;

extern void *data_020ccf94;
extern void func_020109fc(void *p, int a, int b, int c);
extern void func_02009a24(void *dst, struct UnkStruct_02009918 s, int p4, int p5);
extern unsigned int *func_0200f27c(void *p, int a);
extern int func_0200ee0c(void *p);
extern int func_02073908(void *a, int b);
extern int func_020b65c4(void);
extern void func_0209e474(void *p);
extern u8 *func_0209626c(void);
extern void func_0209e140(void *p, int a);
extern void *func_02011368(void *p);
extern void func_02099794(void *p, struct Packed s);
extern short FX_SinCosTable_[];
extern int func_0200f290(UnkStruct_020097c0_2 *self, int k);
extern int FX_MulFunc(int a, int b);
extern int func_020ea9c8(Vec3 *v);
extern void func_02011490(int *p, int v);
extern int func_020ea990(Vec3 *a, Vec3 *b);
extern int func_02011398(int, int);
extern int func_020113b0(int a, int b);
extern int func_020e8ed8(int a, int b);
extern int func_020113e0(short *h, int m);
extern void func_020110a0(UnkStruct_020097c0_2 *self, short *h);
extern void func_0201107c(UnkStruct_020097c0_2 *self, int *p);
extern void func_02010f5c(int);
extern void func_020109c8(UnkStruct_02009728 *p, int a, int b, int c);
extern void func_02054860(unsigned int *p);
extern void func_0200f95c(UnkStruct_02009728 *p);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern int func_0201100c(UnkStruct_020096ac *self);
extern void *func_0209d5e8(void);
extern int func_0209d848(void *p);
extern int func_020310c8(int a);
extern void *func_0209d844(void *p);
extern int func_02008258(UnkStruct_02009624 *self, int a);
extern int func_0200d4e8(UnkStruct_02009624 *self, int a, int b, int c);
extern int func_0203e3f8(void);
extern void func_0200f268(UnkStruct_02009624 *self, int a);
extern int func_0200c3b0(UnkStruct_02009624 *self, int a, int b, int c);
extern void func_02010d64(int);
extern unsigned int func_0200e92c(UnkStruct_020095b0 *lp);
extern void func_0200e90c(UnkStruct_020095b0 *lp, int a, int b, int c);
extern int func_0200e894(int p1, UnkStruct_020095b0 *lp);
extern int func_0200e91c(UnkStruct_020095b0 *lp);

void func_02009918(void *param0, void *param1, int param2)
{
    int p2_copy = param2;
    struct Packed packed;
    struct UnkStruct_02009918_2 local;
    int d;
    struct UnkStruct_02009918 *p = (struct UnkStruct_02009918 *) ((char *) param1 + 0xc);

    func_020109fc(param0, 1, 3, 0);
    d = *(int *) ((char *) p + 0xc);
    func_02009a24((char *) param0 + 0x7d4, *p, d, p2_copy);
    func_0200f27c(param0, 5);
    *(int *) ((char *) param0 + 0x808) = 0;

    if (func_0200ee0c(param0) != 0 && func_02073908(data_020ccf94, *(int *) ((char *) param0 + 0x800)) != 0 &&
        func_020b65c4() == 0xc && d == 0x666) {
        local.unk_00 = 0;
        local.w1 = 0;
        func_0209e474(&local);
        *func_0209626c() &= 0xf9;
        if (!(*func_0209626c() & 1)) {
            func_0209e140(&local, 1);
        }
        packed.low = ((u8 *) &local)[5];
        packed.mid = ((u8 *) &local)[4];
        packed.high = ((u8 *) &local)[3];
        func_02099794(func_02011368(param0), packed);
    }
}

void func_02009914(void *object, int event) {}

int func_020097c0(UnkStruct_020097c0_2 *self)
{
    UnkStruct_020097c0 *w;
    int *m;
    int saved;
    int ret;
    int lim;
    short hv;
    int r;
    Vec3 d;
    Vec3 p;
    Vec3 *sv;
    int idx;
    int t;
    int e;

    w = &self->w;
    m = &w->unk_0C;
    saved = w->unk_10;
    ret = 0;
    sv = (Vec3 *) &self->unk_5C;
    p.x = self->unk_5C;
    p.y = sv->y;
    p.z = sv->z;
    if (func_0200f290(self, 0x18) != 0) {
        w->unk_00 = self->unk_5C;
    }
    if (func_020b65c4() == 0x20 && w->unk_14 == 0x40 && p.z >= w->unk_08) {
        w->unk_08 = p.z;
    }
    d.x = w->unk_00 - self->unk_5C;
    d.z = w->unk_08 - self->unk_64;
    lim = FX_MulFunc(0x4000, *m);
    if (lim < 0x1000) {
        lim = 0x1000;
    }
    if (func_020ea9c8(&d) < lim) {
        if (*m <= 0x333) {
            func_02011490(&self->unk_5C, w->unk_00);
            func_02011490(&self->unk_64, w->unk_08);
            if (w->unk_00 == self->unk_5C && w->unk_08 == self->unk_64) {
                *m = 0;
                ret = 1;
            } else {
                *m = func_020ea990((Vec3 *) &self->unk_5C, &p);
                sv = (Vec3 *) &self->unk_5C;
                self->unk_5C = p.x;
                sv->y = p.y;
                sv->z = p.z;
            }
        } else {
            *m = func_02011398(*m, 819);
        }
    } else {
        *m = func_020113b0(*m, saved);
    }
    r = func_020e8ed8(d.x, d.z);
    hv = self->unk_8E;
    if (*m != 0) {
        func_020113e0(&hv, r);
        func_020110a0(self, &hv);
    }
    idx = ((unsigned short) (short) (hv - r)) >> 4;
    t = FX_MulFunc(*m, FX_SinCosTable_[idx * 2 + 1]);
    if (t < 0) {
        t = -t;
    }
    e = t;
    func_0201107c(self, &e);
    return ret;
}

void func_02009728(UnkStruct_02009728 *self)
{
    int val;
    int result;

    if (self->unk_704 == 0) {
        func_02010f5c((int) self);
        return;
    }

    val = self->unk_98;
    if (func_0200f290((UnkStruct_020097c0_2 *) self, 0x18)) {
        val <<= 1;
    }

    result = FX_MulFunc(val, 0x3ae1);
    if (result <= self->unk_2D4) {
        self->unk_2E0 = result;
    }

    if (val > 0x53f) {
        if (self->unk_704 != 2) {
            func_020109c8(self, 2, 3, 0);
        }
    } else {
        if (self->unk_704 != 1) {
            func_020109c8(self, 1, 3, 0);
        }
    }

    func_02054860(&self->unk_234);
    func_0200f95c(self);
}

void func_020096ac(UnkStruct_020096ac *self)
{
    void *p;
    int *f60;
    int target;
    int diff;

    if (func_0200f290((UnkStruct_020097c0_2 *) self, 0x18)) {
        func_0201100c(self);
        p = func_0209d5e8();
        if (func_0209d848(p) != 1) {
            return;
        }
        f60 = &self->unk_60;
        target = func_020310c8(0);
        if (*f60 >= target) {
            void *q = func_0209d844(p);
            diff = *(int *) ((char *) q + 8) - self->unk_64;
            if (diff < 0) {
                diff = -diff;
            }
            if (diff < 0x1000) {
                int scaled = FX_Div(0x1000 - diff, 0x1000) * 6;
                *f60 = *f60 + (scaled >> 5);
            } else {
                *f60 = target;
            }
        } else {
            *f60 = target;
        }
    } else {
        func_0201100c(self);
    }
}

void func_02009624(UnkStruct_02009624 *self, int flag)
{
    if (flag) {
        if (func_0200f290((UnkStruct_020097c0_2 *) self, 0x18)) {
            if (self->unk_704) {
                func_020109fc((void *) self, 0, 3, 0);
            }
            self->unk_7FC = func_02008258(self, self->unk_7F0);
            func_0200d4e8(self, 3, 1, -1);
            func_0203e3f8();
            func_0200f268(self, 5);
            func_0200f268(self, 0x18);
            func_0200f268(self, 3);
        } else {
            func_0200c3b0(self, 3, 5, -1);
            func_0200f268(self, 5);
        }
    }
}

void func_020095f4(int arg)
{
    int temp;

    temp = func_020097c0((UnkStruct_020097c0_2 *) arg);
    func_02009728((UnkStruct_02009728 *) arg);
    func_020096ac((UnkStruct_020096ac *) arg);
    func_02010d64(arg);
    func_02009624((UnkStruct_02009624 *) arg, temp);
}

void func_020095f0(unsigned short *p0, int p1)
{
    p0[0] = p1;
}

int func_020095b0(int p1, int p2, int p3, int p4)
{
    UnkStruct_020095b0 local;
    int result;

    func_0200e92c(&local);
    func_0200e90c(&local, 0x70, p3, p4);
    func_020095f0((unsigned short *) local.data, p2);
    result = func_0200e894(p1, &local);
    func_0200e91c(&local);
    return result;
}

void func_020095ac(unsigned short *p0, int p1)
{
    p0[0] = p1;
}

void func_0200956c(void *a, void *b, int previous)
{
    signed short *s;
    char *p;

    s = (signed short *) ((char *) b + 12);
    p = (char *) a + 0x7D4;
    if (func_0200f290((UnkStruct_020097c0_2 *) a, 0x17) == 0) {
        func_020109fc(a, 1, 3, 0);
    }
    func_020095ac((unsigned short *) p, *s);
    func_0200f27c(a, 6);
}

void func_02009568(void *object, int event) {}

void func_02009534(UnkStruct_02009534_2 *self)
{
    short tmp;
    UnkStruct_02009534 *sub;

    sub = &self->sub;
    tmp = self->unk_8E;
    sub->unk_02 = tmp;
    func_020113e0(&tmp, (short) sub->unk_00);
    func_020110a0((UnkStruct_020097c0_2 *) self, &tmp);
}

void func_02009504(UnkStruct_02009504 *param)
{
    if (param->unk_7D4 == param->unk_8E) {
        func_0200c3b0((UnkStruct_02009624 *) param, 3, 5, -1);
        func_0200f268((UnkStruct_02009624 *) param, 6);
    }
}

void func_020094e4(unsigned int a)
{
    func_02009534((UnkStruct_02009534_2 *) a);
    func_02010f5c(a);
    func_02010d64(a);
    func_02009504((UnkStruct_02009504 *) a);
}

void *func_020094a0(void *obj, unsigned char b, unsigned char c, unsigned char d, unsigned int e, signed short f)
{
    Buffer buf;
    void *ret;

    func_0200e92c((UnkStruct_020095b0 *) (&buf));
    func_0200e90c((UnkStruct_020095b0 *) (&buf), 0x76, e, (signed short) f);
    {
        unsigned char *p = buf.data;
        p[0] = b;
        p[1] = c;
        p[2] = d;
    }
    ret = (void *) func_0200e894((int) obj, (UnkStruct_020095b0 *) (&buf));
    func_0200e91c((UnkStruct_020095b0 *) (&buf));
    return ret;
}
