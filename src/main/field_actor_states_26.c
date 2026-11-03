/* field_actor_states_26: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200d1a0 @ 0x0200d1a0, 0x40 bytes, Thumb
 * func_0200d198 @ 0x0200d198, 0x6 bytes, Thumb
 * func_0200d148 @ 0x0200d148, 0x50 bytes, Thumb
 * func_0200d144 @ 0x0200d144, 0x2 bytes, Thumb
 * func_0200d0b0 @ 0x0200d0b0, 0x94 bytes, Thumb
 * func_0200cf50 @ 0x0200cf50, 0x160 bytes, Thumb
 * func_0200ce2c @ 0x0200ce2c, 0x124 bytes, Thumb
 * func_0200cdc8 @ 0x0200cdc8, 0x64 bytes, Thumb
 * func_0200cce8 @ 0x0200cce8, 0xe0 bytes, Thumb
 * func_0200cccc @ 0x0200cccc, 0x1c bytes, Thumb
 * func_0200cc44 @ 0x0200cc44, 0x88 bytes, Thumb
 * func_0200cc40 @ 0x0200cc40, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char data[12];
} UnkStruct_0200d1a0;

typedef struct {
    char data[16];
} UnkStruct_0200d1a0_2;

typedef struct {
    unsigned long unk_00;
} UnkStruct_0200d198;

typedef struct UnkStruct_0200cf50 {
    int x, y, z;
} UnkStruct_0200cf50;

typedef struct UnkStruct_0200cf50_3 {
    u8 pad_00[0x5c];
    UnkStruct_0200cf50 v;
    u8 pad_68[0x8e - 0x68];
    short unk_8E;
    u8 pad_90[0x98 - 0x90];
    int unk_98;
} UnkStruct_0200cf50_3;

typedef struct UnkStruct_0200cf50_2 {
    u8 unk_00;
    u8 unk_01;
    short unk_02;
    short unk_04;
    short unk_06;
} UnkStruct_0200cf50_2;

typedef struct UnkStruct_0200ce2c {
    int x, y, z;
} UnkStruct_0200ce2c;

typedef struct UnkStruct_0200ce2c_2 {
    int unk_00;
    int unk_04;
    char pad_08[0x10 - 8];
    int unk_10;
} UnkStruct_0200ce2c_2;

typedef struct Other {
    char pad_00[0x9c];
    UnkStruct_0200ce2c_2 sub;
} Other;

typedef struct UnkStruct_0200ce2c_3 {
    char pad_00[0x5c];
    UnkStruct_0200ce2c v;
    char pad_68[0x98 - 0x68];
    int unk_98;
    char pad_9C[0x134 - 0x9c];
    int unk_134;
    short unk_138;
    char pad_13A[0x234 - 0x13a];
    char unk_234;
    char pad_235[0x2d4 - 0x235];
    int unk_2D4;
    char pad_2D8[0x2e0 - 0x2d8];
    int unk_2E0;
    char pad_2E4[0x5a0 - 0x2e4];
    char unk_5A0;
    char pad_5A1[0x704 - 0x5a1];
    int unk_704;
} UnkStruct_0200ce2c_3;

struct UnkStruct_0200cdc8 {
    char pad_00[0x98];
    int unk_98;
    char pad_9C[0x668];
    int unk_704;
};

typedef struct self_t {
    unsigned char pad_00[0x98];
    unsigned int unk_98;
    unsigned char pad_9C[0x704 - 0x9c];
    unsigned int unk_704;
    unsigned char pad_708[0x7d4 - 0x708];
    int unk_7D4;
    unsigned char pad_7D8[0x8e8 - 0x7d8];
    unsigned char unk_8E8;
} UnkStruct_0200cce8;

extern unsigned int func_0200e92c(UnkStruct_0200d1a0 *);
extern void func_0200e90c(UnkStruct_0200d1a0 *, int, int, int);
extern void func_0200d1e0(UnkStruct_0200d1a0_2 *, int);
extern int func_0200e894(int, UnkStruct_0200d1a0 *);
extern int func_0200e91c(UnkStruct_0200d1a0 *);
extern void func_020109fc(void *a, int b, int c, int d);
extern int func_0200fbe0(void *a);
extern void func_0205eae0(void *a, int b, int c, int d);
extern int func_02010718(void *a);
extern int func_020113b0(int a, int b);
extern int func_02011398(int a, int b);
extern int func_0200dc48(void *a);
extern int func_020113e0(short *p, int b);
extern void func_020110a0(void *a, short *p);
extern int FX_MulFunc(int a, int b);
extern void func_0201107c(void *a, int *p);
extern short FX_SinCosTable_[];
extern int func_0200e9a8(UnkStruct_0200cf50_3 *s, UnkStruct_0200cf50_2 *a, int *b, int *c, short *d);
extern int func_020b65c4(void);
extern int func_0200e93c(UnkStruct_0200cf50_3 *s, int a, int b, int c, int d, short *e);
extern int FX_Sqrt(int a);
extern int FX_Div(int a, int b);
extern int func_020b03c0(UnkStruct_0200ce2c *out, int *b, int *c, int d, int e);
extern int func_020ea990(UnkStruct_0200ce2c *a, UnkStruct_0200ce2c *b);
extern Other *func_0205e8e4(void *p);
extern void func_020109c8(UnkStruct_0200ce2c_3 *s, int a, int b, int c);
extern void func_02054860(void *p);
extern void func_0200f95c(UnkStruct_0200ce2c_3 *s);
extern void func_02006530(void *obj, int a, int b);
extern void func_0201108c(void *obj, int value);
extern unsigned char data_020e54a8;
extern int func_020984e8(void);
extern int func_02099784(unsigned char *);
extern void func_020112f8(void *dst, void *src);
extern int func_020644cc(int);
extern int func_ov003_0220edcc(void *self, int a, int b);
extern int func_0200d4e8(void *self, int a, int b, int c);
extern int func_0200dc8c(void *self);
extern int func_020e8b4c(int a, signed short b);
extern int func_0200cc00(void *self, int a, int b, int c);
extern int func_02010538(void *self);
extern int data_020ccf94;
extern int func_02073908(int, int);
extern int func_0201100c(int);
extern void func_02010d64(int);
extern int func_02010ca4(int);
extern int func_02010ff4(int);
extern void func_0200ef1c(int);

int func_0200d1a0(int p0, int p1, int p2, int p3)
{
    UnkStruct_0200d1a0 v1;
    UnkStruct_0200d1a0_2 v2;
    int result;

    func_0200e92c(&v1);
    func_0200e90c(&v1, 3, p2, p3);
    func_0200d1e0(&v2, p1);
    result = func_0200e894(p0, &v1);
    func_0200e91c(&v1);
    return result;
}

void func_0200d198(UnkStruct_0200d198 *p)
{
    p->unk_00 = 0;
}

void func_0200d148(void *a, void *b, int previous)
{
    unsigned char *q = (unsigned char *) b + 0xc;
    unsigned int *p = (unsigned int *) ((char *) a + 0x7d4);
    int three = 3;

    func_020109fc(a, 1, three, three);
    if (func_0200fbe0(a) == 4) {
        func_0205eae0((char *) a + 0x5a0, 1, three, 0);
    }
    func_0200d198((UnkStruct_0200d198 *) p);
    if (*q) {
        *p = 0x456;
    }
}

void func_0200d144(void *object, int event) {}

void func_0200d0b0(char *a)
{
    int *p = (int *) (a + 0x7d4);
    int cur = func_02010718(a);

    if (*p < cur) {
        *p = func_020113b0(*p, cur);
    } else if (*p > cur) {
        *p = func_02011398(*p, cur);
    }

    {
        int r7 = func_0200dc48(a);
        short local = *(short *) (a + 0x8e);

        if (cur > 0) {
            func_020113e0(&local, r7);
            func_020110a0(a, &local);
        }

        {
            short diff = (short) (local - r7);
            unsigned short udiff = (unsigned short) diff;
            int idx = (udiff >> 4) * 2 + 1;
            int t = FX_MulFunc(*p, FX_SinCosTable_[idx]);
            int val;
            if (t < 0) {
                t = -t;
            }
            val = t;
            func_0201107c(a, &val);
        }
    }
}

int func_0200cf50(UnkStruct_0200cf50_3 *self)
{
    UnkStruct_0200cf50_2 s;
    int v10;
    int v14;
    int cur;
    int dx;
    int dz;
    int acc;
    int mag;
    int lim;
    int k;
    int tv;
    int tt;
    int j;

    if (func_0200e9a8(self, &s, &v10, &v14, &s.unk_02) == 0) {
        return 1;
    }
    if (s.unk_00 != func_020b65c4()) {
        return 1;
    }
    dx = v10 - self->v.x;
    dz = v14 - self->v.z;
    acc = FX_MulFunc(dx, dx);
    acc = acc + FX_MulFunc(dz, dz);
    if (func_0200e93c(self, dx, dz, acc, s.unk_02, &s.unk_04) == 0) {
        return 1;
    }
    s.unk_06 = self->unk_8E;
    func_020113e0(&s.unk_06, s.unk_04);
    func_020110a0((void *) self, &s.unk_06);
    cur = self->unk_98;
    mag = FX_Sqrt(acc);
    lim = mag;
    if (mag > 0x6e2) {
        lim = 0x6e2;
    }
    k = (int) (unsigned short) (short) (s.unk_06 - s.unk_04) >> 4;
    j = (k << 1) + 1;
    tv = FX_SinCosTable_[j];
    if (tv < 0) {
        tv = 0;
    }
    acc = FX_MulFunc(lim, tv);
    if (mag >= 0x2666) {
        if (mag >= 0xe000) {
            self->v.x = v10;
            self->v.z = v14;
            self->unk_8E = s.unk_02;
            return 1;
        }
    } else {
        tt = FX_MulFunc(mag - 0x108, FX_Div(0x5da, 0x255e));
        tt = tt + 0x108;
        if (tt < 0x108) {
            tt = 0x108;
        }
        if (acc > tt) {
            acc = tt;
        }
    }
    if (cur < acc) {
        cur = func_020113b0(cur, acc);
    } else if (cur > acc) {
        cur = func_02011398(cur, acc);
    }
    func_0201107c((void *) self, &cur);
    return 0;
}

void func_0200ce2c(UnkStruct_0200ce2c_3 *self)
{
    int b;
    int v;
    int c;
    UnkStruct_0200ce2c nv;
    UnkStruct_0200ce2c old;
    int ok;
    int r;
    UnkStruct_0200ce2c *p;
    UnkStruct_0200ce2c_2 *q;

    v = self->unk_98;
    p = &self->v;
    old.x = p->x;
    old.y = p->y;
    old.z = p->z;
    ok = func_020b03c0(&nv, &b, &c, self->unk_134, self->unk_138);
    if (ok) {
        p = &self->v;
        p->x = nv.x;
        p->y = nv.y;
        p->z = nv.z;
        func_020110a0((void *) self, (short *) (&b));
        v = func_020ea990(&self->v, &old);
        func_0201107c((void *) self, &v);
        v = c;
        v = v << 2;
    }
    r = FX_MulFunc(v, 0x3ae1);
    if (r <= self->unk_2D4) {
        self->unk_2E0 = r;
        q = &func_0205e8e4(&self->unk_5A0)->sub;
        if (r <= q->unk_04) {
            q = &func_0205e8e4(&self->unk_5A0)->sub;
            q->unk_10 = r;
        }
    }
    if (ok) {
        if (self->unk_704 != 3) {
            func_020109c8(self, 3, 3, 3);
        }
    } else {
        if (v > 0x53f) {
            if (self->unk_704 != 2) {
                func_020109c8(self, 2, 3, 3);
            }
        } else {
            if (self->unk_704 != 1) {
                func_020109c8(self, 1, 3, 3);
            }
        }
    }
    func_02054860(&self->unk_234);
    func_0200f95c(self);
}

void func_0200cdc8(struct UnkStruct_0200cdc8 *obj)
{
    int diff;
    int q;
    int tmp;
    int val;
    if (obj->unk_704 != 2) {
        func_02006530(obj, 0x93, 1);
        return;
    }
    diff = obj->unk_98 - 0x53f;
    if (diff < 0) {
        func_02006530(obj, 0x93, 1);
    }
    q = FX_Div(diff, 0x1a3);
    tmp = FX_MulFunc((int) ((void *) 0x00c17000), q);
    val = (tmp << 4) >> 16;
    func_0201108c(obj, val);
}

int func_0200cce8(UnkStruct_0200cce8 *self, signed short *p)
{
    unsigned int cond = (data_020e54a8 == 0) ? 1 : 0;

    if (cond > 0) {
        if (self->unk_8E8 != 0) {
            goto other;
        }
        if (self->unk_98 != 0x6e2) {
            goto other;
        }

        if (func_02099784((unsigned char *) func_020984e8()) != 2) {
            unsigned short tmp[4];
            func_020112f8(tmp, self);
            if (tmp[0] != 0x13c3) {
                goto other;
            }
        }

        if (func_020644cc(0x17a) != 0) {
            goto other;
        }

        return func_ov003_0220edcc(self, 6, -1);
    }

other:
    if (self->unk_7D4 <= 0) {
        func_0200d4e8(self, 3, 1, -1);
    }

    if (self->unk_704 == 2) {
        if (func_0200dc8c(self) > 0) {
            int m = func_0200dc48(self);
            if (func_020e8b4c(m, p[0]) > 0x3a4c) {
                func_0200cc00(self, m, 3, -1);
            }
        }
    }

    return func_02010538(self);
}

void func_0200cccc(int a, unsigned char *b)
{
    if (*b != 0) {
        func_0200d4e8((void *) a, 3, 1, -1);
    }
}

void func_0200cc44(int r0)
{
    int r4 = r0;
    short local;
    char local2;

    if (func_02073908(data_020ccf94, *(int *) (r4 + 0x800)) != 0) {
        local = *(short *) (r4 + 0x94);
        func_0200d0b0((char *) r4);
        func_0200ce2c((UnkStruct_0200ce2c_3 *) r4);
        func_0200cdc8((struct UnkStruct_0200cdc8 *) r4);
        func_0201100c(r4);
        func_02010d64(r4);
        func_02010ca4(r4);
        func_0200cce8((UnkStruct_0200cce8 *) r4, (signed short *) (&local));
    } else {
        local2 = func_0200cf50((UnkStruct_0200cf50_3 *) r4);
        func_0200ce2c((UnkStruct_0200ce2c_3 *) r4);
        func_0200cdc8((struct UnkStruct_0200cdc8 *) r4);
        func_02010ff4(r4);
        func_0200ef1c(r4);
        func_0200cccc(r4, (unsigned char *) (&local2));
    }
}

void func_0200cc40(unsigned short *p0, int p1)
{
    p0[0] = p1;
}
