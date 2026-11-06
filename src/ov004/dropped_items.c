/* dropped_items: 11 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02233ad4 @ 0x02233ad4, 0x3c bytes, Thumb
 * func_ov004_02233aa4 @ 0x02233aa4, 0x2e bytes, Thumb
 * func_ov004_02233a00 @ 0x02233a00, 0xa4 bytes, Thumb
 * func_ov004_022339e0 @ 0x022339e0, 0x20 bytes, Thumb
 * func_ov004_02233918 @ 0x02233918, 0xc8 bytes, Thumb
 * func_ov004_0223383c @ 0x0223383c, 0xdc bytes, Thumb
 * func_ov004_0223380c @ 0x0223380c, 0x30 bytes, Thumb
 * func_ov004_022337ac @ 0x022337ac, 0x60 bytes, Thumb
 * func_ov004_022336f0 @ 0x022336f0, 0xbc bytes, Thumb
 * func_ov004_022336c4 @ 0x022336c4, 0x2c bytes, Thumb
 * func_ov004_0223362c @ 0x0223362c, 0x98 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int a, b;
} UnkStruct_02233a00;

struct UnkStruct_022339e0 {
    int unk_00;
    int unk_04;
    unsigned short unk_08;
    unsigned short unk_0A;
    int unk_0C;
};

typedef struct UnkStruct_0223383c {
    char unk_00[0xa];
    unsigned short unk_0A;
    char unk_0C[0x1c - 0xc];
    int unk_1C;
    char unk_20[8];
    int unk_28;
    char unk_2C[4];
    int unk_30, unk_34, unk_38, unk_3C;
    char unk_40[4];
    int unk_44;
    char unk_48[0x8c - 0x48];
    signed char unk_8C;
} UnkStruct_0223383c;

typedef struct Rec {
    int unk_00;
    int unk_04;
    unsigned short unk_08;
    unsigned short unk_0A;
    int unk_0C;
    unsigned char pad_10[0x14];
    int unk_24;
    int unk_28;
    int unk_2C;
    unsigned char pad_30[0x1c];
    unsigned char unk_4C[0x41];
    unsigned char unk_8D;
    unsigned char pad_8E[6];
} Rec;

typedef struct {
    int a, b;
} UnkStruct_0223362c;

typedef struct {
    int a, b, c;
} UnkStruct_0223362c_2;

typedef struct {
    int unk_00;
    int unk_04;
    char pad_08[0x94 - 8];
} Elem;

extern int func_020b6660(void);
extern int func_0204f538(void *, unsigned short *, int, int, int);
extern void *data_021c80bc;
extern void func_02045f08(void *, int);
extern void func_0204f794(void *, int, int);
extern int _s32_div_f(int, int);
extern int func_020044c0(void *, int, int, int);
extern void VEC_Add(char *d, char *a, char *b);
extern void func_0200451c(void *p);
extern void func_020044d0(void *self, const Vec3 *v);
extern int func_0203f8d0(Vec3 *, void *);
extern void func_020e96c8(void *, int, int, int);
extern void func_020e9774(void *, int);
extern void func_020e9838(void *, int, int, int);
extern void func_ov004_02233dc0(void *, u16, Vec3 *, Vec3 *, short, short, short);
extern char data_021fbe48;
extern void *data_ov004_02258ae4;
extern int func_020044a0(void *);

void func_ov004_02233918(char *self, int *p1, Vec3 *p2, Vec3 *p3, u16 a5);

void func_ov004_02233ad4(int a0, int a1, unsigned short a2, int a3)
{
    void *g;
    func_020b6660();
    g = data_021c80bc;
    if (g != 0) {
        volatile unsigned short t = 0xfff1;
        t = a2;
        func_0204f538(g, (unsigned short *) &t, a0, a1, a3);
    }
}

void func_ov004_02233aa4(char *self)
{
    int t[2];
    if (*(u8 *) (self + 0x8f) != 0) {
        *(u8 *) (self + 0x8f) = 0;
        t[0] = *(int *) (self + 0x10);
        t[1] = *(int *) (self + 0x14);
        func_02045f08(t, *(u8 *) (self + 0x90));
    }
}

void func_ov004_02233a00(char *self, int a, UnkStruct_02233a00 *b, Vec3 *c, Vec3 *d, int e, u16 f7, int a8, short a9, u8 a10)
{
    char *q;
    UnkStruct_02233a00 bb;
    Vec3 cc, dd;
    *(int *) self = a;
    *(int *) (self + 4) = 1;
    *(int *) (self + 0xc) = e;
    *(int *) (self + 0x10) = b->a;
    *(int *) (self + 0x14) = b->b;
    *(int *) (self + 0x18) = d->x;
    *(int *) (self + 0x1c) = d->y;
    *(int *) (self + 0x20) = d->z;
    *(short *) (self + 0x48) = a9;
    *(short *) (self + 0x4a) = 0;
    *(u8 *) (self + 0x8e) = 1;
    *(u8 *) (self + 0x8f) = 1;
    q = self;
    q += 0x90;
    *q = (char) a10;
    *(u8 *) (self + 0x8d) = 0;
    *(u8 *) (self + 0x8c) = 0;
    if (e == 0) {
        cc.x = c->x;
        cc.y = c->y;
        cc.z = c->z;
        dd.x = d->x;
        dd.y = d->y;
        dd.z = d->z;
        bb.a = b->a;
        bb.b = b->b;
        func_ov004_02233918((char *) self, (int *) (&bb), &cc, &dd, f7);
    }
}

void func_ov004_022339e0(struct UnkStruct_022339e0 *p)
{
    func_ov004_02233aa4((char *) p);
    p->unk_04 = 0;
    p->unk_0C = 1;
    p->unk_08 = 0xfff1;
    p->unk_0A = 0xfff1;
}

void func_ov004_02233918(char *self, int *p1, Vec3 *p2, Vec3 *p3, u16 a5)
{
    volatile u16 t = 0xfff1;
    int buf[4];
    int q;
    u16 v;
    u16 m;
    int k;
    func_0204f794(buf, p1[0], p1[1]);
    if (p3->y == 0) {
        q = _s32_div_f(p3->z - p2->z, 9);
        *(int *) (self + 0x30) = _s32_div_f(p3->x - p2->x, 9);
        *(int *) (self + 0x34) = 0x1000;
        *(int *) (self + 0x38) = q;
    } else {
        q = _s32_div_f(p3->z - p2->z, 0xc);
        *(int *) (self + 0x30) = _s32_div_f(p3->x - p2->x, 0xc);
        *(int *) (self + 0x34) = 0x1800;
        *(int *) (self + 0x38) = q;
    }
    v = a5;
    *(u16 *) (self + 8) = v;
    *(u16 *) (self + 0xa) = v;
    *(int *) (self + 0x24) = p2->x;
    *(int *) (self + 0x28) = p2->y;
    *(int *) (self + 0x2c) = p2->z;
    *(int *) (self + 0x3c) = 0;
    *(int *) (self + 0x40) = 0x1000;
    *(int *) (self + 0x44) = 0;
    t = v;
    m = t;
    k = (m & 0xf000) >> 12;
    switch (k) {
        case 3:
        case 4:
            *(unsigned char *) (self + 0x8e) = 0;
            break;
        default:
            func_020044c0(self + 0x4c, 0x75, 0x7f, 0);
            break;
    }
}

void func_ov004_0223383c(UnkStruct_0223383c *self)
{
    volatile unsigned short t;
    int ok;
    unsigned short lo, hi;

    self->unk_3C = self->unk_3C + 0x19a;
    if (self->unk_3C >= 0x1000) {
        self->unk_3C = 0x1000;
    }
    self->unk_44 = self->unk_3C;
    self->unk_34 = self->unk_34 - 0x400;
    VEC_Add((char *) self + 0x24, (char *) self + 0x30, (char *) self + 0x24);
    if (self->unk_34 < 0 && self->unk_28 < self->unk_1C) {
        if (self->unk_8C < 2) {
            t = 0xfff1;
            t = self->unk_0A;
            ok = 0;
            lo = t;
            hi = t;
            if (hi >= 0x1492 && lo <= 0x14fd) {
                ok = 1;
            }
            if (ok != 0) {
                func_020044c0((void *) ((char *) self + 0x4c), 0x70, 0x7f, 0);
            }
        }
        self->unk_28 = self->unk_1C;
        if (self->unk_8C == 0) {
            self->unk_8C = 1;
            self->unk_34 = 0x600;
            self->unk_30 = (0x4cd * self->unk_30) >> 12;
            self->unk_38 = (0x4cd * self->unk_38) >> 12;
        } else {
            self->unk_30 = 0;
            self->unk_34 = 0;
            self->unk_38 = 0;
            func_ov004_022339e0((struct UnkStruct_022339e0 *) self);
        }
    }
}

void func_ov004_0223380c(void *self)
{
    int i;
    int z;
    char *p;

    p = (char *) self;
    i = 0;
    z = i;
    for (; i < 0xf; i++) {
        *(int *) (p + 4) = z;
        *(unsigned short *) (p + 8) = 0xfff1;
        *(unsigned short *) (p + 0xa) = 0xfff1;
        func_0200451c(p + 0x4c);
        p += 0x94;
    }
}

void func_ov004_022337ac(Rec *r)
{
    volatile unsigned short h = 0xfff1;
    Vec3 v;
    int i;

    for (i = 0; i < 15; r++, i++) {
        if (r->unk_04 == 2) {
            r->unk_8D++;
            h = r->unk_08;
            if (r->unk_0C == 0) {
                func_ov004_0223383c((UnkStruct_0223383c *) r);
            }
            v.x = r->unk_24;
            v.y = r->unk_28;
            v.z = r->unk_2C;
            func_020044d0(r->unk_4C, &v);
        }
    }
}

void func_ov004_022336f0(char *self)
{
    volatile u16 t = 0xfff1;
    Vec3 v;
    Vec3 a, b;
    int r;
    int i;
    int z;
    char *p = self;
    i = 0;
    z = i;
    do {
        t = *(u16 *) (p + 8);
        if (*(int *) (p + 4) != 0) {
            if (t != 0xfff1) {
                char *q = p + 0x3c;
                u16 id;
                u16 m;
                int k;
                r = func_0203f8d0(&v, p + 0x24);
                func_020e96c8(&data_021fbe48, v.x, v.y, v.z);
                func_020e9774(&data_021fbe48, r);
                func_020e9838(&data_021fbe48, *(int *) (p + 0x3c), *(int *) (q + 4), *(int *) (q + 8));
                id = t;
                m = t;
                k = (m & 0xf000) >> 12;
                switch (k) {
                    case 1:
                    case 3:
                    case 4: {
                        char *s = p + 0x24;
                        a.x = *(int *) (p + 0x24);
                        a.y = *(int *) (s + 4);
                        a.z = *(int *) (s + 8);
                        b.x = 0x1000;
                        b.y = 0x1000;
                        b.z = 0x1000;
                        func_ov004_02233dc0(data_ov004_02258ae4, id, &a, &b, z, z, z);
                        break;
                    }
                }
            }
        }
        p += 0x94;
        i++;
    } while (i < 0xf);
}

void func_ov004_022336c4(void *p)
{
    int i;
    for (i = 0; i < 15; i++) {
        if (*(int *) ((char *) p + 4) != 0) {
            func_ov004_022339e0((struct UnkStruct_022339e0 *) p);
        }
        func_020044a0((char *) p + 0x4c);
        p = (char *) p + 0x94;
    }
}

int func_ov004_0223362c(Elem *base, int b, UnkStruct_0223362c *c, UnkStruct_0223362c_2 *d, UnkStruct_0223362c_2 *e, int ff,
                        unsigned short g, short h, unsigned char i)
{
    UnkStruct_0223362c cc;
    UnkStruct_0223362c_2 dd, ee;
    void *glob;
    Elem *p;
    int found;
    int k;

    glob = data_021c80bc;
    if (glob == 0) {
        return 0;
    }
    p = &base[b * 3];
    found = 0;
    for (k = 0; k < 3; k++) {
        if (p->unk_04 == 0) {
            dd.a = d->a;
            dd.b = d->b;
            dd.c = d->c;
            ee.a = e->a;
            ee.b = e->b;
            ee.c = e->c;
            cc.a = c->a;
            cc.b = c->b;
            func_ov004_02233a00((char *) p, b, (UnkStruct_02233a00 *) (&cc), (Vec3 *) (&dd), (Vec3 *) (&ee), ff,
                                (unsigned short) g, (int) glob, h, (unsigned char) i);
            p->unk_04 = 2;
            found = 1;
            break;
        }
        p++;
    }
    return found;
}
