/* animated_model: 30 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02055260 @ 0x02055260, 0x50 bytes, Thumb
 * func_02055210 @ 0x02055210, 0x50 bytes, Thumb
 * func_020551e0 @ 0x020551e0, 0x30 bytes, Thumb
 * func_020551ac @ 0x020551ac, 0x34 bytes, Thumb
 * func_0205517c @ 0x0205517c, 0x30 bytes, Thumb
 * func_02055140 @ 0x02055140, 0x3c bytes, Thumb
 * func_02055124 @ 0x02055124, 0x1c bytes, Thumb
 * func_0205510c @ 0x0205510c, 0x18 bytes, Thumb
 * func_020550e4 @ 0x020550e4, 0x26 bytes, Thumb
 * func_020550b8 @ 0x020550b8, 0x2c bytes, Thumb
 * func_02055060 @ 0x02055060, 0x56 bytes, Thumb
 * func_02055050 @ 0x02055050, 0x10 bytes, Thumb
 * func_0205502c @ 0x0205502c, 0x22 bytes, Thumb
 * func_02055008 @ 0x02055008, 0x22 bytes, Thumb
 * func_02054fcc @ 0x02054fcc, 0x3c bytes, Thumb
 * func_02054f68 @ 0x02054f68, 0x62 bytes, Thumb
 * func_02054ed4 @ 0x02054ed4, 0x92 bytes, Thumb
 * func_02054ecc @ 0x02054ecc, 0x8 bytes, Thumb
 * func_02054ec4 @ 0x02054ec4, 0x6 bytes, Thumb
 * func_02054e8c @ 0x02054e8c, 0x38 bytes, Thumb
 * func_02054e54 @ 0x02054e54, 0x38 bytes, Thumb
 * func_02054e18 @ 0x02054e18, 0x3c bytes, Thumb
 * func_02054dd8 @ 0x02054dd8, 0x40 bytes, Thumb
 * func_02054d9c @ 0x02054d9c, 0x3c bytes, Thumb
 * func_02054d80 @ 0x02054d80, 0x1a bytes, Thumb
 * func_02054d60 @ 0x02054d60, 0x20 bytes, Thumb
 * func_02054d14 @ 0x02054d14, 0x4c bytes, Thumb
 * func_02054cf4 @ 0x02054cf4, 0x20 bytes, Thumb
 * func_02054cdc @ 0x02054cdc, 0x16 bytes, Thumb
 * func_02054cac @ 0x02054cac, 0x30 bytes, Thumb
 */

#include "types.h"

typedef struct {
    void *unk_00;
    char pad_04[0x9c - 4];
    void *unk_9C;
    char pad_A0[0xa4 - (0x9c + 4)];
    unsigned int unk_A4;
    unsigned int unk_A8;
    unsigned int unk_AC;
    char pad_B0[0xb4 - (0xac + 4)];
    unsigned int unk_B4;
} UnkStruct_02055260;

typedef struct {
    void *vtable;
    char pad_04[0x98];
    int *unk_9C;
    char pad_A0[4];
    int unk_A4;
    int unk_A8;
    int unk_AC;
    char pad_B0[4];
    int unk_B4;
} UnkStruct_02055210;

typedef struct UnkStruct_020551e0 {
    void *unk_00;
} UnkStruct_020551e0;

typedef struct UnkStruct_020551e0_2 {
    void *unk_00;
    char pad_04[0x9c - 4];
    UnkStruct_020551e0 sub;
} UnkStruct_020551e0_2;

typedef struct {
    void *unk_00;
    char pad_04[0x98];
    void *unk_9C;
} UnkStruct_020551ac;

typedef struct {
    unsigned int unk_00;
    char pad_04[0x98];
    unsigned int unk_9C;
} UnkStruct_0205517c;

typedef struct {
    unsigned char pad_00[0x5C];
    int unk_5C;
    unsigned char pad_60[0x54];
    int unk_B4;
} UnkStruct_02055140;

struct UnkStruct_02055124 {
    char pad_00[0x9c];
    int unk_9C;
    int pad_A0;
    int unk_A4;
    char pad_A8[0xc];
    int *unk_B4;
};

typedef struct UnkStruct_0205510c {
    unsigned char pad_00[8];
    unsigned int flags;
    unsigned char pad_0C[0x30];
    unsigned int cond;
} UnkStruct_0205510c;

typedef struct {
    unsigned char pad_00[0x8];
    unsigned int unk_08;
    unsigned char pad_0C[0x30];
    unsigned int unk_3C;
    unsigned char pad_40[0x64];
    unsigned int unk_A4;
    unsigned char pad_A8[0xC];
    unsigned int *unk_B4;
} UnkStruct_020550e4;

typedef struct {
    char pad_00[4];
    unsigned short unk_04;
    char pad_06[2];
    unsigned int unk_08;
} UnkStruct_020550b8;

typedef struct {
    char pad_00[8];
    int unk_08;
    char pad_0C[0x18 - 0xC];
    int unk_18;
    char pad_1C[0xB4 - 0x1C];
    int flag;
} UnkStruct_0205502c;

typedef struct {
    char pad0[0x4C];
    unsigned int unk_4C;
    unsigned int unk_50;
    unsigned int unk_54;
} UnkStruct_02054f68;

typedef struct {
    void *unk_00;
    char pad0[0xB0];
    UnkStruct_02054f68 *t;
    char pad_B8[0x1C];
    void *u;
} UnkStruct_02054f68_2;

typedef struct {
    void *unk_00; // 0x0
    char pad_04[0xb0];
    void *t; // 0xb4
} UnkStruct_02054ed4;

typedef struct {
    unsigned char pad_00[180];
    unsigned long unk_B4;
} UnkStruct_02054ec4;

typedef struct {
    void *unk_00;
    char pad_04[152];
    void *unk_9C;
    char pad_A0[24];
    void *unk_B8;
} UnkStruct_02054e8c;

typedef struct UnkStruct_02054e54 {
    void *unk_00;
    unsigned char pad_04[0x98];
    void *unk_9C;
    unsigned char pad_A0[0x18];
    void *unk_B8;
} UnkStruct_02054e54;

struct UnkStruct_02054e18 {
    void *unk_00;
    char pad_04[0x98];
    void *unk_9C;
    char pad_A0[0x18];
    void *unk_B8;
};

typedef struct {
    void *unk_00;
    char pad_04[0x98];
    void *unk_9C;
    char pad_A0[0x18];
    void *unk_B8;
} UnkStruct_02054dd8;

typedef struct {
    void *unk_00;
    unsigned char pad_04[0x98];
    void *unk_9C;
    unsigned char pad_A0[0x18];
    void *unk_B8;
} UnkStruct_02054d9c;

typedef struct {
    char pad_00[0xb8];
    char sub[0x38];
    int unk_F0;
} UnkStruct_02054d80;

extern void *func_020557a0(void *);
extern char data_020dd184;
extern unsigned char data_020dd05c[];
extern unsigned char data_020dd06c[];
void func_02057054(void *ptr);
void *func_0205572c(void *ptr);
void func_020edb3c(void *ptr);
extern int func_02056548(int, int *, int);
extern int data_020dd030;
extern void func_02056ffc(void *p);
extern void func_02055e7c(UnkStruct_0205510c *s, int param2);
void func_02056fcc(void *p, unsigned short a, int b, int c, unsigned short d);
void NNS_G3dAnmObjInit(void *p, int a, void *b, int c);
extern void NNS_G3dRenderObjAddAnmObj(void *arg1, unsigned int arg2);
extern void NNS_G3dRenderObjRemoveAnmObj(void *a, void *b);
extern void func_02070d24(u8 b);
extern void func_02070c50(void *a, void *b, int c);
extern void func_02070cc4(void *a);
extern void func_02070ca4(void *a);
extern void func_02070cf4(void *a, void *b);
extern void func_02070d4c(u8 b);
extern void *func_02056f04(void *);
extern char data_020dd0dc[];
extern char data_020dd0ec[];
extern char data_020dd0fc[];
void func_02056eb0(void *p);
extern void func_02056aa0(void *sub, int arg);
extern int func_01ffcc10(void *p1, void *p2);
extern void func_02056b18(void *p, void *q);
extern void MTX_Identity33_(void *p);
extern int func_02056e84(void *ptr);
extern void func_02056e60(void *addr, int value);

void *func_02055260(void *arg)
{
    UnkStruct_02055260 *obj;
    obj = (UnkStruct_02055260 *) arg;
    func_020557a0(arg);
    obj->unk_9C = &data_020dd184;
    obj->unk_A4 = 0;
    obj->unk_A8 = 0;
    obj->unk_AC = 0x1000;
    obj->unk_00 = ((char *) data_020dd05c);
    obj->unk_9C = ((char *) data_020dd06c);
    obj->unk_B4 = 0;
    return arg;
}

UnkStruct_02055210 *func_02055210(UnkStruct_02055210 *self)
{
    func_020557a0((void *) self);
    self->unk_9C = ((int *) &data_020dd184);
    self->unk_A4 = 0;
    self->unk_A8 = 0;
    self->unk_AC = 0x1000;
    self->vtable = ((int *) data_020dd05c);
    self->unk_9C = ((int *) data_020dd06c);
    self->unk_B4 = 0;
    return self;
}

UnkStruct_020551e0_2 *func_020551e0(UnkStruct_020551e0_2 *self)
{
    self->unk_00 = (void *) data_020dd05c;
    self->sub.unk_00 = (void *) data_020dd06c;
    func_02057054((void *) (&self->sub));
    func_0205572c((void *) self);
    return self;
}

void *func_020551ac(UnkStruct_020551ac *self)
{
    self->unk_00 = ((char *) data_020dd05c);
    self->unk_9C = ((char *) data_020dd06c);
    func_02057054(&self->unk_9C);
    func_0205572c(self);
    func_020edb3c(self);
    return self;
}

UnkStruct_0205517c *func_0205517c(UnkStruct_0205517c *param)
{
    param->unk_00 = (unsigned int) ((char *) data_020dd05c);
    param->unk_9C = (unsigned int) ((char *) data_020dd06c);
    func_02057054(&param->unk_9C);
    func_0205572c(param);
    return param;
}

int func_02055140(UnkStruct_02055140 *self, int a)
{
    if (self->unk_B4 != 0) {
        goto L_return0;
    }
    if (self->unk_5C != 0) {
        goto L_call;
    }
L_return0:
    return 0;
L_call:
    self->unk_B4 = func_02056548(self->unk_5C, &data_020dd030, a);
    if (self->unk_B4 == 0) {
        return 0;
    }
    return 1;
}

void func_02055124(struct UnkStruct_02055124 *arg)
{
    int value;
    int *ptr;
    func_02056ffc(&arg->unk_9C);
    value = arg->unk_A4;
    ptr = arg->unk_B4;
    *ptr = value;
}

void func_0205510c(UnkStruct_0205510c *s, int param2)
{
    if (s->cond) {
        s->flags |= 1;
    }
    func_02055e7c(s, param2);
}

void func_020550e4(UnkStruct_020550e4 *this, int param1)
{
    this->unk_A4 = param1 << 12;
    *this->unk_B4 = this->unk_A4;
    if (this->unk_3C != 0) {
        this->unk_08 |= 1;
    }
}

unsigned short func_020550b8(int param, UnkStruct_020550b8 *p)
{
    unsigned short v = p->unk_04;

    if (param == 0 || param == 2) {
        unsigned int w = p->unk_08;

        if (w & 2) {
            return v;
        }
        if (w & 1) {
            v = (unsigned short) (v - 1);
        }
    }
    return v;
}

void func_02055060(void *obj, int a1, int a2, int a3, unsigned short a4, unsigned short a5)
{
    if (a5 == 0) {
        a5 = func_020550b8(a2, (UnkStruct_020550b8 *) ((void *) a1));
    }

    func_02056fcc((void *) ((char *) obj + 0x9c), a5, a2, a3, a4);
    NNS_G3dAnmObjInit(*(void **) ((char *) obj + 0xb4), a1, *(void **) ((char *) obj + 0x5c), 0);

    {
        int value = *(int *) ((char *) obj + 0xa4);
        *(int *) (*(void **) ((char *) obj + 0xb4)) = value;
    }
}

void func_02055050(void *p)
{
    NNS_G3dRenderObjAddAnmObj((char *) p + 8, *(unsigned int *) ((char *) p + 0xB4));
}

void func_0205502c(UnkStruct_0205502c *p)
{
    if (p->flag != 0) {
        int *addr = &p->unk_08;
        NNS_G3dRenderObjRemoveAnmObj((void *) addr, (void *) p->unk_18);
        p->flag = 0;
    }
}

void func_02055008(void *arg0)
{
    void *ptr;
    void *field;

    ptr = *(void **) ((char *) arg0 + 0xb4);
    if (ptr != 0) {
        field = (char *) arg0 + 8;
        NNS_G3dRenderObjRemoveAnmObj(field, *(void **) ((char *) arg0 + 0x20));
        *(void **) ((char *) arg0 + 0xb4) = 0;
    }
}

void func_02054fcc(void *p0)
{
    void *ptr = *(void **) ((char *) p0 + 0xb4);
    if (ptr != 0) {
        if (*(void **) ((char *) p0 + 0x18) == ptr) {
            NNS_G3dRenderObjRemoveAnmObj((char *) p0 + 8, *(void **) ((char *) p0 + 0x18));
            *(void **) ((char *) p0 + 0xb4) = 0;
        } else if (*(void **) ((char *) p0 + 0x20) == ptr) {
            NNS_G3dRenderObjRemoveAnmObj((char *) p0 + 8, *(void **) ((char *) p0 + 0x20));
            *(void **) ((char *) p0 + 0xb4) = 0;
        }
    }
}

void func_02054f68(UnkStruct_02054f68_2 *s, int arg2)
{
    unsigned char *ptr;
    unsigned int val2;
    unsigned int val;
    unsigned int mode = ((unsigned char *) s->unk_00)[1];
    if (mode >= 2) {
        unsigned char *u;
        unsigned int a;
        unsigned int b;
        unsigned int w;
        unsigned char *q;
        unsigned char *q4;
        UnkStruct_02054f68 *t;
        u = (unsigned char *) s->u;
        a = *((unsigned short *) (u + 6));
        b = *((unsigned short *) (u + a));
        b = b * mode;
        q = (u + a) + b;
        w = *((unsigned int *) (q + 4));
        val = w;
        q = u + val;
        ptr = q + 4;
        q4 = ptr;
        t = s->t;
        t->unk_4C = *((unsigned int *) ptr);
        t->unk_50 = *((unsigned int *) (q4 + 4));
        t->unk_54 = *((unsigned int *) (q4 + 8));
    } else if ((mode == 1) && (arg2 != 0)) {
        unsigned char *base;
        unsigned char *p;
        unsigned int a;
        unsigned int b;
        unsigned int w;
        unsigned int cur;
        UnkStruct_02054f68 *t;
        base = (unsigned char *) s->u;
        a = *((unsigned short *) (base + 6));
        val2 = a;
        p = base + val2;
        t = s->t;
        cur = t->unk_50;
        b = *((unsigned short *) p);
        b = b * mode;
        p = p + b;
        w = *((unsigned int *) (p + 4));
        p = base + w;
        cur += (*((unsigned int *) (p + 8))) - arg2;
        t->unk_50 = cur;
    }
}

void func_02054ed4(void *unused, UnkStruct_02054ed4 *s, int p2)
{
    int r4;
    int v;

    r4 = *(unsigned char *) s->unk_00 & 0xe0;
    if (r4 == 0x40) {
        func_02070d24(((u8 *) s->unk_00)[4]);
    } else if (r4 == 0x60) {
        func_02070d24(((u8 *) s->unk_00)[5]);
    }

    if (p2 != 0) {
        func_02070c50((char *) s->t + 0x28, (char *) s->t + 0x4c, p2);
    } else {
        v = *(int *) s->t;
        if (v & 2) {
            if (!(v & 4)) {
                func_02070cc4((char *) s->t + 0x4c);
            }
        } else {
            if (v & 4) {
                func_02070ca4((char *) s->t + 0x28);
            } else {
                func_02070cf4((char *) s->t + 0x28, (char *) s->t + 0x4c);
            }
        }
    }

    if (r4 == 0x20 || r4 == 0x60) {
        func_02070d4c(((u8 *) s->unk_00)[4]);
    }
}

int func_02054ecc(int p0)
{
    return *(int *) ((char *) (*(int *) ((char *) (((int) (p0) + (180))) + (0))) + (8));
}

unsigned long func_02054ec4(UnkStruct_02054ec4 *p)
{
    return p->unk_B4;
}

UnkStruct_02054e8c *func_02054e8c(UnkStruct_02054e8c *obj)
{
    func_02055260(obj);
    func_02056f04(&obj->unk_B8);
    obj->unk_00 = (void *) ((char *) data_020dd0dc);
    obj->unk_9C = (void *) ((char *) data_020dd0ec);
    obj->unk_B8 = (void *) ((char *) data_020dd0fc);
    return obj;
}

UnkStruct_02054e54 *func_02054e54(UnkStruct_02054e54 *this)
{
    func_02055260(this);
    func_02056f04((void *) &this->unk_B8);
    this->unk_00 = data_020dd0dc;
    this->unk_9C = data_020dd0ec;
    this->unk_B8 = data_020dd0fc;
    return this;
}

void *func_02054e18(struct UnkStruct_02054e18 *self)
{
    self->unk_00 = (void *) ((unsigned char *) data_020dd0dc);
    self->unk_9C = (void *) ((unsigned char *) data_020dd0ec);
    self->unk_B8 = (void *) ((unsigned char *) data_020dd0fc);
    func_02056eb0(&self->unk_B8);
    func_0205517c((UnkStruct_0205517c *) self);
    return self;
}

void *func_02054dd8(void *p)
{
    UnkStruct_02054dd8 *s = (UnkStruct_02054dd8 *) p;
    s->unk_00 = ((char *) data_020dd0dc);
    s->unk_9C = ((char *) data_020dd0ec);
    s->unk_B8 = ((char *) data_020dd0fc);
    func_02056eb0(&s->unk_B8);
    func_0205517c((UnkStruct_0205517c *) p);
    func_020edb3c(p);
    return p;
}

UnkStruct_02054d9c *func_02054d9c(UnkStruct_02054d9c *self)
{
    self->unk_00 = ((char *) data_020dd0dc);
    self->unk_9C = ((char *) data_020dd0ec);
    self->unk_B8 = ((char *) data_020dd0fc);
    func_02056eb0((void *) (&self->unk_B8));
    func_0205517c((UnkStruct_0205517c *) self);
    return self;
}

void func_02054d80(UnkStruct_02054d80 *self, int arg)
{
    if (self->unk_F0 != 0) {
        func_02056aa0(self->sub, arg);
    }
}

void func_02054d60(void *p1, void *p2)
{
    if (func_01ffcc10(p1, p2) == 0) {
        func_02054d80((UnkStruct_02054d80 *) p1, (int) p2);
    }
}

void func_02054d14(void *p, void *q)
{
    void *r0;
    void *r5 = p;
    void *r4 = q;
    void *r1;
    void *r2;
    int flags;

    r0 = (char *) r4 + 0xb4;
    r0 = *(void **) r0;
    flags = *(int *) r0;
    if (flags & 4) {
        *(int *) ((char *) r0 + 0x4c) = 0;
        *(int *) ((char *) r0 + 0x50) = 0;
        *(int *) ((char *) r0 + 0x54) = 0;
    }
    flags = *(int *) r0;
    if (flags & 2) {
        MTX_Identity33_((char *) r0 + 0x28);
    }
    r0 = (char *) r5 + 0xf0;
    r0 = *(void **) r0;
    if (r0 != 0) {
        func_02056b18((char *) r5 + 0xb8, r4);
    }
}

void func_02054cf4(int p1, int p2)
{
    int ret;
    ret = func_01ffcc10((void *) p1, (void *) p2);
    if (ret == 0) {
        func_02054d14((void *) p1, (void *) p2);
    }
}

void func_02054cdc(void *arg)
{
    void *r4 = arg;
    func_02056e84((char *) r4 + 0xb8);
    func_02055124((struct UnkStruct_02055124 *) r4);
}

void func_02054cac(unsigned char *a, int b, int c, int d, int e, unsigned short f, unsigned short g)
{
    func_02056e60(a + 0xb8, c);
    func_02055060(a, b, d, e, f, g);
}
