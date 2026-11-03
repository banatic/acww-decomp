/* field_actor_rooms: 37 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02226a80 @ 0x02226a80, 0x2c bytes, Thumb
 * func_ov004_022269a8 @ 0x022269a8, 0xd8 bytes, Thumb
 * func_ov004_02226920 @ 0x02226920, 0x88 bytes, Thumb
 * func_ov004_022268b8 @ 0x022268b8, 0x68 bytes, Thumb
 * func_ov004_02226890 @ 0x02226890, 0x26 bytes, Thumb
 * func_ov004_0222687c @ 0x0222687c, 0x12 bytes, Thumb
 * func_ov004_0222683c @ 0x0222683c, 0x40 bytes, Thumb
 * func_ov004_02226818 @ 0x02226818, 0x24 bytes, Thumb
 * func_ov004_02226810 @ 0x02226810, 0x8 bytes, Thumb
 * func_ov004_02226808 @ 0x02226808, 0x8 bytes, Thumb
 * func_ov004_0222671c @ 0x0222671c, 0xec bytes, Thumb
 * func_ov004_022266f0 @ 0x022266f0, 0x2c bytes, Thumb
 * func_ov004_022266c4 @ 0x022266c4, 0x2c bytes, Thumb
 * func_ov004_02226630 @ 0x02226630, 0x94 bytes, Thumb
 * func_ov004_0222661c @ 0x0222661c, 0x12 bytes, Thumb
 * func_ov004_022265dc @ 0x022265dc, 0x40 bytes, Thumb
 * func_ov004_022265c0 @ 0x022265c0, 0x1a bytes, Thumb
 * func_ov004_022265b8 @ 0x022265b8, 0x8 bytes, Thumb
 * func_ov004_022265b0 @ 0x022265b0, 0x8 bytes, Thumb
 * func_ov004_0222654c @ 0x0222654c, 0x64 bytes, Thumb
 * func_ov004_022264f4 @ 0x022264f4, 0x58 bytes, Thumb
 * func_ov004_022264c8 @ 0x022264c8, 0x2c bytes, Thumb
 * func_ov004_022264a8 @ 0x022264a8, 0x20 bytes, Thumb
 * func_ov004_02226494 @ 0x02226494, 0x12 bytes, Thumb
 * func_ov004_02226454 @ 0x02226454, 0x40 bytes, Thumb
 * func_ov004_0222643c @ 0x0222643c, 0x18 bytes, Thumb
 * func_ov004_02226434 @ 0x02226434, 0x8 bytes, Thumb
 * func_ov004_0222642c @ 0x0222642c, 0x8 bytes, Thumb
 * func_ov004_0222631c @ 0x0222631c, 0x110 bytes, Thumb
 * func_ov004_022262f0 @ 0x022262f0, 0x2c bytes, Thumb
 * func_ov004_022262c4 @ 0x022262c4, 0x2c bytes, Thumb
 * func_ov004_0222629c @ 0x0222629c, 0x26 bytes, Thumb
 * func_ov004_0222626c @ 0x0222626c, 0x30 bytes, Thumb
 * func_ov004_02225fb8 @ 0x02225fb8, 0x2b4 bytes, Thumb
 * func_ov004_02225f70 @ 0x02225f70, 0x48 bytes, Thumb
 * func_ov004_02225ef8 @ 0x02225ef8, 0x78 bytes, Thumb
 * func_ov004_02225de0 @ 0x02225de0, 0x118 bytes, Thumb
 */

#include "types.h"

#define BYTE(p, o) (*(u8 *) ((p) + (o)))
#define WORD(p, o) (*(int *) ((p) + (o)))
#define VEC(p, o) ((Vec *) ((p) + (o)))

typedef struct {
    int a, b, c;
} UnkStruct_02226a80;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_022269a8 {
    int unk_00, unk_04, unk_08, unk_0C, unk_10;
    unsigned char unk_14;
    unsigned char unk_15;
} UnkStruct_022269a8;

typedef struct UnkStruct_022269a8_2 UnkStruct_022269a8_2;

typedef struct {
    int a, b, c;
} UnkStruct_0222687c;

typedef struct {
    char a[0xc];
    char b[0x10];
} UnkStruct_0222683c;

typedef struct {
    int x, y, z;
} UnkStruct_0222683c_2;

typedef struct {
    int a, b, c;
} Triple;

struct UnkStruct_0222671c {
    int a;
    int b;
    int c;
};

typedef struct {
    int a, b, c;
} UnkStruct_022266f0;

typedef struct {
    int a, b, c;
} UnkStruct_0222661c;

typedef struct {
    char a[0xc];
    char b[0x10];
} UnkStruct_022265dc;

typedef struct {
    int x, y, z;
} UnkStruct_022265dc_2;

struct UnkStruct_0222654c {
    int a;
    int b;
    int c;
};

struct UnkStruct_022264f4 {
    int x;
    int y;
    int z;
};

typedef struct {
    int a, b, c;
} UnkStruct_02226494;

typedef struct {
    char a[0xc];
    char b[0x10];
} UnkStruct_02226454;

typedef struct {
    int x, y, z;
} UnkStruct_02226454_2;

typedef struct {
    int a, b, c;
} BIG3;

struct UnkStruct_0222631c {
    int a;
    int b;
    int c;
};

typedef struct {
    int a, b, c;
} UnkStruct_022262f0;

typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    int x, z;
} Pair;

typedef struct {
    int x, y, z;
} UnkStruct_02225de0;

extern void func_ov004_02226bf8(void *p, UnkStruct_02226a80 *v, int *w);
extern int func_ov004_02226c2c(void *self, UnkStruct_02226a80 *v, int k, int arg);
extern void *data_020ccf94;
extern char data_ov004_02254af0;
extern char data_ov004_02254ae4;
extern int func_02073908(void *g, int k);
extern void func_020b220c(void);
extern void func_0201107c(UnkStruct_022269a8_2 *self, char *p);
extern int FX_MulFunc(int a, int b);
extern void func_020109c8(void *self, int a, int b, int c);
extern void func_02054860(void *p);
extern void func_0200f95c(void *self);
extern int func_02008258(void *self, int a);
extern int func_0200d4e8(void *self, int a, int b, int c);
extern void func_0200f268(void *self, int k);
extern int func_0203e110(void);
extern int func_02010ff4(void *);
extern void func_02010d64(void *);
extern unsigned int func_0200e92c(UnkStruct_0222683c *t);
extern void func_0200e90c(UnkStruct_0222683c *t, int x, int y, int z);
extern int func_0200e894(void *self, UnkStruct_0222683c *t);
extern int func_0200e91c(UnkStruct_0222683c *t);
extern void func_020779b8(unsigned char *parameter0, int parameter1, int parameter2);
extern void func_02077978(void *parameter0, unsigned int *parameter1, int parameter2);
extern void func_020109fc(void *self, int a, int b, int c);
extern int func_020b22a0(void);
extern int func_020b5e10(void);
extern int func_020b6098(int a, int b);
extern int func_0200f328(void *self, int msg);
extern int func_02064558(short a);
extern void VEC_Add(struct UnkStruct_0222631c *dst, struct UnkStruct_0222631c *a, struct UnkStruct_0222631c *b);
extern void func_01ffd070(struct UnkStruct_0222631c *out, struct UnkStruct_0222631c *a, struct UnkStruct_0222631c *b);
extern unsigned int *func_0200f27c(void *self, int a);
extern int data_ov004_02254ae8;
extern void *data_021c80bc;
extern int data_ov004_02247780;
extern int data_ov004_02254aec;
extern int func_020b67d4(void);
extern int func_ov004_0223bbc0(int *, int *, u16 *, u16 *);
extern int func_ov004_0223bb88(unsigned);
extern int func_0200bdbc(char *, Pair *, int, int, short);
extern int func_ov004_0222ac24(char *, Pair *, int, int, short);
extern void func_0200fa1c(Vec *, char *, Vec *, u16 *, int *);
extern int func_0201005c(char *, Vec *, int);
extern u16 *func_0204f5a8(void *, Vec *, u8);
extern int func_02099fe8(void);
extern int func_0204bd08(u16 *);
extern void func_0204f818(int *, int *, Vec *);
extern unsigned func_020b2300(void);
extern int func_0200ff28(char *, Vec *, int, int);
extern int func_0200fd04(char *, Vec *, int);
extern void func_02073770(void *a, unsigned int b, unsigned int c);
extern void func_020737f0(void *argument0, int argument1, int argument2);
extern void func_02073820(void *argument0);
extern int func_02073d90(void *argument0);
extern void func_0209645c(unsigned char *out, unsigned int a, unsigned int b);
extern void *func_ov004_0223cb10(void);
extern void *func_ov004_0223cadc(void *a, int b);
extern int *func_ov004_0223cb24(void *h);
extern int func_ov004_0223cb18(void *h);
extern int func_ov004_0222a494(void *self, int a, int b, int c, int d, int e);
extern int func_0200fbe0(void *self);
extern int func_02010004(void *self, int a);
extern int func_020ea9c8(UnkStruct_02225de0 *d);
extern void func_020114b0(void *dst, int a, int b, int c, int d);
extern int func_020ea990(void *a, void *b);
extern int func_02011398(int a, int b);
extern int func_020113b0(int a, int b);
extern int func_020e8ed8(int dx, int dz);
extern int func_020113e0(short *a, int b);
extern void func_020110a0(void *object, short *values);
extern short FX_SinCosTable_[];

void func_ov004_02225de0(char *self, UnkStruct_02225de0 *p1, int *out, int *p3);

void func_ov004_02226a80(void *self, int arg)
{
    UnkStruct_02226a80 v;
    func_ov004_02226bf8((char *) self + 0x8f0, &v, &v.c);
    func_ov004_02226c2c(self, &v, 6, arg);
}

void func_ov004_022269a8(UnkStruct_022269a8_2 *self)
{
    int a;
    Vec3 v;
    UnkStruct_022269a8 *s;
    unsigned char *p;

    s = (UnkStruct_022269a8 *) ((char *) self + 0x7d4);
    p = &s->unk_14;
    if (*p != 0) {
        *p = (unsigned char) (*p - 1);
        if (s->unk_15 == 2) {
            if (*p != 0) {
                return;
            }
            if (func_02073908(data_020ccf94, *(int *) ((char *) self + 0x800)) == 0) {
                func_020b220c();
                func_0200f328((void *) self, 0x4cb);
            }
            *(int *) ((char *) self + 0x7f8) = 1;
            func_0201107c(self, &data_ov004_02254af0);
            s->unk_0C = 0x400;
        } else {
            if (*p > 0xa) {
                return;
            }
            if (*p == 0xa) {
                *(int *) ((char *) self + 0x7f8) = 1;
                func_0201107c(self, &data_ov004_02254ae4);
                s->unk_0C = 0x400;
            } else if (*p == 0) {
                if (func_02073908(data_020ccf94, *(int *) ((char *) self + 0x800)) == 0) {
                    func_0200f328((void *) self, 0x4d3);
                }
            }
        }
    }
    a = s->unk_10;
    v.x = s->unk_00;
    v.y = s->unk_04;
    v.z = s->unk_08;
    func_ov004_02225de0((char *) self, (UnkStruct_02225de0 *) (&v), &s->unk_0C, &a);
}

void func_ov004_02226920(char *self)
{
    int v;
    int n;

    v = *(int *) (self + 0x98);
    n = FX_MulFunc(v, 0x3ae1);
    if (n < 0x800) {
        n = 0x800;
    }
    if (n <= *(int *) (self + 0x2d4)) {
        *(int *) (self + 0x2e0) = n;
    }
    if (v > 0x53f) {
        if (*(int *) (self + 0x704) != 2) {
            func_020109c8(self, 2, 3, 0);
        }
    } else {
        if (*(int *) (self + 0x704) != 1) {
            func_020109c8(self, 1, 3, 0);
        }
    }
    func_02054860(self + 0x234);
    func_0200f95c(self);
}

void func_ov004_022268b8(void *self)
{
    if (*(int *) ((char *) self + 0x98) == 0 && *(int *) ((char *) self + 0x7f8) == 1) {
        *(int *) ((char *) self + 0x7fc) = func_02008258(self, *(int *) ((char *) self + 0x7f0));
        func_0200d4e8(self, 3, 5, -1);
        func_0200f268(self, 5);
        if (func_02073908(data_020ccf94, *(int *) ((char *) self + 0x800)) != 0) {
            func_0203e110();
        }
    }
}

void func_ov004_02226890(void *p)
{
    func_ov004_022269a8((UnkStruct_022269a8_2 *) p);
    func_ov004_02226920((char *) p);
    func_02010ff4(p);
    func_02010d64(p);
    func_ov004_022268b8(p);
}

void func_ov004_0222687c(int *d, UnkStruct_0222687c v)
{
    d[0] = v.a;
    d[1] = v.b;
    d[2] = v.c;
}

int func_ov004_0222683c(void *self, UnkStruct_0222683c_2 *v, int c, int d)
{
    UnkStruct_0222683c t;
    int r;
    func_0200e92c(&t);
    func_0200e90c(&t, 0x8c, c, d);
    func_ov004_0222687c((int *) t.b, *(UnkStruct_0222687c *) &(*v));
    r = func_0200e894(self, &t);
    func_0200e91c(&t);
    return r;
}

void func_ov004_02226818(char *self, Triple v, int setting, int extent, u8 f)
{
    *(int *) (self) = v.a;
    *(int *) (self + 4) = v.b;
    *(int *) (self + 8) = v.c;
    *(int *) (self + 0xc) = setting;
    *(int *) (self + 0x10) = extent;
    *(u8 *) (self + 0x14) = 0;
    *(u8 *) (self + 0x15) = f;
}

void func_ov004_02226810(unsigned char *arg0, int arg1, int arg2)
{
    func_020779b8((unsigned char *) arg0, arg1, arg2);
}

void func_ov004_02226808(void *arg0, unsigned int *arg1, int arg2)
{
    func_02077978((void *) arg0, (unsigned int *) arg1, arg2);
}

void func_ov004_0222671c(unsigned char *self, unsigned char *p, int previous)
{
    struct UnkStruct_0222671c *q;
    struct UnkStruct_0222671c v;
    int msg, r;
    q = (struct UnkStruct_0222671c *) (p + 0xc);
    if (*(int *) (self + 0x704) != 1) {
        func_020109fc(self, 1, 3, 0);
    }
    msg = 0;
    r = func_020b22a0();
    switch (r) {
        case 2:
            msg = 0x4cb;
            break;
        case 1:
            msg = 0x4d2;
            break;
        case 0:
        case 3:
            if (func_02073908((void *) ((*(int *) &data_020ccf94)), *(int *) (self + 0x800)) != 0) {
                func_020b6098(func_020b5e10(), *(int *) (self + 0x804));
            }
            break;
    }
    if (msg != 0) {
        if (func_02073908((void *) ((*(int *) &data_020ccf94)), *(int *) (self + 0x800)) == 0) {
            func_0200f328(self, msg);
            if (msg == 0x4cb) {
                func_020b220c();
            }
        }
    }
    v.a = q->a;
    v.b = q->b;
    v.c = q->c;
    func_ov004_02226818((char *) (self + 0x7d4), *(Triple *) &v, *(int *) (self + 0x98), 0x400, (unsigned char) ((unsigned char) r));
    func_ov004_02226810((unsigned char *) (self + 0x8f0), v.a, v.c);
}

void func_ov004_022266f0(void *self, int arg)
{
    UnkStruct_022266f0 v;
    func_ov004_02226808((char *) self + 0x8f0, (unsigned int *) (&v), (int) (&v.c));
    func_ov004_0222683c(self, (UnkStruct_0222683c_2 *) (&v), 6, arg);
}

void func_ov004_022266c4(void *self)
{
    int t0, t[3];
    int *p = (int *) ((char *) self + 0x7d4);
    t0 = p[4];
    t[0] = p[0];
    t[1] = p[1];
    t[2] = p[2];
    func_ov004_02225de0((char *) self, (UnkStruct_02225de0 *) t, p + 3, &t0);
}

void func_ov004_02226630(char *self)
{
    unsigned char *q;
    unsigned char *p;
    unsigned int m;
    char *g;

    func_ov004_022266c4(self);
    func_ov004_02226920((char *) self);
    func_02010ff4(self);
    func_02010d64(self);
    q = (unsigned char *) (self + 0x7d4);
    p = q + 0x14;
    m = q[0x15];
    g = (*(char * *) &data_020ccf94);
    if (func_02073908((void *) g, *(int *) (self + 0x800)) == 0 && *p == 0xf && m == 1) {
        func_0200f328(self, 0x4d3);
    }
    if (func_02073908((void *) g, *(int *) (self + 0x800)) != 0 && m - 1 <= 1 && *p == 0xa) {
        func_020b6098(func_020b5e10(), *(int *) (self + 0x804));
    }
    *p = *p + 1;
}

void func_ov004_0222661c(int *d, UnkStruct_0222661c v)
{
    d[0] = v.a;
    d[1] = v.b;
    d[2] = v.c;
}

int func_ov004_022265dc(void *self, UnkStruct_022265dc_2 *v, int c, int d)
{
    UnkStruct_022265dc t;
    int r;
    func_0200e92c((UnkStruct_0222683c *) (&t));
    func_0200e90c((UnkStruct_0222683c *) (&t), 0x8d, c, d);
    func_ov004_0222661c((int *) t.b, *(UnkStruct_0222661c *) &(*v));
    r = func_0200e894(self, (UnkStruct_0222683c *) (&t));
    func_0200e91c((UnkStruct_0222683c *) (&t));
    return r;
}

void func_ov004_022265c0(int *self, Triple v, int setting, int extent)
{
    self[0] = v.a;
    self[1] = v.b;
    self[2] = v.c;
    self[3] = setting;
    self[4] = extent;
}

void func_ov004_022265b8(unsigned char *arg0, int arg1, int arg2)
{
    func_020779b8((unsigned char *) arg0, arg1, arg2);
}

void func_ov004_022265b0(void *arg0, unsigned int *arg1, int arg2)
{
    func_02077978((void *) arg0, (unsigned int *) arg1, arg2);
}

void func_ov004_0222654c(unsigned char *self, unsigned char *p, int previous)
{
    struct UnkStruct_0222654c *q;
    struct UnkStruct_0222654c v;
    q = (struct UnkStruct_0222654c *) (p + 0xc);
    if (*(int *) (self + 0x704) != 1) {
        func_020109fc(self, 1, 3, 0);
    }
    v.a = q->a;
    v.b = q->b;
    v.c = q->c;
    func_ov004_022265c0((int *) (self + 0x7d4), *(Triple *) &v, *(int *) (self + 0x98), 0x400);
    func_ov004_022265b8((unsigned char *) (self + 0x8f0), v.a, v.c);
}

void func_ov004_022264f4(char *self, int arg)
{
    struct UnkStruct_022264f4 p;

    func_ov004_022265b0(self + 0x8f0, (unsigned int *) (&p.x), (int) (&p.z));
    if ((p.x & 0x80000) != 0) {
        p.x |= 0xfff00000;
    }
    if ((p.z & 0x80000) != 0) {
        p.z |= 0xfff00000;
    }
    func_ov004_022265dc(self, (UnkStruct_022265dc_2 *) (&p), 6, arg);
}

void func_ov004_022264c8(void *self)
{
    int t0, t[3];
    int *p = (int *) ((char *) self + 0x7d4);
    t0 = p[4];
    t[0] = p[0];
    t[1] = p[1];
    t[2] = p[2];
    func_ov004_02225de0((char *) self, (UnkStruct_02225de0 *) t, p + 3, &t0);
}

void func_ov004_022264a8(int arg)
{
    func_ov004_022264c8((void *) arg);
    func_ov004_02226920((char *) arg);
    func_02010ff4((void *) arg);
    func_02010d64((void *) arg);
}

void func_ov004_02226494(int *d, UnkStruct_02226494 v)
{
    d[0] = v.a;
    d[1] = v.b;
    d[2] = v.c;
}

int func_ov004_02226454(void *self, UnkStruct_02226454_2 *v, int c, int d)
{
    UnkStruct_02226454 t;
    int r;
    func_0200e92c((UnkStruct_0222683c *) (&t));
    func_0200e90c((UnkStruct_0222683c *) (&t), 0x8e, c, d);
    func_ov004_02226494((int *) t.b, *(UnkStruct_02226494 *) &(*v));
    r = func_0200e894(self, (UnkStruct_0222683c *) (&t));
    func_0200e91c((UnkStruct_0222683c *) (&t));
    return r;
}

void func_ov004_0222643c(int *self, BIG3 v, int d)
{
    self[0] = v.a;
    self[1] = v.b;
    self[2] = v.c;
    self[3] = d;
    self[4] = d;
}

void func_ov004_02226434(unsigned char *arg0, int arg1, int arg2)
{
    func_020779b8((unsigned char *) arg0, arg1, arg2);
}

void func_ov004_0222642c(void *arg0, unsigned int *arg1, int arg2)
{
    func_02077978((void *) arg0, (unsigned int *) arg1, arg2);
}

void func_ov004_0222631c(unsigned char *self, unsigned char *p, int previous)
{
    struct UnkStruct_0222631c *q, *s;
    struct UnkStruct_0222631c t, v, out;
    unsigned char *w, *w2;

    q = (struct UnkStruct_0222631c *) (p + 0xc);
    w = self + 0x7d4;
    func_020109fc(self, 1, 0, 0);
    *(int *) (self + 0x2e0) = 0;
    v.a = 0;
    v.b = 0;
    v.c = 0;
    w2 = self + 0x8f0;
    switch (func_02064558(*(short *) (self + 0x8e))) {
        case 2:
            v.c = v.c + 0x6000;
            break;
        case 0:
            v.c = v.c - 0x6000;
            break;
        case 3:
            v.a = v.a + 0x6000;
            break;
        case 1:
            v.a = v.a - 0x6000;
            break;
    }
    if (func_02073908((void *) ((*(int *) &data_020ccf94)), *(int *) (self + 0x800)) != 0) {
        s = (struct UnkStruct_0222631c *) (self + 0x5c);
        t.a = s->a;
        t.b = s->b;
        t.c = s->c;
        func_ov004_02226434((unsigned char *) w2, t.a, t.c);
        VEC_Add((struct UnkStruct_0222631c *) (self + 0x5c), &v, (struct UnkStruct_0222631c *) (self + 0x5c));
    } else {
        t.a = q->a;
        t.b = q->b;
        t.c = q->c;
        func_01ffd070(&out, &t, &v);
        s = (struct UnkStruct_0222631c *) (self + 0x5c);
        s->a = out.a;
        s->b = out.b;
        s->c = out.c;
    }
    func_ov004_0222643c((int *) w, *(BIG3 *) &t, 0x400);
    func_0201107c((UnkStruct_022269a8_2 *) self, (char *) (&data_ov004_02254ae8));
    func_0200f27c(self, 5);
}

void func_ov004_022262f0(void *self, int arg)
{
    UnkStruct_022262f0 v;
    func_ov004_0222642c((char *) self + 0x8f0, (unsigned int *) (&v), (int) (&v.c));
    func_ov004_02226454(self, (UnkStruct_02226454_2 *) (&v), 6, arg);
}

void func_ov004_022262c4(void *self)
{
    int t0, t[3];
    int *p = (int *) ((char *) self + 0x7d4);
    t0 = p[4];
    t[0] = p[0];
    t[1] = p[1];
    t[2] = p[2];
    func_ov004_02225de0((char *) self, (UnkStruct_02225de0 *) t, p + 3, &t0);
}

void func_ov004_0222629c(void *p)
{
    func_ov004_022262c4(p);
    func_ov004_02226920((char *) p);
    func_02010ff4(p);
    func_02010d64(p);
    func_ov004_022268b8(p);
}

void func_ov004_0222626c(u8 *self, unsigned int t, unsigned int step)
{
    u8 *p = self + 0x8e9;
    if (*p == t) {
        return;
    }
    if (*p < t) {
        *p = (u8) (*p + step);
        if (*p > t) {
            *p = (u8) t;
        }
    } else {
        *p = (u8) (*p - step);
        if (*(signed char *) p < (int) t) {
            *p = (u8) t;
        }
    }
}

static inline void copyvec(Vec *out, const Vec *in)
{
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;
}

int func_ov004_02225fb8(char *self, int action, int mode)
{
    int x = 0, z = 0, cx, cz;
    Pair p0, p1, p2, p3, p4, p5;
    Vec position, val, val2;
    int candidate;
    void *grid;
    u16 *tile;
    if (!func_020b67d4()) {
        goto fail;
    }
    if (WORD(self, 0x800)) {
        goto fail;
    }
    candidate = func_ov004_0223bbc0(&cx, &cz, (u16 *) (self + 0x820), (u16 *) (self + 0x822));
    if (candidate >= 0 && (candidate == BYTE(self, 0x16d) || WORD(self, 0x170) == 1)) {
        if (!func_ov004_0223bb88(candidate)) {
            p0.x = 0;
            p0.z = 0;
            func_0200bdbc(self, &p0, candidate, 6, -1);
        } else {
            p1.x = (u8) cx;
            p1.z = (u8) cz;
            func_ov004_0222ac24(self, &p1, candidate, 6, -1);
        }
        return 1;
    }
    grid = data_021c80bc;
    if (candidate == -2) {
        if (WORD(self, 0x170) == 1) {
            func_0200fa1c(&val, self, VEC(self, 0x5c), (u16 *) (self + 0x8e), &data_ov004_02247780);
            copyvec(&position, &val);
        } else {
            position.x = WORD(self, 0x158);
            position.y = WORD(self, 0x15c);
            position.z = WORD(self, 0x160);
            if (!func_0201005c(self, &position, 14)) {
                goto fallback;
            }
        }
        tile = func_0204f5a8(grid, &position, 1);
        if (func_02099fe8() == -1) {
            if (tile && func_0204bd08(tile)) {
                func_0204f818(&x, &z, &position);
                p2.x = x;
                p2.z = z;
                func_0200bdbc(self, &p2, -1, 6, -1);
                return 1;
            }
        } else if (tile && func_0204bd08(tile)) {
            if (func_020b2300() <= 1) {
                if (func_0200ff28(self, &position, 0, action) && func_0200fd04(self, &position, 1)) {
                    return 1;
                }
            } else {
                func_0204f818(&x, &z, &position);
                p3.x = x;
                p3.z = z;
                func_0200bdbc(self, &p3, -3, 6, -1);
                return 1;
            }
        }
    }
fallback:
    if (WORD(self, 0x170) == 1) {
        func_0200fa1c(&val2, self, VEC(self, 0x5c), (u16 *) (self + 0x8e), &data_ov004_02254aec);
        copyvec(&position, &val2);
    } else {
        position.x = WORD(self, 0x158);
        position.y = WORD(self, 0x15c);
        position.z = WORD(self, 0x160);
        if (!func_0201005c(self, &position, 12)) {
            return 0;
        }
    }
    tile = func_0204f5a8(grid, &position, 0);
    if (tile && func_0204bd08(tile)) {
        if (func_02099fe8() == -1) {
            func_0204f818(&x, &z, &position);
            p4.x = x;
            p4.z = z;
            func_0200bdbc(self, &p4, -1, 6, -1);
            return 1;
        } else {
            if (func_020b2300() <= 1) {
                if (func_0200ff28(self, &position, 0, action) && func_0200fd04(self, &position, 0)) {
                    return 1;
                }
            } else {
                func_0204f818(&x, &z, &position);
                p5.x = x;
                p5.z = z;
                func_0200bdbc(self, &p5, -3, 6, -1);
                return 1;
            }
        }
    }
fail:
    return 0;
}

void func_ov004_02225f70(char *self, unsigned int a1, unsigned int a2)
{
    // DECLS
    int v2;
    int v4;
    unsigned char frame[0x4];
    // ENDDECLS
    v2 = func_02073d90((void *) ((void *) (*(int *) ((char *) &data_020ccf94))));
    if (v2 != 0x0) {
        func_0209645c(frame, a1, a2);
        v4 = *(int *) ((char *) &data_020ccf94);
        func_02073820((void *) (v4));
        func_020737f0((void *) (v4), (int) (frame), (int) (0x1));
        func_02073770((void *) (v4), (unsigned int) (0x2c), (unsigned int) (0x4));
    }
}

int func_ov004_02225ef8(char *self)
{
    volatile int v[3];
    void *h;
    int *p;

    if (*(unsigned char *) (self + 0x141) != 0) {
        h = func_ov004_0223cadc(func_ov004_0223cb10(), 0);
        if (h == 0) {
            return 0;
        }
        p = func_ov004_0223cb24(h);
        v[0] = p[0];
        v[1] = p[1];
        v[2] = p[2];
        return func_ov004_0222a494(self, v[0], v[2], func_ov004_0223cb18(h), 5, -1);
    }
    if (*(unsigned char *) (self + 0x148) != 0) {
        return func_02010004(self, func_0200fbe0(self));
    }
    return 0;
}

void func_ov004_02225de0(char *self, UnkStruct_02225de0 *p1, int *out, int *p3)
{
    int r;
    int ang;
    UnkStruct_02225de0 d;
    int idx;
    short prevAngle;
    UnkStruct_02225de0 saved;
    short diffS;

    {
        int *p = (int *) (self + 0x5c);
        saved.x = p[0];
        saved.y = p[1];
        saved.z = p[2];
    }

    d.x = p1->x - *(int *) (self + 0x5c);
    d.z = p1->z - *(int *) (self + 0x64);

    if (func_020ea9c8(&d) < 0x1000) {
        if (*out <= *p3) {
            func_020114b0(self + 0x5c, p1->x, 0x800, *p3, 0x31);
            func_020114b0(self + 0x64, p1->z, 0x800, *p3, 0x31);
            if (p1->x == *(int *) (self + 0x5c) && p1->z == *(int *) (self + 0x64)) {
                *out = 0;
            } else {
                *out = func_020ea990(self + 0x5c, &saved);
                {
                    int *p = (int *) (self + 0x5c);
                    p[0] = saved.x;
                    p[1] = saved.y;
                    p[2] = saved.z;
                }
            }
        } else {
            *out = func_02011398(*out, *p3);
        }
    } else {
        *out = func_020113b0(*out, *p3);
    }

    ang = func_020e8ed8(d.x, d.z);
    prevAngle = *(short *) (self + 0x8e);
    if (*out != 0) {
        func_020113e0(&prevAngle, ang);
        func_020110a0(self, (short *) (&prevAngle));
    }
    diffS = prevAngle - ang;
    idx = (unsigned short) diffS >> 4;
    {
        int t = FX_MulFunc(*out, FX_SinCosTable_[idx * 2 + 1]);
        r = (t < 0) ? -t : t;
    }
    func_0201107c((UnkStruct_022269a8_2 *) self, (char *) (&r));
}
