/* birthday_villager_2: 21 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221c6d4 @ 0x0221c6d4, 0x58 bytes, Thumb
 * func_ov004_0221c494 @ 0x0221c494, 0x240 bytes, Thumb
 * func_ov004_0221c410 @ 0x0221c410, 0x84 bytes, Thumb
 * func_ov004_0221c40c @ 0x0221c40c, 0x2 bytes, Thumb
 * func_ov004_0221c3fc @ 0x0221c3fc, 0x10 bytes, Thumb
 * func_ov004_0221c39c @ 0x0221c39c, 0x60 bytes, Thumb
 * func_ov004_0221c38c @ 0x0221c38c, 0x10 bytes, Thumb
 * func_ov004_0221c310 @ 0x0221c310, 0x7c bytes, Thumb
 * func_ov004_0221c2dc @ 0x0221c2dc, 0x34 bytes, Thumb
 * func_ov004_0221c2d8 @ 0x0221c2d8, 0x2 bytes, Thumb
 * func_ov004_0221c2a4 @ 0x0221c2a4, 0x34 bytes, Thumb
 * func_ov004_0221c298 @ 0x0221c298, 0xc bytes, Thumb
 * func_ov004_0221c294 @ 0x0221c294, 0x4 bytes, Thumb
 * func_ov004_0221c274 @ 0x0221c274, 0x20 bytes, Thumb
 * func_ov004_0221c270 @ 0x0221c270, 0x4 bytes, Thumb
 * func_ov004_0221c264 @ 0x0221c264, 0xc bytes, Thumb
 * func_ov004_0221c224 @ 0x0221c224, 0x40 bytes, Thumb
 * func_ov004_0221c0f0 @ 0x0221c0f0, 0x134 bytes, Thumb
 * func_ov004_0221c0ec @ 0x0221c0ec, 0x4 bytes, Thumb
 * func_ov004_0221c0cc @ 0x0221c0cc, 0x20 bytes, Thumb
 * func_ov004_0221c0bc @ 0x0221c0bc, 0x10 bytes, Thumb
 */

#include "types.h"

#define B(p, o) (*(u8 *) ((p) + (o)))
#define H(p, o) (*(u16 *) ((p) + (o)))
#define S(p, o) (*(short *) ((p) + (o)))
#define W(p, o) (*(int *) ((p) + (o)))
#define V(p, o) ((Vec *) ((p) + (o)))

struct UnkStruct_0221c6d4 {
    u8 pad_00[0x3b0];
    u8 sub[0x564 - 0x3b0];
    u8 sub2[4];
};

typedef struct {
    int x, y, z;
} Vec;

struct UnkStruct_0221c2dc {
    u8 pad_00[0x564];
    u8 sub[0x898 - 0x564];
    int phase;
};

struct InnerOverlay {
    int unk_00;
    int unk_04;
};

struct OuterOverlay {
    char pad_00[0x8e0];
    struct InnerOverlay *ptr;
};

typedef struct {
    int a, b, c;
} UnkStruct_0221c0f0;

extern u16 data_020c80f8;
extern int data_020c814c;
extern int data_021fbee8;
extern int func_02019c6c(void *p, int a, u16 b);
extern void func_0201ad18(void *p, int a, int b, int c, void *d, int e, int f, int g);
extern int func_02019e00(void *);
extern int func_ov004_0221e1e0(Vec *, Vec *, int);
extern int func_020644cc(int);
extern int func_02019de8(void *);
extern int func_0201c194(char *, Vec *);
extern void func_0201b044(void *, Vec *);
extern int func_020eaa2c(Vec *, Vec *);
extern int func_020ea990(Vec *, Vec *);
extern char *func_ov004_0221e2c0(void);
extern int func_020e8ed8(int dx, int dz);
extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern int func_02019c90(void *p, int a, int b, u16 c);
extern int func_ov004_0221c844(void *self, int a);
extern void *func_020961a8(int k);
extern int func_0201c314(void *self, void *p);
extern int func_020147fc(void *p, int x, int y, int z);
int func_0203e020(struct OuterOverlay *self);
extern int func_0203e0a8(int a, int b);
extern void *func_02095794(int);
extern int func_0201c378(void *self, int a);
extern int func_0200322c(void *a, void *b);
extern int func_020e8b4c(int a, int b);

int func_ov004_0221c6d4(struct UnkStruct_0221c6d4 *self)
{
    if (func_02019c6c(&self->sub2, 1, data_020c80f8)) {
        func_0201ad18(&self->sub, 1, 0, 0, &data_021fbee8, 4, data_020c814c, 1);
        return 1;
    }
    return 0;
}

static inline void copy(Vec *d, const Vec *s)
{
    d->x = s->x;
    d->y = s->y;
    d->z = s->z;
}

void func_ov004_0221c494(char *self)
{
    Vec next;
    char *state = self + 0x564;
    if (B(self, 0x508) != 0 && func_02019e00(state) == 1) {
        func_02019d0c(state, 0, 1, 0, 0, 0, 0, 0, 0, (u16) data_020c80f8, 0);
        return;
    }
    if (func_02019e00(self + 0x564) == 0) {
        if (H(self, 0xa56) != 0) {
            --H(self, 0xa56);
        }
        if (H(self, 0xa56) == 0) {
            H(self, 0xa54) = func_ov004_0221e1e0(V(self, 0xa64), V(self, 0x5c), S(self, 0x8e));
            copy(V(self, 0xa58), V(self, 0xa64));
            if (S(self, 0xa54) != S(self, 0x8e)) {
                if (func_02019d0c(self + 0x564, 3, 1, 0, 0, 0, (short) (S(self, 0xa54)), 0, 0, (u16) data_020c80f8, 0)) {
                    H(self, 0xa56) = func_020644cc(70) + 20;
                }
            } else {
                if (func_02019d0c(self + 0x564, 1, 1, W(self, 0xa64), W(self, 0xa6c), 0, 0, 0, 0, (u16) data_020c80f8, 0)) {
                    H(self, 0xa56) = func_020644cc(80) + 20;
                }
            }
        } else {
            if (func_02019de8(self + 0x564)) {
                func_02019c6c(self + 0x564, 1, data_020c80f8);
            }
        }
    } else if (func_02019e00(self + 0x564) == 3) {
        if (func_02019de8(self + 0x564)) {
            func_02019d0c(self + 0x564, 1, 1, W(self, 0xa64), W(self, 0xa6c), 0, 0, 0, 0, (u16) data_020c80f8, 0);
        }
    } else if (func_02019e00(self + 0x564) == 1) {
        switch (func_0201c194(self, &next)) {
            case 1:
                func_02019c6c(self + 0x564, 1, data_020c80f8);
                break;
            case 2:
                copy(V(self, 0xa58), &next);
                func_0201b044(self + 0x350, V(self, 0xa58));
                break;
            default:
                if (func_020eaa2c(V(self, 0xa58), V(self, 0xa64))) {
                    copy(V(self, 0xa58), V(self, 0xa64));
                    func_0201b044(self + 0x350, V(self, 0xa64));
                } else if (func_020ea990(V(self, 0xa64), V(self, 0x5c)) < 0x200) {
                    func_02019c6c(self + 0x564, 1, data_020c80f8);
                }
                break;
        }
    }
}

int func_ov004_0221c410(char *s)
{
    char *m = s + 0x564;
    char *o = func_ov004_0221e2c0();
    if (o != 0) {
        func_02019d0c(m, 3, 1, 0, 0, 0,
                      func_020e8ed8(*(int *) (o + 0x5c) - *(int *) (s + 0x5c), *(int *) (o + 0x64) - *(int *) (s + 0x64)), 0,
                      0, data_020c80f8, 0);
        func_0201ad18(s + 0x3b0, 2, 0, (int) o, &data_021fbee8, 4, data_020c814c, 1);
        return 1;
    }
    return 0;
}

void func_ov004_0221c40c(void *callbackObject) {}

int func_ov004_0221c3fc(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0xa53) = 0x1e;
    return 0x1;
}

void func_ov004_0221c39c(char *self)
{
    if (*(u8 *) (self + 0xa53) != 0) {
        *(u8 *) (self + 0xa53) = *(u8 *) (self + 0xa53) - 1;
    }

    switch (*(u8 *) (self + 0xa53)) {
        case 0x14:
            func_02019c90(self + 0x564, 1, 3, data_020c80f8);
            break;
        case 1:
            func_02019c90(self + 0x564, 1, 0, data_020c80f8);
            break;
        case 0:
            func_ov004_0221c844(self, 0);
            break;
    }
}

int func_ov004_0221c38c(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0xa53) = 0x32;
    return 0x1;
}

void func_ov004_0221c310(char *self)
{
    if (*(u8 *) (self + 0xa53) != 0) {
        *(u8 *) (self + 0xa53) = (u8) (*(u8 *) (self + 0xa53) - 1);
    }
    switch (*(u8 *) (self + 0xa53)) {
        case 0x28:
            if (func_020644cc(2) == 0) {
                func_02019c90(self + 0x564, 1, 0xa, data_020c80f8);
            } else {
                func_02019c90(self + 0x564, 1, 0x17, data_020c80f8);
            }
            break;
        case 1:
            func_02019c90(self + 0x564, 1, 0, data_020c80f8);
            break;
        case 0:
            func_ov004_0221c844(self, 0);
            break;
    }
}

int func_ov004_0221c2dc(struct UnkStruct_0221c2dc *self)
{
    if (self->phase == 1 || self->phase == 2 || self->phase == 3) {
        func_02019c90(&self->sub, 2, 0, data_020c80f8);
    }
    return 1;
}

void func_ov004_0221c2d8(void *callbackObject) {}

int func_ov004_0221c2a4(void *self)
{
    void *p = func_020961a8(4);
    if (p != 0) {
        func_020147fc((char *) self + 0x618, 0, func_0201c314(self, p), 0);
        return 1;
    }
    return 0;
}

void func_ov004_0221c298(int a)
{
    func_ov004_0221c844((void *) a, 6);
}

int func_ov004_0221c294(void *callbackObject)
{
    return 1;
}

void func_ov004_0221c274(struct OuterOverlay *self)
{
    if (self->ptr != 0 && self->ptr->unk_04 == 0) {
        func_0203e020(self);
    }
}

int func_ov004_0221c270(void *callbackObject)
{
    return 1;
}

int func_ov004_0221c264(int a)
{
    return func_0203e0a8(a, 0);
}

int func_ov004_0221c224(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0xa52) = 0x32;
    func_02019d0c(self + 0x564, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, *(u16 *) ((char *) ((void * *) &data_020c80f8)), 0x0);
    return 0x1;
}

void func_ov004_0221c0f0(char *self)
{
    UnkStruct_0221c0f0 t1c;
    UnkStruct_0221c0f0 t28;
    int cnt;
    int dist;
    int ang;

    {
        void *src;
        int a, b, c;
        src = func_02095794(4);
        a = *(int *) src;
        t1c.a = a;
        b = *((int *) src + 1);
        t1c.b = b;
        c = *((int *) src + 2);
        t1c.c = c;
        t28.a = a;
        t28.b = b;
        t28.c = c;
    }

    cnt = func_0201c378(self, 4);

    if (cnt > 0x4000) {
        if (func_02019e00(self + 0x564) == 1) {
            func_02019d0c(self + 0x564, 2, 1, 0, 0, 0x800, 0, 0, 0, (u16) data_020c80f8, 0);
        }
    } else {
        if (func_02019e00(self + 0x564) == 2) {
            func_02019d0c(self + 0x564, 1, 1, 0, 0, 0, 0, 0, 0, (u16) data_020c80f8, 0);
        }
    }

    func_0201b044(self + 0x350, (Vec *) (&t28));

    if (*(unsigned char *) (self + 0xa52) != 0) {
        *(unsigned char *) (self + 0xa52) = *(unsigned char *) (self + 0xa52) - 1;
    }

    dist = func_0200322c(self + 0x5c, &t1c);
    ang = *(short *) (self + 0x8e);
    ang = func_020e8b4c(ang, dist);

    if (cnt <= 0x3000 || *(unsigned char *) (self + 0xa52) == 0) {
        func_020147fc(self + 0x618, 0, dist, 0);
        func_ov004_0221c844(self, 9);
    } else if (ang > 0x2000) {
        func_02019d0c(self + 0x564, 4, 2, t28.a, t28.c, 0, dist, 0, 0, (u16) data_020c80f8, 0);
    }
}

int func_ov004_0221c0ec(void *callbackObject)
{
    return 1;
}

void func_ov004_0221c0cc(struct OuterOverlay *self)
{
    if (self->ptr != 0 && self->ptr->unk_04 == 0) {
        func_0203e020(self);
    }
}

int func_ov004_0221c0bc(char *self)
{
    // DECLS
    // ENDDECLS
    *(int *) ((char *) *(int *) (self + 0x8e0) + 0x14) = 0x1;
    return 0x1;
}
