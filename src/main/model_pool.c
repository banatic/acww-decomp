/* model_pool: 19 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209d34c @ 0x0209d34c, 0xc bytes, Thumb
 * func_0209d340 @ 0x0209d340, 0xc bytes, Thumb
 * func_0209d328 @ 0x0209d328, 0x18 bytes, Thumb
 * func_0209d324 @ 0x0209d324, 0x4 bytes, Thumb
 * func_0209d320 @ 0x0209d320, 0x4 bytes, Thumb
 * func_0209d2dc @ 0x0209d2dc, 0x44 bytes, Thumb
 * func_0209d2d0 @ 0x0209d2d0, 0xa bytes, Thumb
 * func_0209d2b8 @ 0x0209d2b8, 0x18 bytes, Thumb
 * func_0209d2b4 @ 0x0209d2b4, 0x2 bytes, Thumb
 * func_0209d238 @ 0x0209d238, 0x7c bytes, Thumb
 * func_0209d200 @ 0x0209d200, 0x38 bytes, Thumb
 * func_0209d180 @ 0x0209d180, 0x80 bytes, Thumb
 * func_0209d138 @ 0x0209d138, 0x48 bytes, Thumb
 * func_0209d11c @ 0x0209d11c, 0x1a bytes, Thumb
 * func_0209d104 @ 0x0209d104, 0x16 bytes, Thumb
 * func_0209d0ac @ 0x0209d0ac, 0x58 bytes, Thumb
 * func_0209d0a4 @ 0x0209d0a4, 0x8 bytes, Thumb
 * func_0209d090 @ 0x0209d090, 0x14 bytes, Thumb
 * func_0209d088 @ 0x0209d088, 0x8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char flag;
    unsigned int value;
    char sub[1];
} UnkStruct_0209d328;

typedef struct {
    int unk_00;
    void *unk_04;
} UnkStruct_0209d2dc;

typedef struct {
    unsigned char unk_00;
    unsigned char pad_01[3];
    int unk_04;
} UnkStruct_0209d2d0;

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned int unk_14;
} Func0209D2B8;

struct UnkStruct_0209d238 {
    unsigned char unk_00;
    char pad_01[3];
    void *unk_04;
    char pad2[20];
};

struct UnkStruct_0209d238_2 {
    unsigned short unk_00;
    unsigned short pad2;
    unsigned int unk_04;
    int unk_08;
    struct UnkStruct_0209d238 *unk_0C;
};

struct UnkStruct_0209d200;

struct UnkStruct_0209d200_2 {
    unsigned short unk_00;
    unsigned char pad_02[6];
    int unk_08;
    struct UnkStruct_0209d200 *unk_0C;
};

struct UnkStruct_0209d200 {
    char unk_00;
    char pad_01[3];
    void *unk_04;
    char pad_08[20];
};

typedef struct Elem {
    u8 pad_00[0x1c];
} Elem;

typedef struct UnkStruct_0209d180 {
    int unk_00;
    u32 count;
    int unk_08;
    Elem *buf;
    int (*fn)(int, int);
    void (*unk_14)(void);
} UnkStruct_0209d180;

struct UnkStruct_0209d138_2 {
    char data[0x1c];
};

typedef struct {
    u16 unk_00;
    u32 unk_04;
    u32 unk_08;
    struct UnkStruct_0209d138_2 *arr;
    u32 unk_10;
    void (*unk_14)(void);
} UnkStruct_0209d138;

struct UnkStruct_0209d11c {
    char pad_00[0x34];
    char unk_34;
    char pad_35[3];
    int unk_38;
};

typedef struct {
    char pad_00[0x34];
    unsigned char flag;
    char pad_35[3];
    unsigned int value;
} UnkStruct_0209d0ac;

extern void *func_02055cf4(void *);
extern void *func_020ea0e0(unsigned int, int);
extern int func_02055c80(UnkStruct_0209d2dc *, int, int, int);
extern void func_020e9b9c(void *arg);
extern void *func_020e98b4(int size);
extern void func_020e9898(struct UnkStruct_0209d138_2 *p);
extern void *func_02055b00(struct UnkStruct_0209d11c *p);
extern void func_02055af4(int a);
extern int func_020559d0(UnkStruct_0209d0ac *, unsigned int, int, int, unsigned int);
extern unsigned int data_021fbe94;
extern void func_02055aac(void *);
extern int func_02055950(int *);

void func_0209d090(void *arg0);

void func_0209d34c(unsigned short *ptr)
{
    *ptr = 0xFFFF;
}

void func_0209d340(unsigned short *ptr)
{
    *ptr = 0xFFFF;
}

UnkStruct_0209d328 *func_0209d328(UnkStruct_0209d328 *obj)
{
    func_02055cf4(obj->sub);
    obj->flag = 0;
    obj->value = 0;
    return obj;
}

int func_0209d324(int *p0)
{
    return p0[1];
}

int func_0209d320(int p0)
{
    return ((int) (p0) + (8));
}

int func_0209d2dc(UnkStruct_0209d2dc *self, int a, int b, int c, int d)
{
    if (c) {
        self->unk_04 = func_020ea0e0((c + 3) & ~3, d);
    }
    if (a || b) {
        self = self + 1;
        if (func_02055c80(self, a, 0, b)) {
            return 1;
        } else {
            return 0;
        }
    }
    return 1;
}

int func_0209d2d0(UnkStruct_0209d2d0 *p)
{
    p->unk_00 = 0;
    p->unk_04 = 0;
    return 1;
}

void func_0209d2b8(Func0209D2B8 *param)
{
    param->unk_10 = 0;
    param->unk_14 = 0;
    param->unk_0C = 0;
    param->unk_04 = 0;
    param->unk_08 = 0;
    param->unk_00 = 0xffff;
}

void func_0209d2b4(void *object) {}

struct UnkStruct_0209d238 *func_0209d238(struct UnkStruct_0209d238_2 *self, unsigned short *out)
{
    unsigned short v;
    struct UnkStruct_0209d238 *p;
    unsigned short i;
    unsigned int count;
    struct UnkStruct_0209d238 *base;
    struct UnkStruct_0209d238 *q;

    v = *out;
    if (v == 0xffff) {
        base = self->unk_0C;
        p = base;
        i = 0;
        count = self->unk_04;
        while (i < count) {
            if (p->unk_00 == 0 && i != self->unk_00) {
                p->unk_00 = 1;
                *out = i;
                self->unk_08++;
                return p;
            }
            p++;
            i = (unsigned short) (i + 1);
        }
        q = base + self->unk_00;
        if (q->unk_00 == 0) {
            q->unk_00 = 1;
            *out = self->unk_00;
            self->unk_08++;
            return q;
        }
        goto ret0;
    }
    if (v < self->unk_04) {
        return self->unk_0C + v;
    }
    *out = 0xffff;
ret0:
    return 0;
}

void func_0209d200(struct UnkStruct_0209d200_2 *r4, unsigned short *r1)
{
    unsigned short val = *r1;
    if (val != 0xffff) {
        struct UnkStruct_0209d200 *entry = &r4->unk_0C[val];
        entry->unk_00 = 0;
        r4->unk_00 = *r1;
        *r1 = 0xffff;
        if (entry->unk_04 != 0) {
            func_020e9b9c(entry->unk_04);
        }
        r4->unk_08--;
    }
}

int func_0209d180(UnkStruct_0209d180 *self, u32 n, int a, int b, int c, int (*fn)(int, int), void (*f14)(void), void *context)
{
    Elem *p;
    u32 i;
    int t;
    int sz;

    self->fn = fn;
    self->unk_14 = f14;
    sz = n * ((c + 0x5b) & ~3);
    self->count = n;
    t = 0;
    self->unk_08 = 0;
    if (c != 0) {
        t = self->fn(sz, 0);
    }
    self->buf = (Elem *) func_020e98b4(0x1c * self->count);
    p = self->buf;
    if (p != 0) {
        for (i = 0; i < self->count; i++) {
            if (p != 0) {
                p = (Elem *) func_0209d328((UnkStruct_0209d328 *) p);
            }
            if (func_0209d2dc((UnkStruct_0209d2dc *) p, a, b, c, t) == 0) {
                return 0;
            }
            p++;
        }
    }
    return 1;
}

int func_0209d138(UnkStruct_0209d138 *s)
{
    if (s->arr != 0) {
        struct UnkStruct_0209d138_2 *p = s->arr;
        u32 i;

        for (i = 0; i < s->unk_04; i++) {
            func_0209d2d0((UnkStruct_0209d2d0 *) p);
            p++;
        }

        func_020e9898(s->arr);
    }

    if (s->unk_14 != 0) {
        s->unk_14();
    }

    s->unk_10 = 0;
    s->unk_14 = 0;
    s->unk_04 = 0;
    s->unk_08 = 0;
    s->unk_00 = 0xffff;
    s->arr = 0;

    return 1;
}

struct UnkStruct_0209d11c *func_0209d11c(struct UnkStruct_0209d11c *p)
{
    func_02055b00(p);
    p->unk_34 = 0;
    p->unk_38 = 0;
    return p;
}

int func_0209d104(int a)
{
    func_0209d090((void *) a);
    func_02055af4(a);
    return a;
}

unsigned char func_0209d0ac(UnkStruct_0209d0ac *P, unsigned int X, unsigned int Y)
{
    if (P->value == 0) {
        P->value = X;
    }
    if (P->flag != 0) {
        goto exit;
    }
    {
        int v1 = func_0209d320(X);
        int v2 = func_0209d324((int *) X);
        if (func_020559d0(P, Y, v1, v2, data_021fbe94) == 3) {
            P->flag = 1;
        }
    }
exit:
    return P->flag;
}

void func_0209d0a4(void *argument0)
{
    func_0209d090((void *) argument0);
}

void func_0209d090(void *arg0)
{
    unsigned char *ptr = (unsigned char *) arg0;
    unsigned int *ptr2 = (unsigned int *) arg0;

    ptr[0x34] = 0;
    ptr2[0x0e] = 0;
    ptr2[0x0f] = 0;
    func_02055aac(arg0);
}

int func_0209d088(int *argument0)
{
    return func_02055950((int *) argument0);
}
