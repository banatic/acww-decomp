/* field_actor_57: 17 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02219718 @ 0x02219718, 0x38 bytes, Thumb
 * func_ov003_022196e0 @ 0x022196e0, 0x38 bytes, Thumb
 * func_ov003_02219668 @ 0x02219668, 0x78 bytes, Thumb
 * func_ov003_02219648 @ 0x02219648, 0x1e bytes, Thumb
 * func_ov003_02219604 @ 0x02219604, 0x44 bytes, Thumb
 * func_ov003_022195c8 @ 0x022195c8, 0x3c bytes, Thumb
 * func_ov003_022195c0 @ 0x022195c0, 0x8 bytes, Thumb
 * func_ov003_022195b0 @ 0x022195b0, 0x10 bytes, Thumb
 * func_ov003_022195ac @ 0x022195ac, 0x4 bytes, Thumb
 * func_ov003_022195a8 @ 0x022195a8, 0x4 bytes, Thumb
 * func_ov003_022194a8 @ 0x022194a8, 0x100 bytes, Thumb
 * func_ov003_0221947c @ 0x0221947c, 0x2c bytes, Thumb
 * func_ov003_02219438 @ 0x02219438, 0x44 bytes, Thumb
 * func_ov003_022191c0 @ 0x022191c0, 0x278 bytes, Thumb
 * func_ov003_022190b0 @ 0x022190b0, 0x110 bytes, Thumb
 * func_ov003_02218ff0 @ 0x02218ff0, 0xc0 bytes, Thumb
 * func_ov003_02218fec @ 0x02218fec, 0x4 bytes, Thumb
 */

#include "types.h"

#define IN(v, lo, hi) ((v) >= (lo) && (v) <= (hi))

typedef struct UnkStruct_02219718 UnkStruct_02219718;

struct UnkStruct_02219718 {
    char pad_00[0xd];
    unsigned char flag;
    char pad_0E[0xe];
    unsigned int unk_1C;
};

typedef struct {
    char pad_00[0x7d4];
    UnkStruct_02219718 sub;
} UnkStruct_02219718_2;

typedef struct {
    int a;
    int b;
} Pair2;

typedef struct {
    char pad_00[0x24];
    int unk_24;
    int unk_28;
    int unk_2C;
} UnkStruct_02219668;

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

typedef struct {
    char pad_00[0xc];
    unsigned short unk_0C;
    char pad_0E[0xe];
} LocalObj;

typedef struct {
    u16 id;
    u16 pad;
    int unk_04;
    int unk_08;
    u8 unk_0C;
    u8 unk_0D;
} UnkStruct_022194a8;

typedef struct {
    char pad[0xc];
    u16 unk_0C;
} Src;

typedef struct {
    int pad_00;
    int unk_04;
    int unk_08;
    unsigned char unk_0C;
} UnkStruct_02219438;

typedef struct {
    int m[9];
    int tx, ty, tz;
} Mtx43;

typedef struct {
    int x, y, z;
} Vec3_022191c0;

typedef struct {
    volatile unsigned short a;
    short b, c, d;
} Id;

typedef struct {
    int unk_00;
    int unk_04;
    char pad_08[5];
    unsigned char st;
} UnkStruct_022190b0;

typedef struct {
    int x, y, z;
} Vec3_02218ff0;

typedef struct {
    int w[12];
} Mtx;

typedef struct {
    char pad_00[0xc4];
    Vec3_02218ff0 v;
    short d0;
    char pad_D2[0x298 - 0xd2];
    Mtx a;
    char pad_2C8[0x698 - 0x2c8];
    Mtx b;
} UnkStruct_02218ff0;

extern UnkStruct_02219718_2 *func_02096718(int);
extern int func_0200fbe0(void *argument0);
extern void *func_02095794(void *);
extern void MTX_MultVec43(const Vec3 *a, const UnkStruct_02219668 *b, Vec3 *c);
extern void func_02095764(unsigned short *, int);
extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, void *, void *);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern void func_020778b0(int, int, ...);
extern int func_02077898(int x);
extern void *data_020ccf94;
extern void func_ov003_0222e898(int a, int b);
extern int func_0204fea4(void);
extern void func_020109a0(void *self, int b, int c, unsigned short d);
extern int func_0200f328(void *self, int a);
extern int func_02073908(void *a, int b);
extern void func_0209129c(int);
extern void func_0204fdbc(int);
extern void func_ov003_0222e6c4(unsigned char, int);
extern int func_0200faf0(void *self, int k);
extern int _s32_div_f(int a, int b);
extern int func_0203f7d0(Vec3_022191c0 *a, Vec3_022191c0 *b);
extern void func_02091278(int h, Vec3_022191c0 *v, int a, int b);
extern int func_0209120c(int k, Vec3_022191c0 *v, int a, int b);
extern int func_ov003_0222d83c(int a, unsigned short *p, Mtx43 *m, int c);
extern void func_ov003_0222aaa0(Vec3_022191c0 *v, int k);
extern int FX_MulFunc(int a, int b);
extern int func_0204fdec(int x, int y, void *position, void *scale, short rotation_x, short rotation_y, short rotation_z,
                         unsigned char flag0, unsigned char flag1, unsigned int tag);
extern int func_02056f28(void *, int);
extern int func_02056f94(void *);
extern int func_0200c9a8(void *, int, int, int);
extern void func_02010f5c(void *self);
extern void func_0200ee40(void *self);
extern int func_0200f554(void *self);
extern void func_02010d64(void *self);
extern int func_0201100c(void *self);

int func_ov003_02219718(void)
{
    UnkStruct_02219718_2 *p = func_02096718(4);

    if (p != 0) {
        if (p->sub.unk_1C == 6) {
            UnkStruct_02219718 *s = &p->sub;

            if (s->flag == 1) {
                s->flag = 2;
                return 1;
            }
        }
    }

    return 0;
}

void *func_ov003_022196e0(void *arg)
{
    void *p = (void *) func_02096718((int) arg);
    if (p != 0 && func_0200fbe0(p) == 3) {
        Pair2 *base = (Pair2 *) ((char *) p + 0x5c8);
        if (base->b > 1) {
            return base + 1;
        }
    }
    return func_02095794(arg);
}

void func_ov003_02219668(UnkStruct_02219668 *obj, const Vec3 *target)
{
    int old_24;
    int old_28;
    int old_2c;
    UnkStruct_02219668 tmp;
    Vec3 arg;
    Vec3 out;

    old_24 = obj->unk_24;
    old_28 = obj->unk_28;
    old_2c = obj->unk_2C;

    obj->unk_2C = 0;
    obj->unk_28 = obj->unk_2C;
    obj->unk_24 = obj->unk_28;

    tmp = *obj;

    if (target == 0) {
        arg.x = 0x4cd;
        arg.y = 0;
        arg.z = 0;
    } else {
        arg.x = target->x;
        arg.y = target->y;
        arg.z = target->z;
    }

    MTX_MultVec43(&arg, &tmp, &out);

    obj->unk_24 = out.x + old_24;
    obj->unk_28 = out.y + old_28;
    obj->unk_2C = out.z + old_2c;
}

void func_ov003_02219648(void)
{
    int x;

    x = (int) func_02096718(4);
    if (x != 0) {
        func_020109a0((void *) x, 0x99, 3, 0);
    }
}

int func_ov003_02219604(void)
{
    unsigned short w;
    unsigned int t;
    unsigned short wv;

    func_02095764(&w, 4);
    t = 0;
    wv = w;
    if (*(volatile unsigned short *) &w >= 0x1376 && wv <= 0x1376) {
        t = 1;
    }
    if (t > 0 || IN(wv, 0x1377, 0x1377)) {
        return 1;
    }
    return 0;
}

int func_ov003_022195c8(void *p0, unsigned short p1, void *p2, void *p3)
{
    LocalObj local;
    int result;
    func_0200e92c(&local);
    func_0200e90c(&local, 6, p2, p3);
    local.unk_0C = p1;
    result = func_0200e894(p0, &local);
    func_0200e91c(&local);
    return result;
}

void func_ov003_022195c0(void *receiver, int value)
{
    func_020778b0((int) receiver, value);
}

void func_ov003_022195b0(int x, unsigned short *out)
{
    *out = func_02077898(x);
}

void func_ov003_022195ac(unsigned char *p0, int p1)
{
    p0[2] = p1;
}

int func_ov003_022195a8(unsigned char *p0)
{
    return p0[2];
}

void func_ov003_022194a8(char *self, Src *src, int previous)
{
    u16 v;
    u16 id;
    UnkStruct_022194a8 *w;
    int f;
    u16 a0, a1;
    int code;
    void *q;
    int x;
    u16 h;

    w = (UnkStruct_022194a8 *) (self + 0x7d4);
    id = src->unk_0C;
    v = id;
    w->id = id;
    f = 0;
    w->unk_04 = -1;
    w->unk_08 = 0;

    a0 = *(volatile u16 *) &v;
    a1 = *(volatile u16 *) &v;
    if (a1 >= 0x12e8 && a0 <= 0x131f) {
        f = 1;
    }
    w->unk_0C = (u8) f;
    w->unk_0D = 0;

    if (w->unk_0C == 0) {
        f = 0;
        a0 = *(volatile u16 *) &v;
        a1 = *(volatile u16 *) &v;
        if (a1 >= 0x12b0 && a0 <= 0x12e7) {
            f = 1;
        }
        x = f ? (a0 - 0x12b0) : -1;
        func_ov003_0222e898((u8) x, (u8) * (int *) (self + 0x800));
        code = 0x9f;
    } else {
        w->unk_08 = func_0204fea4();
        code = 0x9e;
    }

    func_020109a0(self, code, 3, 3);
    func_0200f328(self, 0x4f);

    q = self + 0x8f0;
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        func_ov003_022195c0(q, id);
        func_ov003_022195ac((unsigned char *) q, 0);
    } else {
        if ((unsigned int) func_ov003_022195a8((unsigned char *) q) >= 1) {
            w->unk_0D = 1;
            h = (u16) (*(u32 *) (self + 0x2d4) >> 12);
            h = h - 1;
            *(int *) (self + 0x2d8) = h << 12;
        }
    }
}

void func_ov003_0221947c(void *r0, void *r1)
{
    unsigned short local;
    func_ov003_022195b0((int) ((char *) r0 + 0x8f0), &local);
    func_ov003_022195c8(r0, local, (void *) 5, r1);
}

void func_ov003_02219438(void *base)
{
    UnkStruct_02219438 *sub = (UnkStruct_02219438 *) ((char *) base + 0x7d4);
    if (sub->unk_04 > -1) {
        func_0209129c(sub->unk_04);
    }
    if (sub->unk_0C == 0) {
        func_ov003_0222e6c4((unsigned char) (*(unsigned int *) ((char *) base + 0x800)), 1);
    } else {
        func_0204fdbc(sub->unk_08);
    }
}

void func_ov003_022191c0(char *self)
{
    Id id;
    Mtx43 m;
    Vec3_022191c0 v;
    Vec3_022191c0 w;
    Vec3_022191c0 vv;
    char *p7d4;
    int *p7d8;
    int t;
    int q;
    int ok;
    unsigned short lo, hi;
    int k;
    short s;
    int d8;
    float f;
    int fx;

    p7d4 = self + 0x7d4;
    id.a = *(unsigned short *) p7d4;
    p7d8 = (int *) (p7d4 + 4);
    func_0200faf0(self, 0x400);
    m = *(Mtx43 *) (self + 0x698);
    v.x = 0x4cd;
    v.y = 0;
    v.z = 0;
    t = (int) ((unsigned int) (*(int *) (self + 0x2d8) << 4) >> 16);
    if (*(int *) (self + 0x704) != 0xa0 && t >= 0x10) {
        q = _s32_div_f(0x19a * (t - 0xf), 0xc);
        v.x = v.x + q * 2;
        v.y = v.y + q;
        v.z = v.z - q;
    }
    func_ov003_02219668((UnkStruct_02219668 *) (&m), (const Vec3 *) (&v));
    d8 = *p7d8;
    ok = 0;
    if (d8 > -1) {
        w.x = m.tx;
        w.y = m.ty;
        w.z = m.tz;
        func_0203f7d0(&w, &w);
        func_02091278(*p7d8, &w, 0, 0);
    } else if (d8 == -1) {
        *p7d8 = -2;
        if (*(unsigned char *) (p7d4 + 0xc) == 0) {
            lo = id.a;
            hi = id.a;
            if (hi >= 0x12b0 && lo <= 0x12e7) {
                ok = 1;
            }
            if (ok != 0) {
                k = lo - 0x12b0;
            } else {
                k = -1;
            }
            if (k == 0x18 || k == 0x30 || k == 0x32 || k == 0x33) {
                w.x = m.tx;
                w.y = m.ty;
                w.z = m.tz;
                func_0203f7d0(&w, &w);
                *p7d8 = func_0209120c(0x5a, &w, 0, 0);
            }
        }
    }
    if (*(int *) (self + 0x704) != 0xa0) {
        if (t <= 0xa) {
            s = 0;
        } else if (t < 0x10) {
            s = 0x11 * (t - 0xa);
        } else {
            s = 0x64;
        }
    } else {
        if (t < 6) {
            s = 0x64 - 0x11 * t;
        } else {
            s = 0;
        }
    }
    if (*(unsigned char *) (p7d4 + 0xc) == 0) {
        id.b = s;
        id.c = s;
        id.d = s;
        func_ov003_0222d83c((unsigned char) *(int *) (self + 0x800), (unsigned short *) &id.b, &m, 0);
        return;
    }
    f = s / 100.0f;
    fx = (int) (f > 0.0f ? 0.5f + 4096.0f * f : 4096.0f * f - 0.5f);
    ok = 0;
    lo = id.a;
    hi = id.a;
    if (hi >= 0x12e8 && lo <= 0x131f) {
        ok = 1;
    }
    if (ok != 0) {
        k = lo - 0x12e8;
    } else {
        k = -1;
    }
    func_ov003_0222aaa0(&vv, k);
    vv.x = FX_MulFunc(vv.x, fx);
    vv.y = FX_MulFunc(vv.y, fx);
    vv.z = FX_MulFunc(vv.z, fx);
    w.x = m.tx;
    w.y = m.ty;
    w.z = m.tz;
    func_0203f7d0(&w, &w);
    ok = 0;
    lo = id.a;
    hi = id.a;
    if (hi >= 0x12e8 && lo <= 0x131f) {
        ok = 1;
    }
    if (ok != 0) {
        k = lo - 0x12e8;
    } else {
        k = -1;
    }
    func_0204fdec(*(int *) (p7d4 + 8), k, &w, &vv, 0, 0, 0, 1, 1, 0x1f);
}

void func_ov003_022190b0(char *a)
{
    UnkStruct_022190b0 *p = (UnkStruct_022190b0 *) (a + 0x7d4);
    void *q = a + 0x8f0;
    unsigned char *st = &p->st;

    switch (p->st) {
        case 0:
            if (func_02056f28(a + 0x2d0, 0xa)) {
                func_0200f328(a, 0x63);
            } else if (func_02056f28(a + 0x2d0, 0x19)) {
                func_0200f328(a, 0x7f2);
            }
            if (func_02056f94(a + 0x2d0)) {
                *st = 1;
                func_ov003_022195ac((unsigned char *) q, 1);
            }
            break;
        case 1:
            if (func_02073908((void *) ((*(int *) &data_020ccf94)), *(int *) (a + 0x800)) == 0) {
                if ((unsigned int) func_ov003_022195a8((unsigned char *) q) >= 2) {
                    *st = 2;
                }
            }
            break;
        case 2:
            if (p->unk_04 > -1) {
                func_0209129c(p->unk_04);
            }
            if (func_02073908((void *) ((*(int *) &data_020ccf94)), *(int *) (a + 0x800)) != 0) {
                func_ov003_022195ac((unsigned char *) q, 2);
            }
            func_020109a0(a, 0xa0, 3, 0);
            func_0200f328(a, 0x7f1);
            *st = 3;
            break;
        case 3:
            if (func_02056f94(a + 0x2d0)) {
                func_0200c9a8(a, 3, 5, -1);
            }
            break;
    }
}

void func_ov003_02218ff0(UnkStruct_02218ff0 *self)
{
    Vec3_02218ff0 *p;
    volatile Vec3_02218ff0 sv;
    short d;
    Mtx sa, sb;

    func_02010f5c(self);
    p = &self->v;
    sv.x = self->v.x;
    sv.y = p->y;
    sv.z = p->z;
    d = self->d0;
    sa = self->a;
    sb = self->b;
    func_0200ee40(self);
    func_ov003_022191c0((char *) self);
    self->v.x = sv.x;
    self->v.y = sv.y;
    self->v.z = sv.z;
    self->d0 = d;
    self->a = sa;
    self->b = sb;
    if (func_0200f554(self) != 0) {
        func_0201100c(self);
    }
    func_02010d64(self);
    func_ov003_022190b0((char *) self);
}

void func_ov003_02218fec(unsigned short *p0, int p1)
{
    p0[0] = p1;
}
