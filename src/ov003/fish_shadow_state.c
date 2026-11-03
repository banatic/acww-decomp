/* fish_shadow_state: 15 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02227a30 @ 0x02227a30, 0x18 bytes, Thumb
 * func_ov003_022279d8 @ 0x022279d8, 0x58 bytes, Thumb
 * func_ov003_0222799c @ 0x0222799c, 0x3c bytes, Thumb
 * func_ov003_0222796c @ 0x0222796c, 0x30 bytes, Thumb
 * func_ov003_02227950 @ 0x02227950, 0x1c bytes, Thumb
 * func_ov003_0222793c @ 0x0222793c, 0x12 bytes, Thumb
 * func_ov003_0222791c @ 0x0222791c, 0x20 bytes, Thumb
 * func_ov003_022278e0 @ 0x022278e0, 0x3c bytes, Thumb
 * func_ov003_0222780c @ 0x0222780c, 0xd4 bytes, Thumb
 * func_ov003_022277fc @ 0x022277fc, 0x10 bytes, Thumb
 * func_ov003_02227778 @ 0x02227778, 0x84 bytes, Thumb
 * func_ov003_02227680 @ 0x02227680, 0xf8 bytes, Thumb
 * func_ov003_02227654 @ 0x02227654, 0x2c bytes, Thumb
 * func_ov003_02227638 @ 0x02227638, 0x1c bytes, Thumb
 * func_ov003_02227608 @ 0x02227608, 0x30 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x48];
    int unk_48;
    char pad_4C[0x14];
    Vec3 unk_60;
    char pad_6C[0x38];
} UnkStruct_022278e0;

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
} UnkStruct_02227680;

typedef struct {
    int unk_00;
    int unk_04;
    char unk_08[0x50];
    UnkStruct_02227680 a;
    char pad_B8[0x64];
    int unk_11C;
} UnkStruct_02227680_2;

typedef struct {
    char pad_00[0x24c];
} UnkStruct_02227654;

int func_020ba4e4(void);
extern int func_020e8840(void *p);
int func_020644cc(int n);
extern UnkStruct_022278e0 data_ov003_0225f4dc[];
extern char *func_020961a8(int idx);
extern int func_0200322c(Vec3 *a, Vec3 *b);
extern void func_ov003_0222a7bc(char *rec, int v, int kind);
extern void *data_ov003_0223bdb8;
extern int func_0205556c(void *r, int tag, void *h);
extern void *func_0209d238(void *arg, void *p);
extern void *func_0209d324(void *argument0);
extern void *NNS_G3dGetJntAnmSet(void *m);
extern void *func_02107b44(void *a, int b);
extern int func_02055140(void *r, void *p);
extern void func_02055060(void *r, void *q, int a, int b, int c, int d);
extern void func_02055050(void *r);
extern void *data_ov003_0223bdb0;
extern void *data_ov003_0223bdb4;
extern void *data_ov003_0223bdbc;
extern int func_0209d0ac(void *p, void *h, void *g);
extern void *func_0209d088(void *p);
extern int func_02055f2c(UnkStruct_02227680 *a, void *x, int f);
extern void *func_02064b2c(void *g, void *m, int n, int f);
extern void *NNS_G3dGetTexSRTAnmSet(void *p);
extern void *func_02107bbc(void *p, int i);
extern int func_0205650c(int *p, int q, void *m);
extern void func_02056478(int *p, void *q, int b, int c, int d);
extern void *func_02055e00(UnkStruct_02227680 *a);
extern void func_020563dc(int *p, void *q);
extern UnkStruct_02227654 data_ov003_0225f76c[];

int func_ov003_02227950(int a, int b, int c);

int func_ov003_02227a30(void *a0)
{
    int r = 0;
    if ((unsigned int) (func_020ba4e4() - 1) <= 1) {
        r = 1;
    }
    return r;
}

void func_ov003_022279d8(void *self)
{
    if (func_020e8840((char *) self + 0x212) == 0) {
        if (*(unsigned int *) ((char *) self + 0x80) <= 1) {
            u8 v;
            *(unsigned int *) ((char *) self + 0x80) = 0;
            v = *(u8 *) ((char *) self + 0x211);
            if (v < 3) {
                *(u8 *) ((char *) self + 0x1fc) = 3;
            } else if (v < 6) {
                *(u8 *) ((char *) self + 0x1fc) = 4;
            }
        }
        *(short *) ((char *) self + 0x212) = 0x960;
    }
}

int func_ov003_0222799c(Vec3 *a, Vec3 *b, int dx, int dz, int dz2)
{
    int r = 0;
    int d, e, f;
    d = b->x - a->x;
    if (d < 0) {
        d = -d;
    }
    if (d > dx) {
        return 0;
    }
    e = b->z - a->z;
    if (e >= 0) {
        if (e <= dz) {
            r = 1;
        }
    } else {
        f = a->z - b->z;
        if (f <= dz2) {
            r = 1;
        }
    }
    return r;
}

int func_ov003_0222796c(Vec3 *a, Vec3 *b, Vec3 *c)
{
    if (func_ov003_02227950(a->x, b->x, c->x) != 0 && func_ov003_02227950(a->z, b->z, c->z) != 0) {
        return 1;
    }
    return 0;
}

int func_ov003_02227950(int a, int b, int c)
{
    int r = 0;
    a = a - b;
    if (a < 0) {
        a = -a;
    }
    b = c - b;
    if (b < 0) {
        b = -b;
    }
    if (a >= b) {
        r = 1;
    }
    return r;
}

int func_ov003_0222793c(int a, int b)
{
    return a + func_020644cc(b - a);
}

int func_ov003_0222791c(int a, int b)
{
    int v = func_ov003_0222793c(a, b);
    if (func_020644cc(2) == 0) {
        v *= -1;
    }
    return v;
}

int func_ov003_022278e0(Vec3 *out, int i)
{
    int r = 0;
    UnkStruct_022278e0 *e;
    Vec3 *q;
    if (i < 0 || i >= 4) {
        return 0;
    }
    e = &data_ov003_0225f4dc[i];
    if (e->unk_48 == 1) {
        q = &e->unk_60;
        out->x = q->x;
        out->y = q->y;
        out->z = q->z;
        r = 1;
    }
    return r;
}

int func_ov003_0222780c(int idx, int id, Vec3 *pos)
{
    volatile u16 t;
    Vec3 v;
    int ok;
    u16 lo;
    u16 hi;
    char *rec;
    char *p;
    int d;
    Vec3 *q;
    t = id;
    ok = 0;
    lo = t;
    hi = t;
    if (hi >= 0x12e8 && lo <= 0x131f) {
        ok = 1;
    }
    if (!ok) {
        return 0;
    }
    if (idx < 0 || idx >= 4) {
        return 0;
    }
    rec = &((char *) data_ov003_0225f4dc)[idx * 0xa4];
    if (*(int *) (rec + 0x40) != 0) {
        return 0;
    }
    p = func_020961a8(idx);
    if (p == 0) {
        return 0;
    }
    q = (Vec3 *) (p + 0x5c);
    v.x = q->x;
    v.y = q->y;
    v.z = q->z;
    d = t - 0x12e8;
    *(int *) (rec + 0x90) = d;
    func_ov003_0222a7bc(rec, func_0200322c(&v, pos), d);
    q = (Vec3 *) (rec + 0x60);
    q->x = v.x;
    q->y = v.y;
    q->z = v.z;
    q = (Vec3 *) (rec + 0x6c);
    q->x = pos->x;
    q->y = pos->y;
    q->z = pos->z;
    q = (Vec3 *) (rec + 0x54);
    q->x = v.x;
    q->y = v.y;
    q->z = v.z;
    *(int *) (rec + 0x7c) = 0;
    *(int *) (rec + 0x48) = 4;
    *(int *) (rec + 0x40) = 1;
    return 1;
}

void func_ov003_022277fc(char *o, int v)
{
    *(int *) (o + 0x1f0) = (v << 12) >> 4;
}

int func_ov003_02227778(char *self, void *m, void *arg)
{
    int ok = 0;
    char *r = self + 0x144;
    void *p;
    void *q;
    func_0205556c(r, 0x66736477, data_ov003_0223bdb8);
    if (m == 0) {
        return ok;
    }

    p = func_0209d324((void *) func_0209d238(arg, self + 0x7c));
    q = func_02107b44(NNS_G3dGetJntAnmSet(m), 0);
    if (func_02055140(r, p)) {
        func_02055060(r, q, 0, 0x1000, 1, 0);
        func_02055050(r);
        ok = 1;
    }
    return ok;
}

int func_ov003_02227680(UnkStruct_02227680_2 *self, void *p1)
{
    int ok;
    void *h;
    void *m;
    void *j;
    UnkStruct_02227680 *a;
    char *p8;

    ok = 0;
    h = func_0209d238(p1, (void *) (&self->unk_04));
    p8 = self->unk_08;
    if (func_0209d0ac(p8, h, data_ov003_0223bdb0) != 0) {
        a = &self->a;
        func_02055f2c(a, func_0209d088(p8), 0);
        m = func_0209d324(h);
        j = func_02107b44(NNS_G3dGetJntAnmSet(func_02064b2c(data_ov003_0223bdb4, m, 4, 0)), 0);
        if (func_02055140((void *) a, m) != 0) {
            func_02055060((void *) a, j, 0, 0x1000, 1, 0);
            func_02055050((void *) a);
        } else {
            return 0;
        }
        j = func_02107bbc(NNS_G3dGetTexSRTAnmSet(func_02064b2c(data_ov003_0223bdbc, m, 4, 0)), 0);
        if (func_0205650c(&self->unk_11C, a->unk_5C, m) != 0) {
            func_02056478(&self->unk_11C, j, 0, 0x1000, 1);
            func_020563dc(&self->unk_11C, func_02055e00(a));
        } else {
            return 0;
        }
        ok = 1;
    }
    return ok;
}

UnkStruct_02227654 *func_ov003_02227654(int i)
{
    UnkStruct_02227654 *e;
    int s;
    if (i < 0 || i >= 6) {
        return 0;
    }
    e = &data_ov003_0225f76c[i];
    s = *(int *) ((char *) e + 0x80);
    if ((unsigned int) (s - 3) > 1) {
        e = 0;
    }
    return e;
}

int func_ov003_02227638(int i)
{
    void *e = (void *) func_ov003_02227654(i);
    if (e == 0) {
        return -1;
    }
    return *(s8 *) ((char *) e + 0x7e);
}

int func_ov003_02227608(Vec3 *dst, int i)
{
    Vec3 *q;
    void *e = (void *) func_ov003_02227654(i);
    if (e == 0) {
        return 0;
    }
    q = (Vec3 *) ((char *) e + 0x120);
    dst->x = q->x;
    dst->y = q->y;
    dst->z = q->z;
    return 1;
}
