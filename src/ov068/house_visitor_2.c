/* house_visitor_2: 18 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_022759f8 @ 0x022759f8, 0x3c bytes, Thumb
 * func_ov068_022759d0 @ 0x022759d0, 0x28 bytes, Thumb
 * func_ov068_02275994 @ 0x02275994, 0x3c bytes, Thumb
 * func_ov068_02275934 @ 0x02275934, 0x60 bytes, Thumb
 * func_ov068_022758a8 @ 0x022758a8, 0x8c bytes, Thumb
 * func_ov068_02275868 @ 0x02275868, 0x40 bytes, Thumb
 * func_ov068_0227584c @ 0x0227584c, 0x1a bytes, Thumb
 * func_ov068_0227580c @ 0x0227580c, 0x40 bytes, Thumb
 * func_ov068_0227576c @ 0x0227576c, 0xa0 bytes, Thumb
 * func_ov068_0227570c @ 0x0227570c, 0x60 bytes, Thumb
 * func_ov068_022753ec @ 0x022753ec, 0x320 bytes, Thumb
 * func_ov068_022753e8 @ 0x022753e8, 0x4 bytes, Thumb
 * func_ov068_022753e4 @ 0x022753e4, 0x2 bytes, Thumb
 * func_ov068_02275388 @ 0x02275388, 0x5c bytes, Thumb
 * func_ov068_0227537c @ 0x0227537c, 0xc bytes, Thumb
 * func_ov068_02275378 @ 0x02275378, 0x4 bytes, Thumb
 * func_ov068_02275358 @ 0x02275358, 0x20 bytes, Thumb
 * func_ov068_02275354 @ 0x02275354, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int unk_00;
    int unk_04;
} Pair;

typedef struct {
    char pad_00[0x510];
    char flag;
    char pad_511[0x533];
    Pair pair;
} Dest;

typedef struct {
    char pad_00[0x5c];
    u32 unk_5C;
    u32 unk_60;
    u32 unk_64;
    char pad_68[0x510 - 0x68];
    u8 unk_510;
    char pad_511[0xa44 - 0x511];
    u32 unk_A44;
    u32 unk_A48;
    char pad_A4C[0xa50 - 0xa4c];
    u8 unk_A50;
    char pad_A51[0xa70 - 0xa51];
    u32 unk_A70;
    u32 unk_A74;
    volatile u32 unk_A78;
} UnkStruct_02275934;

typedef struct {
    unsigned int lo, hi;
} UnkPair;

struct UnkStruct_022758a8 {
    unsigned char pad_00[0x564];
    unsigned char unk_564[0x4e0];
    unsigned int unk_A44;
    unsigned int unk_A48;
    unsigned char pad_A4C[4];
    unsigned char unk_A50;
    unsigned char pad_A51[0x1f];
    unsigned int unk_A70;
    unsigned char pad_A74[4];
    unsigned int unk_A78;
};

typedef struct UnkStruct_0227576c UnkStruct_0227576c;

struct UnkStruct_0227576c {
    unsigned char pad_00[0x618];
    unsigned char unk_618;
    unsigned char pad_619[0xa58 - 0x619];
    unsigned char unk_A58;
    unsigned char unk_A59;
    unsigned char pad_A5A[0xa5c - 0xa5a];
    unsigned char unk_A5C;
    unsigned char pad_A5D[0xa5e - 0xa5d];
    short unk_A5E;
    unsigned char unk_A60;
};

typedef struct {
    int x;
    int y;
    int z;
} Vec;

typedef struct {
    u8 pad_00[0x5c];
    Vec pos; // 0x5c
    u8 pad_68[0x8e - 0x68];
    short unk_8E; // 0x8e
    u8 pad_90[0x350 - 0x90];
    u8 unk_350[0x508 - 0x350]; // 0x350
    u8 unk_508;                // 0x508
    u8 pad_509[0x564 - 0x509];
    u8 unk_564[0x618 - 0x564]; // 0x564
    u8 unk_618[0x898 - 0x618]; // 0x618
    int unk_898;               // 0x898
    u8 pad_89C[0xa52 - 0x89c];
    u16 unk_A52; // 0xa52
    u8 pad_A54[0xa58 - 0xa54];
    u8 unk_A58; // 0xa58
    u8 unk_A59; // 0xa59
    u8 pad_A5A[0xa5c - 0xa5a];
    u8 unk_A5C; // 0xa5c
    u8 pad_A5D;
    short unk_A5E; // 0xa5e
    u8 unk_A60;    // 0xa60
    u8 pad_A61;
    short unk_A62; // 0xa62
    Vec unk_A64;   // 0xa64
    Vec unk_A70;   // 0xa70
} UnkStruct_022753ec;

struct UnkStruct_02275388 {
    char pad_00[0x618];
    int unk_618;
    char pad_61C[0xa58 - 0x61c];
    u8 unk_A58;
    u8 unk_A59;
};

struct InnerOverlay {
    int unk_00;
    int unk_04;
};

struct OuterOverlay {
    char pad_00[0x8DC];
    struct InnerOverlay *ptr;
};

extern int func_020147e0(void *p, int a, int b);
extern Pair __ptmf_null;
extern int func_020044c0(char *p, int a, int b, int c);
extern void func_020b220c(void);
extern unsigned int data_ov068_02277fdc[2];
extern int func_02019d0c(void *p, int a, int b, unsigned int c, unsigned int d, int e, int f, int g, int h, int i, int j);
extern int func_02019de8(void *p);
extern int func_02014868(void *);
extern unsigned short data_020c80f8;
extern int func_ov068_02275c78(int a1, int a2);
extern int func_0203e020(int a1);
extern void func_0201af28(char *addr, int a, int b, int c, int d);
extern int func_0203e0a8(void *, int);
extern unsigned int *func_02095794(int);
extern int func_02030818(void *);
extern void *data_020c814c;
extern int func_02019c6c(void *self, int a, int b);
extern void func_0201ad18(void *self, int a, int b, int c, int d, int e, void *f, int g);
extern int func_02030864(int a);
extern unsigned char data_021fbee8[];
extern int data_020ca0ec;
extern int func_020ea990(void *, void *);
extern int func_020eaa2c(void *, void *);
extern int func_02019e00(void *);
extern void func_ov068_02276458(UnkStruct_022753ec *);
extern int func_ov004_0221e1e0(Vec *, Vec *, int);
extern int func_020644cc(int);
extern int func_0201c194(UnkStruct_022753ec *, Vec *);
extern void func_0201b044(void *, Vec *);
extern void *func_020961a8(int);
extern int func_0201c314(struct UnkStruct_02275388 *, void *);
extern int func_020147fc(int *, int, int, int);

void func_ov068_022759f8(void *self)
{
    signed char *p;
    int v;

    p = (signed char *) self;
    v = p[0xa61];
    if (v > 0) {
        p[0xa61] = v - 1;
    }
    if (p[0xa61] == 0) {
        func_020147e0((char *) self + 0x618, 0, 1);
        p[0xa61] = -1;
    }
}

int func_ov068_022759d0(Dest *dst)
{
    dst->pair = __ptmf_null;
    dst->flag = 1;
    return 1;
}

void func_ov068_02275994(char *self)
{
    if (*(int *) ((char *) *(int *) (self + 0x8dc) + 4) != 0) {
        return;
    }
    func_020044c0(self + 0x514, 0x4cb, 0x7f, 0);
    func_020b220c();
    func_ov068_02275c78((int) self, 3);
}

int func_ov068_02275934(UnkStruct_02275934 *self)
{
    u32 a, b;
    self->unk_A70 = self->unk_5C;
    self->unk_A74 = self->unk_60;
    self->unk_A78 = self->unk_64;
    self->unk_A78 -= 0x2000;

    a = (*(volatile struct { u32 a; u32 b; } *) &__ptmf_null).a;
    b = (*(volatile struct { u32 a; u32 b; } *) &__ptmf_null).b;
    self->unk_A44 = a;
    self->unk_A48 = b;

    self->unk_510 = 1;
    self->unk_A50 = 0x28;
    return 1;
}

void func_ov068_022758a8(struct UnkStruct_022758a8 *self)
{
    if (self->unk_A50 == 1) {
        *(UnkPair *) ((char *) self + 0xa44) = *(UnkPair *) &data_ov068_02277fdc;
        func_02019d0c(&self->unk_564, 1, 2, self->unk_A70, self->unk_A78, 0, 0, 0, 0, 0, 0);
    } else if (self->unk_A50 == 0) {
        if (func_02019de8(&self->unk_564) != 0) {
            func_ov068_02275c78((int) self, 4);
        }
    }
    if (self->unk_A50 != 0) {
        self->unk_A50--;
    }
}

void func_ov068_02275868(void *self)
{
    if (func_02014868((char *) self + 0x618)) {
        func_02019c6c((char *) self + 0x564, 2, (unsigned short) data_020c80f8);
    } else {
        func_02019c6c((char *) self + 0x564, 1, (unsigned short) data_020c80f8);
    }
}

void func_ov068_0227584c(int a1)
{
    if (func_ov068_02275c78(a1, 5) != 0) {
        func_0203e020(a1);
    }
}

int func_ov068_0227580c(char *p)
{
    *(unsigned short *) (p + 0x0a52) = 5;
    func_0201af28(p + 0x350, 1, 0x148, 0x25, 0x25);
    *(unsigned short *) (p + 0x0a5e) = 0x258;
    return 1;
}

void func_ov068_0227576c(UnkStruct_0227576c *self)
{
    if (func_02014868(&self->unk_618) == 0) {
        if (!(self->unk_A5E != 0 && self->unk_A5C != 0)) {
            unsigned char tmp = self->unk_A60;
            if (tmp == 0) {
                func_0203e0a8(self, 0);
                self->unk_A58 = 1;
                return;
            }
            if (tmp != 0) {
                tmp--;
                self->unk_A60 = tmp;
            }
        }
        if (self->unk_A5E > 0) {
            self->unk_A5E--;
        }
    }
    {
        unsigned int *data = func_02095794(4);
        if (data != 0) {
            unsigned int buf[3];
            buf[0] = data[0];
            buf[1] = data[1];
            buf[2] = data[2];
            if (func_02030818(buf) != 0) {
                func_0203e0a8(self, 0);
                self->unk_A59 = 1;
            }
        }
    }
}

int func_ov068_0227570c(void *param)
{
    if (func_02019c6c((char *) param + 0x564, 1, data_020c80f8) != 0) {
        func_0201ad18((char *) param + 0x3b0, 1, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
        func_02030864(0);
        return 1;
    }
    return 0;
}

void func_ov068_022753ec(UnkStruct_022753ec *a)
{
    Vec v;
    Vec loc;
    Vec *e;
    int d;
    u8 t;
    short cur;

    e = (Vec *) func_02095794(4);
    if (a->unk_898 == 6 && func_02014868(a->unk_618) == 0) {
        if (a->unk_A5E == 0 || a->unk_A5C == 0) {
            t = a->unk_A60;
            if (t == 0) {
                func_0203e0a8((void *) a, 0);
                a->unk_A58 = 1;
                return;
            }
            if (t != 0) {
                a->unk_A60 = t - 1;
            }
        }
        if (a->unk_A5E > 0) {
            a->unk_A5E--;
        }
    }

    if (a->unk_898 == 6 && e != 0) {
        v.x = e->x;
        v.y = e->y;
        v.z = e->z;
        if (func_02030818((void *) (&v)) != 0) {
            func_0203e0a8((void *) a, 0);
            a->unk_A59 = 1;
            return;
        }
    }

    d = data_020ca0ec;
    if (e != 0) {
        d = func_020ea990(e, &a->pos);
    }

    if (a->unk_508 != 0 || (a->unk_898 != 6 && d < 0x2334)) {
        if (func_02019e00(a->unk_564) == 1 || a->unk_898 == 3) {
            if (func_02019c6c(a->unk_564, 2, (*(u16 *) &data_020c80f8)) != 0) {
                func_ov068_02276458(a);
                return;
            }
        }
    }

    if (func_02019e00(a->unk_564) == 0) {
        if (a->unk_A52 != 0) {
            a->unk_A52--;
        }
        if (a->unk_A52 == 0) {
            a->unk_A62 = (short) func_ov004_0221e1e0(&a->unk_A70, &a->pos, a->unk_8E);
            a->unk_A64.x = a->unk_A70.x;
            a->unk_A64.y = a->unk_A70.y;
            a->unk_A64.z = a->unk_A70.z;
            cur = a->unk_A62;
            if (cur != a->unk_8E) {
                if (func_02019d0c(a->unk_564, 3, 1, 0, 0, 0, cur, 0, 0, (*(u16 *) &data_020c80f8), 0) != 0) {
                    a->unk_A52 = (u16) (func_020644cc(0x46) + 0x14);
                }
                return;
            }
            if (func_02019d0c(a->unk_564, 1, 1, a->unk_A70.x, a->unk_A70.z, 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0) != 0) {
                a->unk_A52 = (u16) (func_020644cc(0x50) + 0x14);
            }
            return;
        }
        if (func_02019de8(a->unk_564) != 0) {
            func_02019c6c(a->unk_564, 1, (*(u16 *) &data_020c80f8));
        }
        return;
    }

    if (func_02019e00(a->unk_564) == 3) {
        if (func_02019de8(a->unk_564) == 0) {
            return;
        }
        func_02019d0c(a->unk_564, 1, 1, a->unk_A70.x, a->unk_A70.z, 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
        return;
    }

    if (func_02019e00(a->unk_564) != 1) {
        return;
    }

    switch (func_0201c194(a, &loc)) {
        case 1:
            if (func_02019c6c(a->unk_564, 1, (*(u16 *) &data_020c80f8)) != 0) {
                func_ov068_02276458(a);
            }
            return;
        case 2:
            a->unk_A64.x = loc.x;
            a->unk_A64.y = loc.y;
            a->unk_A64.z = loc.z;
            func_0201b044(a->unk_350, &a->unk_A64);
            return;
        default:
            if (func_020eaa2c(&a->unk_A64, &a->unk_A70) != 0) {
                a->unk_A64.x = a->unk_A70.x;
                a->unk_A64.y = a->unk_A70.y;
                a->unk_A64.z = a->unk_A70.z;
                func_0201b044(a->unk_350, &a->unk_A70);
                return;
            }
            if (func_020ea990(&a->unk_A70, &a->pos) < 0x200) {
                func_02019c6c(a->unk_564, 1, (*(u16 *) &data_020c80f8));
                func_ov068_02276458(a);
            }
            return;
    }
}

int func_ov068_022753e8(void)
{
    return 1;
}

void func_ov068_022753e4(void) {}

int func_ov068_02275388(struct UnkStruct_02275388 *self)
{
    void *p;
    int m;

    p = func_020961a8(4);
    if (p != 0) {
        m = func_0201c314(self, p);
        if (self->unk_A58 != 0 || self->unk_A59 != 0) {
            func_020147fc(&self->unk_618, 0, m, 1);
        } else {
            func_020147fc(&self->unk_618, 0, m, 0);
        }
        return 1;
    }
    return 0;
}

int func_ov068_0227537c(int a)
{
    return func_ov068_02275c78(a, 9);
}

int func_ov068_02275378(void)
{
    return 1;
}

void func_ov068_02275358(struct OuterOverlay *self)
{
    if (self->ptr != 0 && self->ptr->unk_04 == 0) {
        func_0203e020((int) self);
    }
}

int func_ov068_02275354(void)
{
    return 1;
}
