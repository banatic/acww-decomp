/* taxi_2: 10 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_022738d8 @ 0x022738d8, 0x10 bytes, Thumb
 * func_ov068_02273860 @ 0x02273860, 0x78 bytes, Thumb
 * func_ov068_022737e4 @ 0x022737e4, 0x7c bytes, Thumb
 * func_ov068_02273764 @ 0x02273764, 0x80 bytes, Thumb
 * func_ov068_022736d8 @ 0x022736d8, 0x8c bytes, Thumb
 * func_ov068_0227359c @ 0x0227359c, 0x13c bytes, Thumb
 * func_ov068_0227356c @ 0x0227356c, 0x30 bytes, Thumb
 * func_ov068_02273510 @ 0x02273510, 0x5c bytes, Thumb
 * func_ov068_02273338 @ 0x02273338, 0x1d8 bytes, Thumb
 * func_ov068_022732bc @ 0x022732bc, 0x7c bytes, Thumb
 */

#include "types.h"

struct UnkStruct_022738d8 {
    char pad_00[0x1c];
    void (*func)(void *);
    char pad_20[0x70];
    char flag;
};

typedef struct UnkStruct_022736d8 {
    unsigned char pad_00[0xec];
    unsigned char sub[0x148 - 0xec];
    int unk_148;
    unsigned char pad_14C[0x59c - 0x14c];
    unsigned short unk_59C;
    unsigned short unk_59E;
    unsigned short unk_5A0;
} UnkStruct_022736d8;

struct UnkStruct_0227359c;

struct UnkStruct_0227359c {
    u8 pad_00[0xec];
    u8 unk_EC[0x5c];
    void *unk_148;
    u8 pad_14C[0x144];
    u8 unk_290[8];
    u32 unk_298;
    u8 pad_29C[0xc];
    u32 *unk_2A8;
    u8 pad_2AC[4];
    u8 unk_2B0[8];
    u32 unk_2B8;
    u8 pad_2BC[0xc];
    u32 *unk_2C8;
    u8 pad_2CC[4];
    u8 unk_2D0[0x160];
    u8 unk_430;
    u8 pad_431[3];
    u8 unk_434[0xb8];
    u8 unk_4EC[0xae];
    s16 unk_59A;
    s16 unk_59C;
    s16 unk_59E;
    s16 unk_5A0;
};

typedef struct UnkStruct_022732bc {
    char pad_00[0xec];
    char unk_EC[0xa4];
    unsigned int unk_190;
    char pad_194[0x10];
    char unk_1A4[1];
    char pad_1A5[0x290 - 0x1a5];
    char unk_290[1];
    char pad_291[0x298 - 0x291];
    unsigned int unk_298;
} UnkStruct_022732bc;

extern void func_ov068_022738e8(void *state);
extern void *func_ov004_0222c87c(void *);
extern void func_020565c8(void *);
extern void *func_02055210(void *);
extern int func_ov004_0222c548(void *);
extern void func_ov004_0222c398(void *);
extern char data_ov068_022778f4[];
extern void func_ov004_0222c394(void *p);
extern int func_ov004_0222c538(void *p);
extern void *func_020551e0(void *p);
extern void *func_020565b0(void *p);
extern void *func_ov004_0222c7a0(void *p);
extern void func_020edf54(void *);
extern UnkStruct_022736d8 *data_ov068_022787fc;
extern void func_02055dc8(void *p, void (*fn)(void *), UnkStruct_022736d8 *self);
extern unsigned short func_02057a50(void *object, const char *name);
extern char data_ov068_02277988[];
extern char data_ov068_02277990[];
extern char data_ov068_02277998[];
extern int func_ov068_02273230(UnkStruct_022736d8 *self, int a);
extern void func_02004658(int id);
extern void func_ov068_022731b4(struct UnkStruct_0227359c *self);
extern void func_02056ffc(void *p);
extern void func_02055124(void *p);
extern int func_ov051_02260474(void);
extern unsigned int func_ov051_02260490(void);
extern void func_ov068_02272fe8(struct UnkStruct_0227359c *self, u8 kind, void *a, void *b, int c, int d, int e, int f);
extern void NNS_G3dMdlSetMdlAlpha(void *p, int a, u8 b);
extern void func_0205510c(void *, int);
extern void func_ov004_0222c598(void *p);
extern void func_ov004_0222c5b4(void *a, void *b);
extern void func_02004644(void *addr, int val);
extern int func_ov004_0222c5c8(void *self, void *data);
extern int func_ov004_0222c3c4(void *ptr, int flags);
extern int func_02055140(void *ptr, void *g);
extern void func_02055060(void *ptr, int val, int mode, int size, int arg4, int arg5);
extern void func_02055050(void *ptr);
extern int func_ov004_0222c3a4(void *ptr, int flags);
extern int func_ov004_0222c3b4(void *ptr, int flags);
extern int func_0205650c(void *ptr, int val, void *g);
extern void func_02056478(void *ptr, int val, int mode, int size, int arg4);
extern int func_02055e00(void *ptr);
extern void func_020563dc(void *ptr, int val);
extern int func_ov004_0222c62c(void *data, void *p1, void *p2, void *p3);
extern unsigned char data_ov068_0227795c;
extern unsigned char data_ov068_02277968;
extern unsigned char data_ov068_02277978;
extern void *data_021c9b24;
extern void func_02056440(void *p, int a, int b, void *c, int d, int e);

void func_ov068_02273338(void *self);

void func_ov068_022738d8(struct UnkStruct_022738d8 *self)
{
    self->func = func_ov068_022738e8;
    self->flag = 2;
}

void *func_ov068_02273860(void *self)
{
    func_ov004_0222c87c(self);
    *(void **) self = data_ov068_022778f4;
    func_020565c8((char *) self + 0x290);
    func_020565c8((char *) self + 0x2b0);
    func_02055210((char *) self + 0x2d0);
    func_ov004_0222c548((char *) self + 0x388);
    func_ov004_0222c398((char *) self + 0x42c);
    func_02055210((char *) self + 0x434);
    func_ov004_0222c548((char *) self + 0x4ec);
    func_ov004_0222c398((char *) self + 0x590);
    return self;
}

void *func_ov068_022737e4(void *arg)
{
    char *obj = (char *) arg;
    *(void **) obj = (void *) ((unsigned char *) data_ov068_022778f4);
    func_ov004_0222c394(obj + 0x590);
    func_ov004_0222c538(obj + 0x4ec);
    func_020551e0(obj + 0x434);
    func_ov004_0222c394(obj + 0x42c);
    func_ov004_0222c538(obj + 0x388);
    func_020551e0(obj + 0x2d0);
    func_020565b0(obj + 0x2b0);
    func_020565b0(obj + 0x290);
    func_ov004_0222c7a0(arg);
    return arg;
}

void *func_ov068_02273764(void *p)
{
    *(void **) p = ((char *) data_ov068_022778f4);
    func_ov004_0222c394((char *) p + 0x590);
    func_ov004_0222c538((char *) p + 0x4ec);
    func_020551e0((char *) p + 0x434);
    func_ov004_0222c394((char *) p + 0x42c);
    func_ov004_0222c538((char *) p + 0x388);
    func_020551e0((char *) p + 0x2d0);
    func_020565b0((char *) p + 0x2b0);
    func_020565b0((char *) p + 0x290);
    func_ov004_0222c7a0(p);
    func_020edf54(p);
    return p;
}

int func_ov068_022736d8(UnkStruct_022736d8 *self)
{
    data_ov068_022787fc = self;
    func_ov068_02273338((void *) self);
    func_02055dc8(self->sub, (void (*)(void *)) func_ov068_022738d8, self);
    self->unk_59C = func_02057a50((void *) (self->unk_148), (const char *) (data_ov068_02277988));
    self->unk_59E = func_02057a50((void *) (self->unk_148), (const char *) (data_ov068_02277990));
    self->unk_5A0 = func_02057a50((void *) (self->unk_148), (const char *) (data_ov068_02277998));
    func_ov068_02273230(self, 0);
    func_02004658(0x884);
    func_02004658(0x885);
    return 1;
}

int func_ov068_0227359c(struct UnkStruct_0227359c *self)
{
    int val;
    int kind;

    func_ov068_022731b4(self);
    func_02056ffc(self->unk_2B0);

    *self->unk_2C8 = self->unk_2B8;

    func_02055124(self->unk_EC);
    func_02056ffc(self->unk_290);

    *self->unk_2A8 = self->unk_298;

    if (self->unk_430 != 0) {
        func_02055124(self->unk_2D0);
    }

    val = func_ov051_02260474();
    func_ov051_02260490();

    kind = 0;
    switch (val) {
        case 0xfb:
            kind = 0;
            break;
        case 0x8d:
            kind = 1;
            break;
        case 0x8e:
            kind = 2;
            break;
        case 0x8f:
            kind = 3;
            break;
        case 0x90:
            kind = 4;
            break;
        case 0x91:
            kind = 5;
            break;
    }

    func_ov068_02272fe8(self, (u8) kind, self->unk_434, self->unk_4EC, 0, 0x1000, 0, 0);

    func_02055124(self->unk_434);

    NNS_G3dMdlSetMdlAlpha(self->unk_148, self->unk_59C, (u8) self->unk_59A);
    NNS_G3dMdlSetMdlAlpha(self->unk_148, self->unk_59E, (u8) self->unk_59A);
    NNS_G3dMdlSetMdlAlpha(self->unk_148, self->unk_5A0, (u8) self->unk_59A);

    return 1;
}

int func_ov068_0227356c(void *self)
{
    func_0205510c((char *) self + 0xec, 0);
    func_0205510c((char *) self + 0x2d0, 0);
    func_0205510c((char *) self + 0x434, 0);
    return 1;
}

int func_ov068_02273510(void *p)
{
    (*(int *) &data_ov068_022787fc) = 0;
    func_ov004_0222c598(p);
    func_ov004_0222c5b4((char *) p + 0x388, (char *) p + 0x42c);
    func_ov004_0222c5b4((char *) p + 0x4ec, (char *) p + 0x590);
    func_02004644((char *) 0x884, 1);
    func_02004644((char *) 0x885, 1);
    return 1;
}

void func_ov068_02273338(void *self)
{
    char *b = (char *) self;

    func_ov004_0222c5c8(b, &data_ov068_0227795c);

    if (func_ov004_0222c3c4(b + 0x1a4, 0) && func_02055140(b + 0xec, data_021c9b24)) {
        func_02055060(b + 0xec, func_ov004_0222c3c4(b + 0x1a4, 0), 0, 0x1000, 0, 0);
        func_02055050(b + 0xec);
    }

    if (func_ov004_0222c3a4(b + 0x1a4, 0) && func_0205650c(b + 0x2b0, *(int *) (b + 0x148), data_021c9b24)) {
        func_02056478(b + 0x2b0, func_ov004_0222c3a4(b + 0x1a4, 0), 0, 0x1000, 0);
        func_020563dc(b + 0x2b0, func_02055e00(b + 0xec));
    }

    if (func_ov004_0222c3b4(b + 0x1a4, 0) && func_0205650c(b + 0x290, *(int *) (b + 0x148), data_021c9b24)) {
        func_02056478(b + 0x290, func_ov004_0222c3b4(b + 0x1a4, 0), 0, 0x1000, 0);
        func_020563dc(b + 0x290, func_02055e00(b + 0xec));
    }

    func_ov004_0222c62c(&data_ov068_02277968, b + 0x2d0, b + 0x388, b + 0x42c);

    if (func_ov004_0222c3c4(b + 0x388, 0) && func_02055140(b + 0x2d0, data_021c9b24)) {
        func_02055060(b + 0x2d0, func_ov004_0222c3c4(b + 0x388, 0), 1, 0x1000, 0, 0);
        func_02055050(b + 0x2d0);
    }

    func_ov004_0222c62c(&data_ov068_02277978, b + 0x434, b + 0x4ec, b + 0x590);

    if (func_ov004_0222c3c4(b + 0x4ec, 0) && func_02055140(b + 0x434, data_021c9b24)) {
        func_02055060(b + 0x434, func_ov004_0222c3c4(b + 0x4ec, 0), 0, 0x1000, 0, 0);
        func_02055050(b + 0x434);
    }
}

void func_ov068_022732bc(UnkStruct_022732bc *self, void *r4)
{
    int tmp1, tmp2, tmp3;
    unsigned int local0, local1;

    tmp1 = func_ov004_0222c3c4(&self->unk_1A4, 0);
    local0 = (self->unk_190 << 4) >> 16;
    local1 = 0;
    func_02055060(&self->unk_EC, tmp1, (int) r4, 0x1000, local0, local1);

    tmp2 = func_02055e00(&self->unk_EC);
    tmp3 = func_ov004_0222c3b4(&self->unk_1A4, 0);
    local0 = 0x1000;
    local1 = (self->unk_298 << 4) >> 16;
    func_02056440(&self->unk_290, tmp2, tmp3, r4, local0, local1);
}
