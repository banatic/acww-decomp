/* field_actor_55: 17 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02218ec4 @ 0x02218ec4, 0x48 bytes, Thumb
 * func_ov003_02218eb8 @ 0x02218eb8, 0xa bytes, Thumb
 * func_ov003_02218eac @ 0x02218eac, 0xa bytes, Thumb
 * func_ov003_02218e4c @ 0x02218e4c, 0x60 bytes, Thumb
 * func_ov003_02218dfc @ 0x02218dfc, 0x50 bytes, Thumb
 * func_ov003_02218dcc @ 0x02218dcc, 0x30 bytes, Thumb
 * func_ov003_02218d44 @ 0x02218d44, 0x88 bytes, Thumb
 * func_ov003_02218cec @ 0x02218cec, 0x58 bytes, Thumb
 * func_ov003_02218ca8 @ 0x02218ca8, 0x42 bytes, Thumb
 * func_ov003_02218c28 @ 0x02218c28, 0x80 bytes, Thumb
 * func_ov003_02218c24 @ 0x02218c24, 0x2 bytes, Thumb
 * func_ov003_02218bf0 @ 0x02218bf0, 0x34 bytes, Thumb
 * func_ov003_02218bc8 @ 0x02218bc8, 0x28 bytes, Thumb
 * func_ov003_022189d8 @ 0x022189d8, 0x1f0 bytes, Thumb
 * func_ov003_02218960 @ 0x02218960, 0x78 bytes, Thumb
 * func_ov003_02218920 @ 0x02218920, 0x40 bytes, Thumb
 * func_ov003_02218918 @ 0x02218918, 0x8 bytes, Thumb
 */

#include "types.h"

typedef struct Vec2 {
    int x;
    int y;
} Vec2;

typedef struct UnkStruct_02218ec4 {
    int data[3];
} UnkStruct_02218ec4;

typedef struct UnkStruct_02218ec4_2 {
    int data[3];
} UnkStruct_02218ec4_2;

struct UnkStruct_02218eb8 {
    int a;
    int b;
};

struct UnkStruct_02218eac {
    int a;
    int b;
};

typedef struct {
    int a;
    int b;
} Pair;

typedef struct {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[0xfc];
    char unk_8F0;
    char pad_8F1[0x393];
    unsigned short unk_C84;
} UnkStruct_02218dfc;

typedef struct {
    char pad_00[2];
    unsigned char flag;
} SubA;

typedef struct UnkStruct_02218d44 UnkStruct_02218d44;

typedef struct UnkStruct_02218d44_2 UnkStruct_02218d44_2;

struct UnkStruct_02218d44_2 {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
};

struct UnkStruct_02218d44 {
    unsigned char pad_00[0x7d4];
    UnkStruct_02218d44_2 sub;
    unsigned char pad_7D7[0x19];
    unsigned int unk_7F0;
    unsigned char pad_7F4[8];
    unsigned int unk_7FC;
    unsigned int unk_800;
};

typedef struct UnkStruct_02218cec {
    u8 pad_00[0x7d4];
    u8 b0;
    u8 b1;
    u8 pad_7D6[0x800 - 0x7d4 - 2];
    int unk_800;
} UnkStruct_02218cec;

typedef struct Vec {
    int x;
    int y;
    int z;
} Vec;

typedef struct Rec {
    Vec v;
    unsigned char flag;
} Rec;

typedef struct Src {
    unsigned char pad_00[0xc];
    unsigned char a;
    unsigned char b;
} Src;

typedef struct UnkStruct_02218c28 {
    unsigned char pad_00[0x5a0];
    unsigned char unk_5A0[0x7d4 - 0x5a0];
    Rec rec; // 0x7d4
    unsigned char pad_7E4[0x820 - 0x7e4];
    unsigned short unk_820;
    unsigned short unk_822;
} UnkStruct_02218c28;

struct UnkStruct_02218bf0 {
    char pad_00[0x800];
    unsigned int unk_800;
};

typedef struct {
    int x, y, z;
} UnkStruct_022189d8;

typedef struct {
    int a, b;
} UnkStruct_022189d8_2;

struct UnkStruct_022189d8_3 {
    u8 pad_00[0x8e];
    short unk_8E;
    u8 pad_90[0x7d4 - 0x90];
    UnkStruct_022189d8 unk_7D4;
    u8 pad_7E0[0x820 - 0x7e0];
    u16 unk_820;
};

typedef struct {
    char pad_00[0x2d0];
    char unk_2D0[8];
    unsigned int unk_2D8;
    char pad_2DC[0x514];
    unsigned int unk_7F0;
    char pad_7F4[0x8];
    unsigned int unk_7FC;
    unsigned int unk_800;
} UnkStruct_02218960;

struct UnkStruct_02218918 {
    int a;
    int b;
    unsigned short c;
};

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_ov003_02218f0c(UnkStruct_02218ec4_2 *, Vec2 *);
extern int func_0200e894(int, void *);
extern int func_0200e91c(void *);
extern void func_020109fc(void *, int, int, int);
extern int func_0200fbe0(void *);
extern void func_0205eae0(void *, int, int, int);
extern void func_02010f5c(void *);
extern unsigned int data_020ccf94;
extern int func_02073908(unsigned int, unsigned int);
extern unsigned int func_02008258(UnkStruct_02218d44 *, unsigned int);
extern int func_0200d4e8(UnkStruct_02218d44 *, int, int, int);
extern int func_0200f530(UnkStruct_02218cec *self, int *data);
extern void func_02010d64(UnkStruct_02218cec *self);
extern void func_0204f794(Vec *out, int a, int b);
extern void func_020109a0(UnkStruct_02218c28 *self, int b, int c, unsigned short d);
extern void *data_021c80bc;
extern unsigned short *func_0204f5a8(void *ctx, Vec *v, int z);
extern int func_0200f290(void *, int);
extern int func_02056f28(void *ptr, int size);
extern void func_0204f818(int *a, int *b, UnkStruct_022189d8 *c);
extern int func_020912d4(int a, UnkStruct_022189d8 *b, short *c, int d);
extern int func_02091230(int a, UnkStruct_022189d8 *b, int c, int d);
extern void VEC_Add(UnkStruct_022189d8 *a, UnkStruct_022189d8 *b, UnkStruct_022189d8 *dst);
extern void func_02044a14(short *a, UnkStruct_022189d8_2 *b, int c, int d);
extern void func_02045f08(UnkStruct_022189d8_2 *a, int b);
extern int func_0200f328(struct UnkStruct_022189d8_3 *self, int a);
extern void func_0200f268(struct UnkStruct_022189d8_3 *self, int a);
extern int func_02056f94(void *);
extern int func_ov003_0220d268(void *);
extern int func_0200f434(void *, int *);
extern int func_02010ca4(void *);

int func_ov003_02218ca8(void *param1, unsigned int *param2, int a2, int a3);
void func_ov003_022189d8(struct UnkStruct_022189d8_3 *self);

int func_ov003_02218ec4(int a0, Vec2 *src, int a2, int a3)
{
    Vec2 pair;
    UnkStruct_02218ec4 obj;
    UnkStruct_02218ec4_2 out;
    int ret;

    func_0200e92c(&obj);
    func_0200e90c(&obj, 0x16, a2, a3);
    pair.x = src->x;
    pair.y = src->y;
    func_ov003_02218f0c(&out, &pair);
    ret = func_0200e894(a0, &obj);
    func_0200e91c(&obj);
    return ret;
}

void func_ov003_02218eb8(u8 *d, struct UnkStruct_02218eb8 *p)
{
    d[0] = (u8) p->a;
    d[1] = (u8) p->b;
}

void func_ov003_02218eac(u8 *p, struct UnkStruct_02218eac *d)
{
    d->a = p[0];
    d->b = p[1];
}

void func_ov003_02218e4c(void *self, void *data, int previous)
{
    unsigned char *p = (unsigned char *) data + 0xc;
    unsigned char b0 = p[0];
    unsigned char b1 = p[1];
    unsigned char *dst = (unsigned char *) self + 0x7d4;
    int loc[2];

    dst[0] = b0;
    dst[1] = b1;
    dst[2] = 0;
    loc[0] = b0;
    loc[1] = b1;
    func_ov003_02218eb8((u8 *) ((unsigned char *) self + 0x8f0), (struct UnkStruct_02218eb8 *) loc);
    func_020109fc(self, 0x15, 3, 0);
    if (func_0200fbe0(self) == 4) {
        func_0205eae0((unsigned char *) self + 0x5a0, 0xb, 3, 0);
    }
}

void func_ov003_02218dfc(UnkStruct_02218dfc *self, int arg2)
{
    Pair local1, local2;

    if (self->unk_7F0 == 0x16) {
        self->unk_C84 = (unsigned short) arg2;
        return;
    }
    local1.a = 0;
    local1.b = 0;
    func_ov003_02218eac((u8 *) (&self->unk_8F0), (struct UnkStruct_02218eac *) (&local1));
    local2.a = local1.a;
    local2.b = local1.b;
    func_ov003_02218ec4((int) self, (Vec2 *) (&local2), 6, arg2);
}

void func_ov003_02218dcc(void *r0)
{
    SubA *sub = (SubA *) ((char *) r0 + 0x7d4);
    if (sub->flag == 0) {
        if (*(int *) ((char *) r0 + 0x818) == 2) {
            sub->flag = 2;
        } else if (*(int *) ((char *) r0 + 0x818) == 1) {
            sub->flag = 1;
        }
    }
    func_02010f5c(r0);
}

void func_ov003_02218d44(UnkStruct_02218d44 *s)
{
    unsigned int tmp[2];

    if (func_02073908(data_020ccf94, s->unk_800) == 0) {
        s->unk_7FC = func_02008258(s, s->unk_7F0);
    }

    {
        UnkStruct_02218d44_2 *sub = &s->sub;
        switch (sub->unk_02) {
            case 0:
                break;
            case 1: {
                unsigned int v1 = sub->unk_01;
                unsigned int v0 = sub->unk_00;
                tmp[0] = v0;
                tmp[1] = v1;
                func_ov003_02218ca8((void *) s, (unsigned int *) tmp, 6, -1);
                break;
            }
            case 2:
                s->unk_7FC = func_02008258(s, s->unk_7F0);
                func_0200d4e8(s, 3, 1, -1);
                break;
        }
    }
}

void func_ov003_02218cec(UnkStruct_02218cec *self)
{
    int pos[2];
    u8 *xy;
    u8 y;

    if (func_02073908((*(int *) &data_020ccf94), self->unk_800)) {
        func_ov003_02218dcc((void *) self);
    } else {
        func_02010f5c((void *) self);
        xy = &self->b0;
        y = xy[1];
        pos[0] = xy[0];
        pos[1] = y;
        func_0200f530(self, pos);
    }
    func_02010d64(self);
    func_ov003_02218d44((UnkStruct_02218d44 *) self);
}

int func_ov003_02218ca8(void *param1, unsigned int *param2, int a2, int a3)
{
    char buf[0x1c];
    char *p = buf + 0xc;
    int ret;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x17, a2, a3);
    p[0] = (char) param2[0];
    p[1] = (char) param2[1];
    ret = func_0200e894((int) param1, buf);
    func_0200e91c(buf);
    return ret;
}

void func_ov003_02218c28(UnkStruct_02218c28 *self, Src *src, int previous)
{
    Vec t;
    Rec *r;
    unsigned char *q = &src->a;

    func_0204f794(&t, q[0], q[1]);
    r = &self->rec;
    r->v.x = t.x;
    r->v.y = t.y;
    r->v.z = t.z;
    r->flag = 0;
    func_020109a0(self, 0x14, 3, 0);
    if (func_0200fbe0((void *) self) == 4) {
        func_0205eae0((void *) self->unk_5A0, 0xe, 3, 0);
    }
    self->unk_822 = *func_0204f5a8(data_021c80bc, &t, 0);
    self->unk_820 = self->unk_822;
}

void func_ov003_02218c24(void *receiver, int event) {}

void func_ov003_02218bf0(void *param)
{
    if (func_02073908(data_020ccf94, ((struct UnkStruct_02218bf0 *) param)->unk_800) != 0) {
        return;
    }
    if (func_0200f290(param, 0x1c) == 0) {
        return;
    }
    func_ov003_022189d8((struct UnkStruct_022189d8_3 *) param);
}

void func_ov003_02218bc8(void *arg0)
{
    void *ptr = arg0;
    func_02010f5c((void *) ((int) arg0));
    if (func_02056f28((char *) ptr + 0x2d0, 10) != 0) {
        func_ov003_022189d8((struct UnkStruct_022189d8_3 *) ptr);
    }
}

void func_ov003_022189d8(struct UnkStruct_022189d8_3 *self)
{
    short aa[2];
    int o1;
    int o2;
    UnkStruct_022189d8_2 p1;
    UnkStruct_022189d8_2 p2;
    UnkStruct_022189d8 v;
    UnkStruct_022189d8 t1;
    UnkStruct_022189d8 t2;
    UnkStruct_022189d8 t3;
    UnkStruct_022189d8 t4;
    UnkStruct_022189d8 *q;

    q = &self->unk_7D4;
    v.x = q->x;
    v.y = q->y;
    v.z = q->z;
    o1 = 0;
    o2 = 0;
    func_0204f818(&o1, &o2, &v);
    aa[0] = self->unk_8E;

    switch (self->unk_820) {
        case 0x1f:
            func_020912d4(0x2e, &v, aa, 0);
            break;
        case 0x20:
            func_020912d4(0x2f, &v, aa, 0);
            break;
        case 0x21:
            t1.x = 0;
            t1.y = 0;
            t1.z = -0x800;
            VEC_Add(&v, &t1, &v);
            func_020912d4(0x2d, &v, aa, 0);
            break;
        case 0x22:
            t2.x = -0x800;
            t2.y = 0;
            t2.z = 0;
            VEC_Add(&v, &t2, &v);
            func_020912d4(0x2d, &v, aa, 0);
            break;
        case 0x23:
            t3.x = 0x800;
            t3.y = 0;
            t3.z = 0xc00;
            VEC_Add(&v, &t3, &v);
            func_020912d4(0x2d, &v, aa, 0);
            break;
        case 0x24:
            t4.x = -0x800;
            t4.y = 0;
            t4.z = 0;
            VEC_Add(&v, &t4, &v);
            func_020912d4(0x2d, &v, aa, 0);
            break;
        default: {
            u16 k = self->unk_820;
            if ((k >= 0x6e && k <= 0x73) || (k >= 0x74 && k <= 0x79) || (k >= 0x7a && k <= 0x7f) || (k >= 0x80 && k <= 0x87) ||
                k == 0x88 || k == 0x89 || (k >= 0x8a && k <= 0x8f) || (k >= 0x90 && k <= 0x95) || (k >= 0x96 && k <= 0x9b) ||
                (k >= 0x9c && k <= 0xa3) || k == 0xa5) {
                goto match;
            }
            if (k != 0xa4) {
                break;
            }
        match:
            func_02091230(0x54, &v, 0, 0);
            aa[1] = self->unk_820;
            p1.a = o1;
            p1.b = o2;
            func_02044a14(&aa[1], &p1, self->unk_8E, 2);
            func_0200f328(self, 0x7d8);
            break;
        }
    }

    switch (self->unk_820) {
        case 0x1f:
        case 0x20:
            func_0200f328(self, 0x7d8);
            break;
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
            func_0200f328(self, 0x7ec);
            break;
    }

    p2.a = o1;
    p2.b = o2;
    func_02045f08(&p2, 0);
    func_0200f268(self, 0x1c);
}

void func_ov003_02218960(UnkStruct_02218960 *self)
{
    if (func_02056f94(self->unk_2D0)) {
        self->unk_7FC = func_02008258((UnkStruct_02218d44 *) self, self->unk_7F0);
        func_0200d4e8((UnkStruct_02218d44 *) self, 3, 1, -1);
    }
    if (((self->unk_2D8 << 4) >> 16) >= 0xe) {
        if (func_02073908((unsigned int) ((*(void **) &data_020ccf94)), self->unk_800)) {
            func_ov003_0220d268(self);
        } else {
            func_0200f268((struct UnkStruct_022189d8_3 *) self, 0x12);
        }
    }
}

void func_ov003_02218920(void *p)
{
    int local[4];
    int *base;
    func_ov003_02218bc8(p);
    base = (int *) ((char *) p + 0x7d4);
    local[0] = base[0];
    local[1] = base[1];
    local[2] = base[2];
    func_0200f434(p, local);
    func_02010d64((UnkStruct_02218cec *) p);
    func_02010ca4(p);
    func_ov003_02218960((UnkStruct_02218960 *) p);
}

void func_ov003_02218918(struct UnkStruct_02218918 *p, int a, int b, int c)
{
    p->a = a;
    p->b = b;
    p->c = (unsigned short) c;
}
