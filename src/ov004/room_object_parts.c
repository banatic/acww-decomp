/* room_object_parts: 12 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220d280 @ 0x0220d280, 0x10 bytes, Thumb
 * func_ov004_0220d268 @ 0x0220d268, 0x18 bytes, Thumb
 * func_ov004_0220d258 @ 0x0220d258, 0x10 bytes, Thumb
 * func_ov004_0220d220 @ 0x0220d220, 0x38 bytes, Thumb
 * func_ov004_0220d208 @ 0x0220d208, 0x18 bytes, Thumb
 * func_ov004_0220d150 @ 0x0220d150, 0xb8 bytes, Thumb
 * func_ov004_0220d140 @ 0x0220d140, 0x10 bytes, Thumb
 * func_ov004_0220d110 @ 0x0220d110, 0x30 bytes, Thumb
 * func_ov004_0220d0f4 @ 0x0220d0f4, 0x1c bytes, Thumb
 * func_ov004_0220d0a0 @ 0x0220d0a0, 0x54 bytes, Thumb
 * func_ov004_0220d058 @ 0x0220d058, 0x48 bytes, Thumb
 * func_ov004_0220d030 @ 0x0220d030, 0x28 bytes, Thumb
 */

#include "types.h"

struct _S {
    unsigned char pad_00[0x18];
    unsigned char count;
};

struct UnkStruct_0220d150 {
    char pad_00[0x14];
    signed char c;
    char pad_15[3];
    struct _S *unk_18;
};

extern void func_020b3740(char *self);
extern void func_020b373c(void *object);
extern int func_02057a50(void *a, const char *name);
extern void func_020b3720(void *self, void *c);
extern int func_020b3670(int a, int b, int c, int d, int e);
extern void func_020b36c8(struct UnkStruct_0220d150 *self);
extern void *func_020b3658(struct UnkStruct_0220d150 *self);
extern void NNSi_G3dModifyMatFlag(struct _S *a, int b, int c);
extern int func_020b365c(void *a, int b, int c);
extern void NNS_G3dMdlSetMdlEmi(struct _S *a, int b, int c);
extern int data_027e0148;
extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern int data_ov004_0224fdf8[];

int func_ov004_0220d140(void);

void func_ov004_0220d280(unsigned char *p, unsigned char v, int f)
{
    if (f) {
        p[1] = v;
    } else {
        p[0] = v;
        p[1] = p[0];
    }
}

char *func_ov004_0220d268(char *self)
{
    func_020b3740(self);
    *(signed char *) (self + 0x14) = -1;
    *(int *) (self + 0x18) = 0;
    return self;
}

int func_ov004_0220d258(int arg)
{
    func_020b373c((void *) arg);
    return arg;
}

int func_ov004_0220d220(unsigned char *self, void *a, void *b, void *c)
{
    if (a != 0) {
        *(signed char *) (self + 0x14) = func_02057a50(a, (const char *) (b));
        if (*(signed char *) (self + 0x14) != -1) {
            func_020b3720(self, c);
            *(void **) (self + 0x18) = a;
            return 1;
        }
    }
    return 0;
}

int func_ov004_0220d208(int a, int b, int c, int d)
{
    return func_020b3670(a, b, c, d, 0x800);
}

void func_ov004_0220d150(struct UnkStruct_0220d150 *self)
{
    int i;
    int v6;
    int v7;
    int v8;
    int v9;
    int v10;
    int value;
    void *o;

    if (self->c != -1) {
        func_020b36c8(self);
        o = func_020b3658(self);
        if (o != 0) {
            NNSi_G3dModifyMatFlag(self->unk_18, 1, 0x400);
            v6 = func_ov004_0220d140();
            v7 = func_020b365c(o, ((v6 >> 10) & 0x1f) << 12, 0x1f000);
            v8 = func_020b365c(o, (v6 & 0x1f) << 12, 0x1f000);
            v9 = func_020b365c(o, ((v6 >> 5) & 0x1f) << 12, 0x1f000);
            v10 = ((v7 >> 12) << 10) | ((v8 >> 12) | ((v9 >> 12) << 5));
            v7 = (unsigned short) v10;
            for (i = 0; i < self->unk_18->count; i++) {
                if (i == self->c) {
                    value = v7;
                } else {
                    value = v6;
                }
                NNS_G3dMdlSetMdlEmi(self->unk_18, i, value);
            }
        } else {
            NNSi_G3dModifyMatFlag(self->unk_18, 0, 0x400);
        }
    }
}

int func_ov004_0220d140(void)
{
    return (int) ((unsigned int) (((int) ((unsigned int) (*(int *) ((char *) ((int) &data_027e0148) + (24))) >> 16) << 16)) >>
                  16);
}

void *func_ov004_0220d110(char *self)
{
    // DECLS
    // ENDDECLS
    __cxa_vec_ctor(self, 0x3, 0x1c, ((void (*)(void *)) func_ov004_0220d268), ((void (*)(void *)) func_ov004_0220d258));
    *(u8 *) (self + 0x54) = 0x0;
    return self;
}

void *func_ov004_0220d0f4(char *self)
{
    // DECLS
    // ENDDECLS
    __cxa_vec_cleanup(self, 0x3, 0x1c, ((void (*)(void *)) func_ov004_0220d258));
    return self;
}

int func_ov004_0220d0a0(char *self, int a1, int a2)
{
    unsigned i;
    u8 *flag;
    int v;

    *(u8 *) (self + 0x54) = 0;
    flag = (u8 *) (self + 0x54);
    for (i = 0; i < 3; i++) {
        v = *flag | func_ov004_0220d220((unsigned char *) (self + 0x1c * i), (void *) a1, (void *) data_ov004_0224fdf8[i], (void *) a2);
        *flag = (u8) ((v != 0) ? 1 : 0);
    }
    return *(u8 *) (self + 0x54);
}

int func_ov004_0220d058(char *self, int a1, int a2, int a3)
{
    int r = 0;
    char *p;

    if (*(u8 *) (self + 0x54) != 0) {
        for (p = self; p < self + 0x54; p += 0x1c) {
            r |= func_ov004_0220d208((int) p, a1, a2, a3);
            r = (r != 0) ? 1 : 0;
        }
    }
    return r;
}

void func_ov004_0220d030(char *self)
{
    char *end;
    if (*(u8 *) (self + 0x54) != 0) {
        end = self + 0x54;
        while (self < end) {
            func_ov004_0220d150((struct UnkStruct_0220d150 *) self);
            self += 0x1c;
        }
    }
}
