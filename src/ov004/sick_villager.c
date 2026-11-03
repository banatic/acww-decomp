/* sick_villager: 22 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02222098 @ 0x02222098, 0x1c bytes, Thumb
 * func_ov004_02221e0c @ 0x02221e0c, 0x28c bytes, Thumb
 * func_ov004_02221dd8 @ 0x02221dd8, 0x34 bytes, Thumb
 * func_ov004_02221d64 @ 0x02221d64, 0x74 bytes, Thumb
 * func_ov004_02221d34 @ 0x02221d34, 0x30 bytes, Thumb
 * func_ov004_02221d30 @ 0x02221d30, 0x2 bytes, Thumb
 * func_ov004_02221cfc @ 0x02221cfc, 0x34 bytes, Thumb
 * func_ov004_02221cf0 @ 0x02221cf0, 0xc bytes, Thumb
 * func_ov004_02221cec @ 0x02221cec, 0x4 bytes, Thumb
 * func_ov004_02221ccc @ 0x02221ccc, 0x20 bytes, Thumb
 * func_ov004_02221cbc @ 0x02221cbc, 0x10 bytes, Thumb
 * func_ov004_02221c88 @ 0x02221c88, 0x34 bytes, Thumb
 * func_ov004_02221c84 @ 0x02221c84, 0x4 bytes, Thumb
 * func_ov004_02221c80 @ 0x02221c80, 0x2 bytes, Thumb
 * func_ov004_02221c7c @ 0x02221c7c, 0x4 bytes, Thumb
 * func_ov004_02221c70 @ 0x02221c70, 0xc bytes, Thumb
 * func_ov004_02221c64 @ 0x02221c64, 0xc bytes, Thumb
 * func_ov004_02221c50 @ 0x02221c50, 0x14 bytes, Thumb
 * func_ov004_02221c38 @ 0x02221c38, 0x18 bytes, Thumb
 * func_ov004_02221bf8 @ 0x02221bf8, 0x40 bytes, Thumb
 * func_ov004_02221bbc @ 0x02221bbc, 0x3c bytes, Thumb
 * func_ov004_02221b9c @ 0x02221b9c, 0x20 bytes, Thumb
 */

#include "types.h"

#define B(p, o) (*(u8 *) ((p) + (o)))
#define H(p, o) (*(u16 *) ((p) + (o)))
#define S(p, o) (*(short *) ((p) + (o)))
#define W(p, o) (*(int *) ((p) + (o)))
#define V(p, o) ((Vec *) ((p) + (o)))

typedef struct {
    int x, y, z;
} Vec;

struct InnerOverlay {
    int unk_00;
    int unk_04;
};

struct OuterOverlay {
    char pad_00[0x8e0];
    struct InnerOverlay *ptr;
};

struct _Obj {
    void *vtbl;
};

extern int func_02019c6c(char *p, int a, int b);
extern unsigned int data_021fbdd0;
extern int func_02019e00(void *);
extern void func_0201ca40(void *, char *);
extern int func_ov004_0221e1e0(Vec *, Vec *, int);
extern int func_02019d0c(void *, int, int, int, int, short, short, int, int, u16, u16);
extern int func_020644cc(int);
extern int func_02019de8(void *);
extern int func_0201c194(char *, Vec *);
extern void func_0201b044(void *, Vec *);
extern int func_020eaa2c(Vec *, Vec *);
extern int func_020ea990(Vec *, Vec *);
extern unsigned short data_020c80f8;
extern int func_02019c90(void *p, int a, int b, unsigned short c);
extern int func_ov004_02222178(void *self, int a);
extern void *func_020961a8(int k);
extern int func_0201c314(void *self, void *p);
extern int func_020147fc(void *p, int x, int y, int z);
int func_0203e020(struct OuterOverlay *self);
extern unsigned short func_0206f9d8(int (*predicate)(unsigned short *, int));
extern int func_0206fa28(int, int);
extern int func_ov004_02222a30(unsigned short *arg0, int arg1);
extern void *func_0202de4c(void *);
extern void *func_0202e5e0(void *argument0);
extern void func_02084f84(void *object);
extern void func_020edf54(unsigned int argument0);
extern void *data_ov004_02254148;
extern void *data_ov004_022541d8;
extern void func_020edb3c(void *);

int func_ov004_02222098(char *self)
{
    return func_02019c6c(self + 0x564, 1, (*(u16 *) &data_020c80f8));
}

static inline void copy(Vec *d, const Vec *s)
{
    d->x = s->x;
    d->y = s->y;
    d->z = s->z;
}

void func_ov004_02221e0c(char *self)
{
    Vec next;
    if (B(self, 0x897) != 0 && func_02019e00(self + 0x564) == 1 && data_021fbdd0 % 14 == 0) {
        func_0201ca40(self + 0x83c, self);
    }
    if (B(self, 0x508) != 0 && func_02019e00(self + 0x564) == 1 && func_ov004_02222178((void *) self, 1)) {
        return;
    }
    if (func_02019e00(self + 0x564) == 0) {
        if (H(self, 0xa76) != 0) {
            --H(self, 0xa76);
        }
        if (H(self, 0xa76) == 0) {
            H(self, 0xa74) = func_ov004_0221e1e0(V(self, 0xa84), V(self, 0x5c), S(self, 0x8e));
            copy(V(self, 0xa78), V(self, 0xa84));
            if (S(self, 0xa74) != S(self, 0x8e)) {
                if (func_02019d0c(self + 0x564, 3, 1, 0, 0, 0, S(self, 0xa74), 0, 0, (*(u16 *) &data_020c80f8), 0)) {
                    if (B(self, 0x897) != 0) {
                        H(self, 0xa76) = func_020644cc(70) + 50;
                    } else {
                        H(self, 0xa76) = func_020644cc(70) + 20;
                    }
                }
            } else {
                if (func_02019d0c(self + 0x564, 1, 1, W(self, 0xa84), W(self, 0xa8c), 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0)) {
                    if (B(self, 0x897) != 0) {
                        H(self, 0xa76) = func_020644cc(70) + 50;
                    } else {
                        H(self, 0xa76) = func_020644cc(80) + 20;
                    }
                }
            }
        } else {
            if (func_02019de8(self + 0x564)) {
                func_02019c6c((char *) (self + 0x564), 1, (u16) ((*(u16 *) &data_020c80f8)));
            }
        }
    } else if (func_02019e00(self + 0x564) == 3) {
        if (func_02019de8(self + 0x564)) {
            func_02019d0c(self + 0x564, 1, 1, W(self, 0xa84), W(self, 0xa8c), 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
        }
    } else if (func_02019e00(self + 0x564) == 1) {
        switch (func_0201c194(self, &next)) {
            case 1:
                func_02019c6c((char *) (self + 0x564), 1, (u16) ((*(u16 *) &data_020c80f8)));
                break;
            case 2:
                copy(V(self, 0xa78), &next);
                func_0201b044(self + 0x350, V(self, 0xa78));
                break;
            default:
                if (func_020eaa2c(V(self, 0xa78), V(self, 0xa84))) {
                    copy(V(self, 0xa78), V(self, 0xa84));
                    func_0201b044(self + 0x350, V(self, 0xa84));
                } else if (func_020ea990(V(self, 0xa84), V(self, 0x5c)) < 0x200) {
                    func_ov004_02222178((void *) self, 1);
                }
                break;
        }
    }
}

int func_ov004_02221dd8(u8 *self)
{
    if (func_02019c6c((char *) (self + 0x564), 1, data_020c80f8) != 0) {
        self[0xa90] = 0x46;
        return 1;
    }
    return 0;
}

void func_ov004_02221d64(char *self)
{
    unsigned char *p;
    unsigned int v;

    switch (*(unsigned char *) (self + 0xa90)) {
        case 0x45:
            func_02019c90(self + 0x564, 1, 7, data_020c80f8);
            break;
        case 1:
            func_02019c90(self + 0x564, 1, 0, data_020c80f8);
            *(short *) (self + 0xa76) = (short) (func_020644cc(0x14) + 0x14);
            break;
        case 0:
            if (func_ov004_02222178(self, 0) != 0) {
                return;
            }
            break;
    }
    if (*(unsigned char *) (self + 0xa90) != 0) {
        *(unsigned char *) (self + 0xa90) -= 1;
    }
}

int func_ov004_02221d34(u8 *self)
{
    if (*(int *) (self + 0x89c) == 1) {
        func_02019c90(self + 0x564, 2, 0, data_020c80f8);
    }
    return 1;
}

void func_ov004_02221d30(void *callbackObject) {}

int func_ov004_02221cfc(void *self)
{
    void *p = func_020961a8(4);
    if (p != 0) {
        func_020147fc((char *) self + 0x618, 0, func_0201c314(self, p), 0);
        return 1;
    }
    return 0;
}

void func_ov004_02221cf0(int a)
{
    func_ov004_02222178((void *) a, 4);
}

int func_ov004_02221cec(void *callbackObject)
{
    return 1;
}

void func_ov004_02221ccc(struct OuterOverlay *self)
{
    if (self->ptr != 0 && self->ptr->unk_04 == 0) {
        func_0203e020(self);
    }
}

int func_ov004_02221cbc(char *self)
{
    // DECLS
    // ENDDECLS
    *(int *) ((char *) *(int *) (self + 0x8e0) + 0x14) = 0x1;
    return 0x1;
}

void func_ov004_02221c88(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) *(int *) (self + 0x8e0) + 0x4) == 0x5 &&
        func_0206fa28(func_0206f9d8(func_ov004_02222a30), 0xd) != 0x0) {
        func_ov004_02222178(self, 0x6);
        return;
    }
}

int func_ov004_02221c84(void *callbackObject)
{
    return 1;
}

void func_ov004_02221c80(void *callbackObject) {}

int func_ov004_02221c7c(void *callbackObject)
{
    return 1;
}

void func_ov004_02221c70(int a)
{
    func_ov004_02222178((void *) a, 4);
}

void *func_ov004_02221c64(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x89a) = 0x1;
    return self;
}

int func_ov004_02221c50(unsigned char *p)
{
    if (p[0x89a] != 0) {
        return 0;
    }
    return 1;
}

void *func_ov004_02221c38(void *arg)
{
    *((void **) arg) = ((int *) &data_ov004_02254148);
    func_0202de4c(arg);
    return arg;
}

void *func_ov004_02221bf8(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_022541d8;
    func_02084f84(self + 0xa54);
    *(void **) (self + 0x8a0) = &data_ov004_02254148;
    func_0202de4c(self + 0x8a0);
    func_0202e5e0(self);
    func_020edf54((unsigned int) (self));
    return self;
}

void *func_ov004_02221bbc(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_022541d8;
    func_02084f84(self + 0xa54);
    *(void **) (self + 0x8a0) = &data_ov004_02254148;
    func_0202de4c(self + 0x8a0);
    func_0202e5e0(self);
    return self;
}

void *func_ov004_02221b9c(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02254148);
    func_0202de4c(obj);
    func_020edb3c(obj);
    return obj;
}
