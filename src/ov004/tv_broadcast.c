/* tv_broadcast: 29 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223adc8 @ 0x0223adc8, 0x2a bytes, Thumb
 * func_ov004_0223adb4 @ 0x0223adb4, 0x12 bytes, Thumb
 * func_ov004_0223ad7c @ 0x0223ad7c, 0x38 bytes, Thumb
 * func_ov004_0223ad64 @ 0x0223ad64, 0x18 bytes, Thumb
 * func_ov004_0223ac98 @ 0x0223ac98, 0xcc bytes, Thumb
 * func_ov004_0223ac7c @ 0x0223ac7c, 0x1a bytes, Thumb
 * func_ov004_0223ac34 @ 0x0223ac34, 0x48 bytes, Thumb
 * func_ov004_0223ac14 @ 0x0223ac14, 0x20 bytes, Thumb
 * func_ov004_0223ac0c @ 0x0223ac0c, 0x6 bytes, Thumb
 * func_ov004_0223abf0 @ 0x0223abf0, 0x1c bytes, Thumb
 * func_ov004_0223abe8 @ 0x0223abe8, 0x6 bytes, Thumb
 * func_ov004_0223abe0 @ 0x0223abe0, 0x8 bytes, Thumb
 * func_ov004_0223ab98 @ 0x0223ab98, 0x48 bytes, Thumb
 * func_ov004_0223ab7c @ 0x0223ab7c, 0x1c bytes, Thumb
 * func_ov004_0223aad4 @ 0x0223aad4, 0xa8 bytes, Thumb
 * func_ov004_0223aa30 @ 0x0223aa30, 0xa4 bytes, Thumb
 * func_ov004_0223a9e0 @ 0x0223a9e0, 0x4e bytes, Thumb
 * func_ov004_0223a9b8 @ 0x0223a9b8, 0x26 bytes, Thumb
 * func_ov004_0223a968 @ 0x0223a968, 0x50 bytes, Thumb
 * func_ov004_0223a8f0 @ 0x0223a8f0, 0x78 bytes, Thumb
 * func_ov004_0223a87c @ 0x0223a87c, 0x74 bytes, Thumb
 * func_ov004_0223a818 @ 0x0223a818, 0x64 bytes, Thumb
 * func_ov004_0223a808 @ 0x0223a808, 0x10 bytes, Thumb
 * func_ov004_0223a7f0 @ 0x0223a7f0, 0x18 bytes, Thumb
 * func_ov004_0223a7d8 @ 0x0223a7d8, 0x18 bytes, Thumb
 * func_ov004_0223a7cc @ 0x0223a7cc, 0xc bytes, Thumb
 * func_ov004_0223a7c0 @ 0x0223a7c0, 0xc bytes, Thumb
 * func_ov004_0223a7a8 @ 0x0223a7a8, 0x18 bytes, Thumb
 * func_ov004_0223a790 @ 0x0223a790, 0x18 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[8];
    long unk_08, unk_0C;
    unsigned char unk_10[0x96];
} UnkStruct_0223ac34;

typedef struct {
    unsigned char pad_00[160];
    unsigned long unk_A0;
} UnkStruct_0223ac0c;

typedef struct {
    unsigned char pad_00[166];
    unsigned short unk_A6;
} UnkStruct_0223abe8;

struct UnkStruct_0223abe0 {
    u8 pad_00[0x18];
    unsigned int lo : 12;
    unsigned int mid : 16;
    unsigned int hi : 4;
};

typedef struct {
    char b[0xa8];
} UnkStruct_0223a9b8;

typedef struct {
    unsigned char *p;
    int n;
} UnkStruct_0223a968;

typedef struct {
    u8 unk_00, unk_01, unk_02, unk_03, unk_04, unk_05, unk_06, unk_07;
} Tm;

typedef union {
    Tm t;
    u32 w[2];
} TmBuf;

typedef struct {
    u8 a, b, c, d;
} Date;

struct UnkStruct_0223a818 {
    s16 unk_00;
    u8 pad_02[0x154 - 2];
    int unk_154;
    int unk_158;
    int unk_15C;
};

extern void *func_020576cc(void *argument0);
extern void *func_02057694(void *);
extern void *func_020ea0e0(int, void *);
extern void *data_021fbe94;
extern int data_ov004_02255fe4[];
extern int func_02064328(char *, void *, int);
extern void *func_02064b2c(char *, void *, int, int);
extern void *func_021077e8(void *);
extern void *NNS_G3dGetTexPatAnmSet(void *);
extern void *func_02107bf8(void *, int);
extern int func_020575e4(void *, void *, void *, void *, void *, void *, int);
extern char data_ov004_02256074;
extern char data_ov004_02256094;
extern char data_ov004_022560b4;
extern char data_ov004_022560d0;
extern char data_ov004_022560ec;
extern char data_ov004_022560f4;
extern void func_020e9b9c(int);
extern int func_02057538(void *);
extern int func_02056f28(void *, int);
extern void func_020e9fc8(void *parameter0);
extern void __cxa_vec_ctor();
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern int func_02056064(int, int);
extern int func_020561cc(int, int);
extern void func_020e9898(void *);
extern char *func_02003ea0(void);
extern char data_ov004_02256060;
extern int data_021c9b24;
extern unsigned char data_ov004_022595b8;
extern void *func_02003e80(void *);
extern void *func_02003ec8(void *, int);
extern void func_02003e90(void *);
extern void func_ov004_0223b274(void);
extern UnkStruct_0223a968 data_ov004_02247cf4[];
extern int func_0209ded0(void);
extern void func_0209def4(void *buf);
extern void func_0209e474(TmBuf *);
extern int func_0209dc10(Date *);
extern u8 data_021f3b28[];

void func_ov004_0223ac7c(char *self);
int func_ov004_0223aa30(char *self, int ch, int prog);
int func_ov004_0223a968(void *receiver);
int func_ov004_0223a87c(void *receiver);
int func_ov004_0223a808(short *p);
unsigned long func_ov004_0223a7f0(char *self);
int func_ov004_0223a7d8(char *self);

void *func_ov004_0223adc8(char *self)
{
    func_020576cc(self + 0x10);
    *(int *) (self + 0xa0) = -1;
    *(short *) (self + 0xa4) = -1;
    *(int *) (self) = 0;
    *(short *) (self + 0xa6) = 0;
    return self;
}

void *func_ov004_0223adb4(char *self)
{
    // DECLS
    // ENDDECLS
    func_02057694(self + 0x10);
    return self;
}

void func_ov004_0223ad7c(char *self, int a1)
{
    *(int *) (self + 0xa0) = -1;
    *(short *) (self + 0xa4) = -1;
    *(void **) self = func_020ea0e0(0xe00, data_021fbe94);
    *(int *) (self + 4) = a1;
}

int func_ov004_0223ad64(unsigned int i)
{
    if (i < 0xb) {
        return data_ov004_02255fe4[i];
    }
    return data_ov004_02255fe4[0];
}

int func_ov004_0223ac98(char *self, int ch, int prog)
{
    char nameA[0x28];
    char nameB[0x28];
    int sel;
    func_ov004_0223ac7c((char *) self);
    sel = -1;
    if (ch != 0xff) {
        func_02064328(nameA, &data_ov004_02256074, ch);
        func_02064328(nameB, &data_ov004_02256094, ch);
    } else {
        sel = func_ov004_0223ad64(prog);
        func_02064328(nameA, &data_ov004_022560b4, sel);
        func_02064328(nameB, &data_ov004_022560d0, sel);
        sel = prog;
    }
    *(void **) (self + 8) = func_021077e8(func_02064b2c(nameA, *(void **) self, 4, 0));
    *(void **) (self + 0xc) = func_02107bf8(NNS_G3dGetTexPatAnmSet(func_02064b2c(nameB, *(void **) self, 4, 0)), 0);
    if (func_020575e4(self + 0x10, *(void **) (self + 4), &data_ov004_022560ec, &data_ov004_022560f4, *(void **) (self + 8),
                      *(void **) (self + 0xc), 0) != 0) {
        *(int *) (self + 0xa0) = ch;
        *(short *) (self + 0xa4) = sel;
        *(short *) (self + 0xa6) = 0;
        return 1;
    }
    return 0;
}

void func_ov004_0223ac7c(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self) != 0x0) {
        func_020e9b9c(*(int *) (self));
    }
    *(void **) (self + 0x8) = 0x0;
    *(void **) (self + 0xc) = 0x0;
}

void func_ov004_0223ac34(UnkStruct_0223ac34 *self)
{
    int v;
    if (self->unk_08 != 0 && self->unk_0C != 0) {
        func_02057538(self->unk_10);
        if (func_02056f28(self->unk_10, 0) != 0) {
            v = *(unsigned short *) ((char *) self + 0xa6) + 1;
            if (v > 0xffff) {
                *(unsigned short *) ((char *) self + 0xa6) = 0xffff;
            } else {
                *(unsigned short *) ((char *) self + 0xa6) = (unsigned short) v;
            }
        }
    }
}

void func_ov004_0223ac14(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self) != 0x0) {
        func_020e9fc8((void *) (*(int *) ((char *) (((unsigned int) (self) + (0x0))) + 0)));
        *(void **) (self) = 0x0;
    }
    *(void **) (self + 0xc) = 0x0;
    *(void **) (self + 0x8) = 0x0;
    *(void **) (self + 0x4) = 0x0;
}

unsigned long func_ov004_0223ac0c(UnkStruct_0223ac0c *p)
{
    return p->unk_A0;
}

int func_ov004_0223abf0(char *self)
{
    if ((int) func_ov004_0223ac0c((UnkStruct_0223ac0c *) self) == 0xff) {
        return *(short *) (self + 0xa4);
    }
    return -1;
}

unsigned short func_ov004_0223abe8(UnkStruct_0223abe8 *p)
{
    return p->unk_A6;
}

int func_ov004_0223abe0(struct UnkStruct_0223abe0 *self)
{
    return self->mid;
}

void *func_ov004_0223ab98(char *self)
{
    __cxa_vec_ctor(self + 0x4, 0x2, 0xa8, (void *) func_ov004_0223adc8, (void *) func_ov004_0223adb4);
    *(short *) (self) = -1;
    *(int *) (self + 0x154) = 0x0;
    *(int *) (self + 0x158) = 0x0;
    *(int *) (self + 0x15c) = 0x0;
    return self;
}

void *func_ov004_0223ab7c(char *self)
{
    // DECLS
    // ENDDECLS
    __cxa_vec_cleanup(self + 0x4, 0x2, 0xa8, ((void (*)(void *)) func_ov004_0223adb4));
    return self;
}

void func_ov004_0223aad4(char *self)
{
    void *h;
    int a;
    *(short *) self = -1;
    *(int *) (self + 0x154) = 0;
    h = func_02064b2c((char *) (&data_ov004_02256060), data_021fbe94, 4, 0);
    if (h != 0) {
        int t = (int) func_021077e8((void *) ((unsigned int *) h));
        func_02056064(t, 0);
        *(int *) (self + 0x154) = func_020561cc(t, data_021c9b24);
        func_020e9898(h);
    }
    func_ov004_0223ad7c((char *) (self + 4), *(int *) (self + 0x154));
    func_ov004_0223ad7c((char *) (self + 0xac), *(int *) (self + 0x154));
    if (data_ov004_022595b8 != 0) {
        *(int *) (self + 0x158) = (int) func_020ea0e0((int) (func_02003ea0() + 0x60), data_021fbe94);
    }
    a = func_ov004_0223a968(self);
    func_ov004_0223aa30((char *) self, a, func_ov004_0223a87c(self));
}

int func_ov004_0223aa30(char *self, int ch, int prog)
{
    int cur = *(short *) self & 1;
    signed char nxt;
    func_ov004_0223ac7c((char *) (self + 4 + cur * 0xa8));
    nxt = (*(short *) self + 1) & 1;
    if (func_ov004_0223ac98((char *) (self + 4 + nxt * 0xa8), ch, prog) != 0) {
        *(short *) self = nxt;
        if (data_ov004_022595b8 != 0 && *(void **) (self + 0x158) != 0) {
            void **p;
            if (*(void **) (self + 0x15c) != 0) {
                func_02003e80(*(void **) (self + 0x15c));
                *(void **) (self + 0x15c) = 0;
            }
            func_020e9b9c((int) (*(void **) (self + 0x158)));
            p = (void **) (self + 0x15c);
            *p = func_02003ec8(*(void **) (self + 0x158), ch);
            if (*p != 0) {
                func_02003e90(*p);
            }
        }
        return 1;
    }
    return 0;
}

void func_ov004_0223a9e0(void *self)
{
    int v = func_ov004_0223a968(self);
    if (v == 0xff) {
        int w;
        w = func_ov004_0223a87c(self);
        if (w != func_ov004_0223a7d8((char *) self)) {
            func_ov004_0223aa30((char *) self, v, w);
            func_ov004_0223b274();
        }
    } else if (v != (int) func_ov004_0223a7f0((char *) self)) {
        func_ov004_0223aa30((char *) self, v, 0xff);
        func_ov004_0223b274();
    }
}

void func_ov004_0223a9b8(char *self)
{
    if (func_ov004_0223a808((short *) self)) {
        UnkStruct_0223a9b8 *a = (UnkStruct_0223a9b8 *) (self + 4);
        func_ov004_0223ac34((UnkStruct_0223ac34 *) (&a[*(short *) self & 1]));
    }
}

int func_ov004_0223a968(void *receiver)
{
    unsigned char buf[4];
    unsigned char *rec;
    UnkStruct_0223a968 *e;
    int i;
    unsigned short key;

    e = &data_ov004_02247cf4[func_0209ded0()];
    func_0209def4(buf);
    i = e->n - 1;
    key = *(unsigned short *) buf;
    for (; i >= 0; i--) {
        rec = e->p + i * 3;
        buf[3] = rec[1];
        buf[2] = rec[2];
        if (key >= *(unsigned short *) (buf + 2)) {
            return rec[0];
        }
    }
    return 0xff;
}

int func_ov004_0223a8f0(void)
{
    TmBuf tm;
    Date d;
    tm.w[0] = 0;
    tm.w[1] = 0;
    func_0209e474(&tm);
    d.a = 1;
    d.b = 1;
    d.c = 0;
    d.d = 0;
    d.c = tm.t.unk_05;
    d.b = tm.t.unk_04;
    d.a = tm.t.unk_03;
    switch (func_0209dc10(&d)) {
        case 0:
        case 1:
        case 2:
        case 0xe:
        case 0xf:
        case 0x10:
        case 0x11:
        case 0x12:
            return 1;
        default:
            return 0;
    }
}

int func_ov004_0223a87c(void *receiver)
{
    int h = data_021f3b28[3] & 0x1f;
    if (h <= 6) {
        return 0;
    }
    if (h <= 9) {
        return 1;
    }
    if (h <= 0xf) {
        return func_ov004_0223a8f0() ? 8 : 2;
    }
    if (h <= 0x12) {
        return 3;
    }
    if (h <= 0x15) {
        return 4;
    }
    if (h <= 0x19) {
        return 5;
    }
    if (h <= 0x1c) {
        return func_ov004_0223a8f0() ? 9 : 6;
    }
    return func_ov004_0223a8f0() ? 0xa : 7;
}

void func_ov004_0223a818(struct UnkStruct_0223a818 *self)
{
    self->unk_00 = -1;
    self->unk_154 = 0;
    if ((*(u8 *) &data_ov004_022595b8) != 0) {
        if (self->unk_158 != 0) {
            if (self->unk_15C != 0) {
                func_02003e80((void *) self->unk_15C);
                self->unk_15C = 0;
            }
            func_020e9fc8((void *) self->unk_158);
            self->unk_158 = 0;
        }
    }
    func_ov004_0223ac14((char *) ((u8 *) self + 4));
    func_ov004_0223ac14((char *) ((u8 *) self + 0xac));
}

int func_ov004_0223a808(short *p)
{
    int ok = 0;
    if (*p != -1) {
        ok = 1;
    }
    return ok;
}

unsigned long func_ov004_0223a7f0(char *self)
{
    return func_ov004_0223ac0c((UnkStruct_0223ac0c *) (self + 4 + (*(short *) (self + 0x0) & 1) * 168));
}

int func_ov004_0223a7d8(char *self)
{
    return func_ov004_0223abf0((char *) (self + 4 + (*(short *) (self + 0x0) & 1) * 168));
}

int func_ov004_0223a7cc(char *self)
{
    // DECLS
    // ENDDECLS
    return *(int *) (self + 0x154);
}

int func_ov004_0223a7c0(char *self)
{
    // DECLS
    // ENDDECLS
    return *(int *) (self + 0x15c);
}

unsigned short func_ov004_0223a7a8(char *self)
{
    return func_ov004_0223abe8((UnkStruct_0223abe8 *) (self + 4 + (*(short *) (self + 0x0) & 1) * 168));
}

int func_ov004_0223a790(char *self)
{
    return func_ov004_0223abe0((struct UnkStruct_0223abe0 *) (self + 4 + (*(short *) (self + 0x0) & 1) * 168));
}
