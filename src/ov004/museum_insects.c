/* museum_insects: 13 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223ee98 @ 0x0223ee98, 0x84 bytes, Thumb
 * func_ov004_0223ee38 @ 0x0223ee38, 0x60 bytes, Thumb
 * func_ov004_0223edd8 @ 0x0223edd8, 0x60 bytes, Thumb
 * func_ov004_0223ed30 @ 0x0223ed30, 0xa8 bytes, Thumb
 * func_ov004_0223ecc8 @ 0x0223ecc8, 0x68 bytes, Thumb
 * func_ov004_0223ebf0 @ 0x0223ebf0, 0xd8 bytes, Thumb
 * func_ov004_0223eba4 @ 0x0223eba4, 0x4c bytes, Thumb
 * func_ov004_0223eb64 @ 0x0223eb64, 0x40 bytes, Thumb
 * func_ov004_0223eb1c @ 0x0223eb1c, 0x48 bytes, Thumb
 * func_ov004_0223eb04 @ 0x0223eb04, 0x18 bytes, Thumb
 * func_ov004_0223eaec @ 0x0223eaec, 0x18 bytes, Thumb
 * func_ov004_0223eacc @ 0x0223eacc, 0x20 bytes, Thumb
 * func_ov004_0223ea78 @ 0x0223ea78, 0x52 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0223ebf0 {
    u8 flag;
    u8 pad_01;
    short v;
};

struct _Obj {
    void *vtbl;
};

extern signed char data_ov004_0225628c;
extern char data_ov004_02259a34[];
extern signed char data_ov004_02256290;
extern char data_0213efe8[];
extern char data_0213f020[];
extern void *func_02032c64(void *);
extern void *func_02055210(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern void *func_02089b50(void *);
extern void *func_0205577c(void *);
extern void func_0209d34c(void *);
extern void *func_0209d11c(void *);
extern void func_0209d0a4(void *);
extern void func_020012dc(void *object);
extern void func_020012e8(void *object);
extern void *func_02032c50(void *);
extern void *func_020551e0(void *);
extern void *func_02055764(void *);
extern void *func_02089b38(void *);
extern int func_0209d104(void *);
extern void func_0209d340(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern struct UnkStruct_0223ebf0 data_ov004_02256308[];
extern void func_020e9898(void *);
extern void func_02055008(void *);
extern void func_0205502c(void *);
extern void func_02004280(void *);
extern void func_0209d090(void *);
extern void func_0209d200(void *, void *);
extern void func_0209d2b8(void *);
extern void *func_020ee660(void *);
extern void *data_020da13c;
extern void *data_ov004_022562c0;
extern void func_0209d2b4(void *);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);
extern void func_020565ec(void *arg);
extern int data_ov004_022562b0;
extern void *func_02056578(void *);
extern void func_020edb3c(void *);
extern void func_0209def4(void *);

void *func_ov004_0223eb04(void *arg);
void *func_ov004_0223eaec(void *arg);

int func_ov004_0223ee98(void *self, unsigned int i)
{
    switch (i) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 10:
        case 14:
        case 15:
        case 25:
        case 26:
        case 30:
        case 32:
        case 36:
        case 37:
        case 45:
        case 46:
        case 47:
        case 48:
        case 50:
        case 51:
        case 52:
            return 0;
    }
    return 1;
}

char *func_ov004_0223ee38(void)
{
    u8 i;
    char *p;
    signed char c = data_ov004_0225628c;
    if (c >= 0) {
        return data_ov004_02259a34 + 0x2d8 * c;
    }
    p = data_ov004_02259a34;
    for (i = 0; i < 0x20; i++) {
        if (*(signed char *) (p + 0x196) == 0x37 && *(int *) (p + 0x198) != 0) {
            data_ov004_0225628c = i;
            return p;
        }
        p += 0x2d8;
    }
    return 0;
}

char *func_ov004_0223edd8(void)
{
    signed char c;
    u8 i;
    char *p;
    c = data_ov004_02256290;
    i = 0;
    if (c >= 0) {
        return data_ov004_02259a34 + 0x2d8 * c;
    }
    p = data_ov004_02259a34;
    while (i < 0x20) {
        if (*(signed char *) (p + 0x196) == 0x38 && *(int *) (p + 0x198) != 0) {
            data_ov004_02256290 = i;
            return p;
        }
        p += 0x2d8;
        i++;
    }
    return 0;
}

void *func_ov004_0223ed30(char *self)
{
    int zero;
    func_ov004_0223eb04(self);
    *(char **) (self + 0x24) = data_0213efe8;
    *(char **) (self + 0x24) = data_0213f020;
    func_02032c64(self + 0x68);
    func_02055210(self + 0xb0);
    __cxa_vec_ctor(self + 0x178, 2, 0xc, ((void (*)(void *)) func_020012e8), ((void (*)(void *)) func_020012dc));
    func_02089b50(self + 0x19c);
    func_0205577c(self + 0x1e8);
    func_0209d34c(self + 0x284);
    func_0209d11c(self + 0x288);
    zero = 0;
    *(signed char *) (self + 0x196) = (signed char) ~zero;
    func_0209d0a4(self + 0x288);
    *(int *) (self + 0x2d4) = 0;
    *(int *) (self + 0x198) = 0;
    return self;
}

void *func_ov004_0223ecc8(char *self)
{
    // DECLS
    // ENDDECLS
    func_0209d104(self + 0x288);
    func_0209d340(self + 0x284);
    func_02055764(self + 0x1e8);
    func_02089b38(self + 0x19c);
    __cxa_vec_cleanup(self + 0x178, 0x2, 0xc, ((void (*)(void *)) func_020012dc));
    func_020551e0(self + 0xb0);
    func_02032c50(self + 0x68);
    func_ov004_0223eaec(self);
    return self;
}

void func_ov004_0223ebf0(char *self, int i)
{
    char *p;
    signed char c;
    int zero;
    if (i < 0 || i >= 0x20) {
        return;
    }
    p = data_ov004_02259a34 + 0x2d8 * i;
    c = *(signed char *) (p + 0x196);
    if (c == 0x38) {
        func_020e9898(*(void **) (self + 0x19c));
        *(int *) (self + 0x19c) = 0;
    } else if (c == 0x23) {
        func_020e9898(*(void **) (self + 0x198));
        *(int *) (self + 0x198) = 0;
    }
    if (data_ov004_02256308[c].flag != 0) {
        func_02055008(p + 0xb0);
    } else {
        func_0205502c(p + 0xb0);
    }
    *(int *) (p + 0x18) = 0;
    *(int *) (p + 0x1c) = 0;
    func_02004280(p + 0x24);
    zero = 0;
    *(signed char *) (p + 0x196) = (signed char) ~zero;
    *(short *) (p + 0x192) = (short) zero;
    *(int *) (p + 0x198) = zero;
    *(short *) (p + 0x168) = (short) zero;
    *(short *) (p + 0x172) = 0x19;
    func_0209d090(p + 0x288);
    func_0209d200(self + 0x180, p + 0x284);
    *(int *) (p + 0x2d4) = 0;
}

void *func_ov004_0223eba4(char *self)
{
    // DECLS
    // ENDDECLS
    func_020ee660(self);
    *(void **) (self) = &data_020da13c;
    *(void **) (self) = &data_ov004_022562c0;
    __cxa_vec_ctor(self + 0x50, 0x4, 0x4c, ((void (*)(void *)) func_02089b50), ((void (*)(void *)) func_02089b38));
    func_0209d2b8(self + 0x180);
    return self;
}

void *func_ov004_0223eb64(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_022562c0;
    func_0209d2b4(self + 0x180);
    __cxa_vec_cleanup(self + 0x50, 0x4, 0x4c, ((void (*)(void *)) func_02089b38));
    *(void **) (self) = &data_020da13c;
    func_020ee62c(self);
    return self;
}

void *func_ov004_0223eb1c(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_022562c0;
    func_0209d2b4(self + 0x180);
    __cxa_vec_cleanup(self + 0x50, 0x4, 0x4c, ((void (*)(void *)) func_02089b38));
    *(void **) (self) = &data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}

void *func_ov004_0223eb04(void *arg)
{
    func_020565ec(arg);
    *(void **) arg = &data_ov004_022562b0;
    return arg;
}

void *func_ov004_0223eaec(void *arg)
{
    *((void **) arg) = &data_ov004_022562b0;
    func_02056578(arg);
    return arg;
}

void *func_ov004_0223eacc(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_022562b0);
    func_02056578(obj);
    func_020edb3c(obj);
    return obj;
}

int func_ov004_0223ea78(void)
{
    unsigned char d[4];
    unsigned char m;
    func_0209def4(d);
    m = d[1];
    if (m >= 4 && m <= 7) {
        return 2;
    }
    if (m >= 8 && m <= 0xf) {
        return 4;
    }
    if (m == 0x10) {
        return 8;
    }
    if ((unsigned char) (m + 0xef) <= 1) {
        return 0x10;
    }
    if (m >= 0x13 && m <= 0x16) {
        return 0x20;
    }
    return 1;
}
