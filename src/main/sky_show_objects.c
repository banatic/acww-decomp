/* sky_show_objects: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020c03f4 @ 0x020c03f4, 0x2c bytes, Thumb
 * func_020c0324 @ 0x020c0324, 0xd0 bytes, Thumb
 * func_020c013c @ 0x020c013c, 0x1e8 bytes, Thumb
 * func_020c00fc @ 0x020c00fc, 0x40 bytes, Thumb
 * func_020c00f8 @ 0x020c00f8, 0x4 bytes, Thumb
 * func_020c0084 @ 0x020c0084, 0x74 bytes, Thumb
 * func_020c003c @ 0x020c003c, 0x48 bytes, Thumb
 * func_020bffc4 @ 0x020bffc4, 0x78 bytes, Thumb
 * func_020bff20 @ 0x020bff20, 0xa4 bytes, Thumb
 * func_020bfee4 @ 0x020bfee4, 0x3c bytes, Thumb
 * func_020bfe6c @ 0x020bfe6c, 0x78 bytes, Thumb
 * func_020bfd1c @ 0x020bfd1c, 0x150 bytes, Thumb
 * func_020bfcd8 @ 0x020bfcd8, 0x44 bytes, Thumb
 */

#include "types.h"

#define R5(c) ((int) ((((u32) ((c) << 27)) >> 27) << 12))
#define G5(c) ((int) ((((u32) ((c) << 22)) >> 27) << 12))
#define B5(c) ((int) ((((u32) ((c) << 17)) >> 27) << 12))

typedef struct {
    int v;
} UnkStruct_020c0324;

typedef struct {
    UnkStruct_020c0324 x;
    UnkStruct_020c0324 y;
    UnkStruct_020c0324 z;
} UnkStruct_020c0324_2;

typedef struct {
    unsigned char pad_00[8];
    int unk_08;
    unsigned char pad_0C[0x24 - 0xc];
    int unk_24;
    unsigned char pad_28[0x60 - 0x28];
    u32 unk_60;
    int unk_64;
} UnkStruct_020c013c;

typedef struct {
    u16 unk_00;
    u16 c1;
} UnkStruct_020c013c_2;

typedef struct {
    int e[3];
} E12;

struct UnkStruct_020c00fc {
    unsigned char pad_00[0x60];
    unsigned int flags;
};

typedef struct {
    char pad_00[0x4c];
    int unk_4C;
    int unk_50;
    char pad_54[0xc];
    unsigned int unk_60;
} UnkStruct_020c0084;

typedef struct UnkStruct_020c003c {
    char pad_00[0xc];
    int unk_0C;
    char pad_10[0x48];
    int unk_58;
    char pad_5C[4];
    int unk_60;
    int unk_64;
    int unk_68;
} UnkStruct_020c003c;

struct UnkStruct_020bffc4 {
    char pad_00[0x34];
    int unk_34;
    int unk_38;
    char pad_3C[0x20];
    char unk_5C;
    char pad_5D[0xf];
    int unk_6C;
    int unk_70;
};

typedef struct {
    unsigned char pad_00[0x3c];
    unsigned int unk_3C;
    unsigned int unk_40;
    unsigned int unk_44;
    unsigned int unk_48;
    unsigned char pad_4C[0x04];
    unsigned int unk_50;
    unsigned char pad_54[0x18];
    unsigned int unk_6C;
    unsigned int unk_70;
} UnkStruct_020bff20;

struct UnkStruct_020bfe6c {
    char pad_00[0x4];
    int unk_04;
    char pad_08[0x8];
    char sub_10[0x24];
    char unk_34[0x2c];
    unsigned int flags;
    int unk_64;
    char pad_68[0x4];
    unsigned int unk_6C;
    unsigned int unk_70;
};

typedef struct {
    u8 pad_00[4];
    int unk_04;
    u8 pad_08[0xc - 8];
    int unk_0C;
    u8 pad_10[0x31 - 0x10];
    u8 unk_31;
    u8 pad_32[0x34 - 0x32];
    int unk_34;
    u8 pad_38[0x3c - 0x38];
    int unk_3C;
    u8 pad_40[0x50 - 0x40];
    int unk_50;
    u8 pad_54[0x60 - 0x54];
    u32 unk_60;
    int unk_64;
    int unk_68;
    int unk_6C;
    int unk_70;
} UnkStruct_020bfd1c_2;

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_020bfd1c;

extern UnkStruct_020c0324_2 data_021c67d0;
extern int data_020ca0e8;
extern int data_020ca0ec;
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern int data_020d22d0[];                  // 0x020d22d0
extern UnkStruct_020c013c_2 data_020d2344[]; // 0x020d2344
extern E12 data_021fa678[];                  // 0x021fa678
extern void func_020bec14(void *o, int i, u16 *c);
extern void func_020bee4c(void *o, int v);
extern void func_020bec54(char *p, int n);
extern char data_021fba00[];
extern int data_020d274c[];
extern int data_020d2444[];
extern int data_020d27fc[];
extern int data_020d2468[];
extern int func_0208a1cc(void *p);
extern void func_020bf220(struct UnkStruct_020bffc4 *a, int b, int c);
extern void func_02065268(int a);
extern unsigned int func_020644cc(unsigned int size);
extern int func_0208a160(void *);
extern unsigned int data_020d2eec;
extern int data_021f8b48;
extern void *func_020bdc50(void *p, int a, int b, UnkStruct_020bfd1c *w, u32 v);
extern void func_020bf590(void *);

void func_020bffc4(struct UnkStruct_020bffc4 *obj, unsigned int b);
void func_020bff20(UnkStruct_020bff20 *self, unsigned int flags);
void func_020bfe6c(struct UnkStruct_020bfe6c *self);
void func_020bfd1c(UnkStruct_020bfd1c_2 *self);

int func_020c03f4(int a, int b)
{
    int result = 15;
    if (b != 0) {
        result = 0;
    } else if (a == 0) {
        result = 2;
    } else if (a == 1) {
        result = 4;
    } else if (a == 2) {
        result = 6;
    } else if (a == 3) {
        result = 8;
    }
    return result;
}

void func_020c0324(int *out, int px, int py, int flag)
{
    UnkStruct_020c0324_2 p;
    int d;
    int e;
    int n;
    int u;
    int w;
    int t;
    int s;

    p.x = data_021c67d0.x;
    p.y = data_021c67d0.y;
    p.z = data_021c67d0.z;
    e = data_020ca0e8;
    d = p.z.v - e;
    n = data_020ca0ec;
    u = n * 4 / 2;
    w = FX_Div((p.x.v - n * 3) << 4, u);
    t = FX_Div(d, e << 2);
    if (w < -0x10000) {
        w = -0x10000;
    } else if (w > 0x10000) {
        w = 0x10000;
    }
    if (t < 0) {
        t = 0;
    } else if (t > 0x1000) {
        t = 0x1000;
    }
    t = t - 0x1000;
    t = FX_MulFunc(t, t);
    t = 0x1000 - t;
    w = -w;
    t = (t - 0x800) << 5;
    if (py < 0) {
        s = 0;
    } else if (py > 0xbf000) {
        s = 0xbf000;
    } else {
        s = py;
    }
    s = FX_Div(0xbf000 - s, 0xbf000);
    s = FX_MulFunc(t, s);
    py = py + s;
    out[0] = px + w;
    out[1] = py;
}

void func_020c013c(UnkStruct_020c013c *self)
{
    // DECLS
    int k;
    u32 g1c;
    u32 w;
    int *p0;
    u32 b1c;
    u32 q;
    int tb;
    u32 v;
    int i1;
    int t;
    int m;
    int q0;
    int a;
    u32 r1c;
    u32 b0c;
    u32 r0c;
    int q1;
    void *o;
    int *p1;
    int n;
    int bb;
    int idx;
    int q4;
    int i0;
    u32 g0c;
    int tg;
    int b;
    int q3;
    int q5;
    int rr;
    UnkStruct_020c013c_2 *e;
    int q2;
    int tr;
    int arg;
    int gg;
    int invT;
    // ENDDECLS
    u16 out[2];

    n = self->unk_64;
    if (n < 0x10) {
        t = 0;
    } else if (n < 0x1b) {
        t = ((n - 0x10) << 12) / 0xb;
    } else {
        t = 0x1000;
    }

    v = self->unk_60;
    idx = (int) ((v >> 8) & 3);
    a = func_020c03f4(idx, ((v >> 31) & 1) != 0);
    b = a + 1;

    i1 = i0 = 0;
    if (n >= 0xb) {
        m = n & 2;
        if (m == 0) {
            i0 = 1;
        }
        if (m != 0) {
            i1 = 1;
        } else {
            i1 = 0;
        }
    }
    p0 = &data_020d22d0[i0];
    p1 = &data_020d22d0[i1];

    if (idx >= 4) {
        return;
    }
    if (a >= 0xf) {
        return;
    }
    if (b >= 0xf) {
        return;
    }

    e = &data_020d2344[idx];
    invT = 0x1000 - t;

    tr = FX_MulFunc(R5(data_020d2344[idx].unk_00), invT);
    rr = tr + FX_MulFunc(R5(e->c1), t);
    tg = FX_MulFunc(G5(data_020d2344[idx].unk_00), invT);
    gg = tg + FX_MulFunc(G5(e->c1), t);
    tb = FX_MulFunc(B5(data_020d2344[idx].unk_00), invT);
    bb = tb + FX_MulFunc(B5(e->c1), t);

    q0 = FX_MulFunc(rr, *p0);
    q1 = FX_MulFunc(gg, *p0);
    q2 = FX_MulFunc(bb, *p0);
    q3 = FX_MulFunc(rr, *p1);
    q4 = FX_MulFunc(gg, *p1);
    q5 = FX_MulFunc(bb, *p1);

    g0c = (u32) ((q1 + 0x800) >> 12);
    b0c = (u32) ((q2 + 0x800) >> 12);
    r1c = (u32) ((q3 + 0x800) >> 12);
    g1c = (u32) ((q4 + 0x800) >> 12);
    b1c = (u32) ((q5 + 0x800) >> 12);
    r0c = (u32) ((q0 + 0x800) >> 12);

    if (r0c > 0x1f) {
        r0c = 0x1f;
    }
    if (g0c > 0x1f) {
        g0c = 0x1f;
    }
    if (b0c > 0x1f) {
        b0c = 0x1f;
    }
    if (r1c > 0x1f) {
        r1c = 0x1f;
    }
    if (g1c > 0x1f) {
        g1c = 0x1f;
    }
    if (b1c > 0x1f) {
        b1c = 0x1f;
    }

    out[0] = (u16) (r0c | (g0c << 5) | (b0c << 10));
    out[1] = (u16) (r1c | (g1c << 5) | (b1c << 10));

    k = self->unk_24;
    arg = self->unk_08;
    o = ((int *) data_021fba00);
    func_020bec14(o, a, &out[0]);
    func_020bec14(o, b, &out[1]);
    func_020bee4c(&data_021fa678[k], arg);
}

void func_020c00fc(struct UnkStruct_020c00fc *self)
{
    unsigned int flags;
    int y;
    int x;
    int z;
    int w;

    flags = self->flags;
    y = ((flags >> 31) & 1) != 0;
    x = (flags >> 8) & 3;
    z = func_020c03f4(x, y);
    w = z + 1;
    if (z < 15) {
        func_020bec54(data_021fba00, z);
    }
    if (w < 15) {
        func_020bec54(data_021fba00, w);
    }
}

int func_020c00f8(int p0, int p1)
{
    return (p1 << 14);
}

void func_020c0084(UnkStruct_020c0084 *self, int n)
{
    int lim;
    int *tbl;
    int a;
    unsigned int v;
    int val;

    v = self->unk_60;
    a = ((v >> 30) & 1) ? 1 : 0;
    if (((v >> 31) & 1) != 0) {
        if (a != 0) {
            tbl = data_020d274c;
            lim = 0xb0;
        } else {
            tbl = data_020d2444;
            lim = 0x24;
        }
    } else {
        if (a != 0) {
            tbl = data_020d27fc;
            lim = 0xb0;
        } else {
            tbl = data_020d2468;
            lim = 0x24;
        }
    }
    if (n < 0) {
        n = func_0208a1cc((char *) self + 0x10);
    }
    if (n < 0) {
        lim = 0;
    } else if (n <= lim) {
        lim = n;
    }
    val = tbl[lim];
    self->unk_4C = val;
    self->unk_50 = val;
}

void func_020c003c(UnkStruct_020c003c *self, int a)
{
    int kind;
    unsigned int ok;

    kind = (a & 0xf) + 0x1d;
    self->unk_0C = kind;
    self->unk_58 = 2;
    self->unk_60 = a;
    ok = 0;
    self->unk_64 = ok;
    self->unk_68 = ok;
    kind -= 0x21;
    if ((unsigned int) kind <= 9) {
        if (((1 << kind) & 0x249) != 0) {
            ok = 1;
        }
    }
    if (ok != 0) {
        func_020bff20((UnkStruct_020bff20 *) self, a);
    } else {
        func_020bffc4((struct UnkStruct_020bffc4 *) self, a);
    }
}

void func_020bffc4(struct UnkStruct_020bffc4 *obj, unsigned int b)
{
    int flag;
    int t;
    int r1, r2;

    if ((b >> 31) & 1) {
        flag = 1;
    } else {
        flag = 0;
    }

    func_020c0084((UnkStruct_020c0084 *) obj, 0);

    obj->unk_6C = obj->unk_34;
    obj->unk_70 = obj->unk_38;

    func_020c0324(&obj->unk_34, obj->unk_6C, obj->unk_70, flag);

    if (flag) {
        r2 = 0x804;
    } else {
        r2 = 0x803;
    }

    t = (b >> 8) & 3;

    if (flag) {
        r1 = 1;
    } else {
        r1 = t + 2;
    }

    func_020bf220(obj, r1, r2);

    if (flag) {
        obj->unk_5C = 4;
        func_02065268(t + 5);
    } else {
        func_02065268(t + 1);
    }
}

void func_020bff20(UnkStruct_020bff20 *self, unsigned int flags)
{
    int r4;
    unsigned int r7, r0;
    unsigned int r1;

    switch ((flags >> 31) & 1) {
        default:
            r4 = 1;
            break;
        case 0:
            r4 = 0;
            break;
    }

    if (r4) {
        r7 = func_020644cc(0x60) + 0x50;
        if (((flags >> 28) & 1) != 0) {
            r0 = 0;
        } else {
            r0 = func_020644cc(0x20);
        }
        r0 += 0x52;
    } else {
        r7 = func_020644cc(0xa0) + 0x30;
        r0 = func_020644cc(0x60) + 0x32;
    }

    self->unk_6C = r7 << 12;
    self->unk_70 = 0x000bf000;
    self->unk_3C = r0 << 12;

    func_020c0324((int *) ((char *) self + 0x34), self->unk_6C, self->unk_70, r4);

    self->unk_40 = 0;
    self->unk_44 = 0xffffc800;
    self->unk_48 = 0;
    self->unk_50 = 0x0000a000;

    r1 = (flags >> 8) & 3;
    if (r4) {
        r1 = 1;
    } else {
        r1 += 2;
    }
    func_020bf220((struct UnkStruct_020bffc4 *) self, r1, 0x802);
}

void func_020bfee4(void *p0)
{
    int v;
    int match;

    *(int *) ((char *) p0 + 0x64) += 1;
    v = *(int *) ((char *) p0 + 0xc);
    match = 0;
    v -= 0x21;
    if ((unsigned int) v <= 9) {
        if ((0x249 & (1 << v)) != 0) {
            match = 1;
        } else {
            match = 0;
        }
    }
    if (match != 0) {
        func_020bfd1c((UnkStruct_020bfd1c_2 *) p0);
    } else {
        func_020bfe6c((struct UnkStruct_020bfe6c *) p0);
    }
}

void func_020bfe6c(struct UnkStruct_020bfe6c *self)
{
    unsigned int flags = self->flags;
    int r4 = ((flags >> 30) & 1) ? 0 : 1;
    int r6 = ((flags >> 31) & 1) ? 1 : 0;

    if (func_0208a160(self->sub_10) != 0) {
        if (r4 != 0) {
            func_020c00fc((struct UnkStruct_020c00fc *) self);
        }
        self->unk_04 = 3;
    } else {
        func_020c0084((UnkStruct_020c0084 *) self, -1);
        func_020c0324((int *) self->unk_34, self->unk_6C, self->unk_70, r6);
        if (r4 != 0) {
            func_020c013c((UnkStruct_020c013c *) self);
        }
    }

    if (self->unk_64 == 0x1d) {
        self->flags |= data_020d2eec;
    }
}

void func_020bfd1c(UnkStruct_020bfd1c_2 *self)
{
    // DECLS
    int lim;
    u32 v;
    int flag;
    int trig;
    int d;
    u32 x;
    u32 a;
    int t;
    int tb;
    int ta;
    // ENDDECLS
    UnkStruct_020bfd1c w;

    v = self->unk_60;
    flag = ((v >> 31) & 1) != 0;
    trig = 0;
    if (self->unk_31 != 0) {
        self->unk_68 = self->unk_68 + 1;
        if (self->unk_68 > 6) {
            trig = 1;
        }
    } else {
        lim = 0xc0000 - self->unk_3C;
        d = func_020c00f8(lim, self->unk_64);
        if (d <= 0x20000) {
            self->unk_50 = FX_Div(0x20000, d);
            self->unk_70 = 0xc0000 - (d / 2);
        } else {
            if (d < lim) {
                self->unk_50 = 0x1000;
            } else {
                self->unk_50 = FX_MulFunc(self->unk_50, 0x14cd);
                if (self->unk_50 >= 0xa000) {
                    self->unk_50 = 0xa000;
                    self->unk_31 = 1;
                }
                d = lim;
            }
            self->unk_70 = 0xc0000 - (d - FX_Div(0x10000, self->unk_50));
        }
        func_020c0324((int *) (&self->unk_34), self->unk_6C, self->unk_70, flag);
    }
    if (trig != 0) {
        self->unk_04 = 3;
        x = (v >> 8) & 3;
        if (((self->unk_60 >> 31) & 1) != 0) {
            x = (x & 3) << 8;
            a = x | 0x80000000;
            x = x | 0xc0000001;
        } else {
            t = self->unk_0C;
            x = (x & 3) << 8;
            a = x | (u32) (((int) (t - 2) - 0x1d) & 0xf);
            x = x | (u32) ((((int) (t - 1) - 0x1d) & 0xf) | 0x40000000);
        }
        tb = self->unk_3C - 0x2000;
        ta = self->unk_6C;
        w.a = ta;
        w.b = tb;
        w.c = 0;
        func_020bdc50(&data_021f8b48, 9, 0x3c, &w, a);
        func_020bdc50(&data_021f8b48, 9, 0x3c, &w, x);
    }
}

void func_020bfcd8(void *self)
{
    unsigned int v;
    int flag;
    unsigned int mask;
    int cond;
    v = *((unsigned int *) (((char *) self) + 0xc));
    flag = 0;
    v -= 0x21;
    if (v <= 9) {
        mask = 1 << v;
        if (mask & 0x249) {
            flag = 1;
        }
        cond = ((*((unsigned int *) (((char *) self) + 0x60))) >> 0x1e) & 1;
    }
    if (!flag) {
        cond = ((*((unsigned int *) (((char *) self) + 0x60))) >> 0x1e) & 1;
        if (!cond) {
            func_020c00fc((struct UnkStruct_020c00fc *) self);
        }
    }
    func_020bf590(self);
}
