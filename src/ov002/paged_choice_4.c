/* paged_choice_4: 9 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_02209518 @ 0x02209518, 0x74 bytes, Thumb
 * func_ov002_022094b4 @ 0x022094b4, 0x64 bytes, Thumb
 * func_ov002_02209464 @ 0x02209464, 0x50 bytes, Thumb
 * func_ov002_02209398 @ 0x02209398, 0xcc bytes, Thumb
 * func_ov002_0220932c @ 0x0220932c, 0x6c bytes, Thumb
 * func_ov002_02209324 @ 0x02209324, 0x8 bytes, Thumb
 * func_ov002_02209318 @ 0x02209318, 0xa bytes, Thumb
 * func_ov002_022092e0 @ 0x022092e0, 0x38 bytes, Thumb
 * func_ov002_022091cc @ 0x022091cc, 0x114 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02209518 {
    u8 pad_00[8];
    int unk_08;
    int unk_0C;
    u8 pad_10[0x8];
    u8 unk_18;
    u8 unk_19;
    u8 unk_1A;
};

struct UnkStruct_022094b4 {
    u8 pad_00[8];
    int unk_08;
    int unk_0C;
    u8 pad_10[0x8];
    u8 unk_18;
    u8 unk_19;
    u8 unk_1A;
};

struct UnkStruct_02209464 {
    u8 pad_00[8];
    int unk_08;
    int unk_0C;
    u8 pad_10[0xa];
    u8 unk_1A;
};

struct UnkStruct_02209398 {
    u8 pad_00[0x18];
    u8 unk_18;
    u8 pad_19;
    u8 unk_1A;
    u8 pad_1B[6];
    volatile u8 unk_21;
};

struct UnkStruct_0220932c {
    u8 pad_00[0x18];
    u8 unk_18;
    u8 pad_19;
    u8 unk_1A;
};

struct UnkStruct_022092e0 {
    u8 pad_00[0x1b];
    u8 unk_1B;
    u8 unk_1C;
};

struct UnkStruct_022091cc {
    u8 pad_00[0x16];
    u8 unk_16;
    u8 unk_17;
    u8 pad_18[2];
    u8 unk_1A;
    u8 pad_1B[4];
    u8 unk_1F;
};

extern const int data_ov002_0220bb84[];
extern void func_ov002_0220958c(struct UnkStruct_02209518 *self);
extern void func_02002708(int v);
extern void func_ov002_02209868(struct UnkStruct_02209518 *self, int a, int b);
extern void func_ov002_0220968c(struct UnkStruct_02209518 *self, int v);
extern void func_0200277c(int v);
extern void func_ov002_022083b8(char *p, int a, int b, int c);
extern int func_ov002_02208780(char *p);
extern void func_0208f210(char *p, int a, int b);
extern void func_0208aa60(char *p, int a, int b);
extern void func_02001a7c(void);
extern unsigned char func_02002d50(unsigned int v);
extern unsigned char func_02001a30(unsigned char mask);
extern void func_02001a1c(int v);
extern int func_02002d8c(int v);
extern void func_ov002_02208558(char *p, int a, int b, int c, int d);
extern void func_ov002_02208a0c(struct UnkStruct_02209398 *self, int bit);
extern int func_ov002_0220866c(char *p, int a);
extern void func_0208a9e4(char *p, int a);
extern void func_ov002_0220851c(char *p, int a, int b, int c, int d);
extern int func_ov002_02208594(char *p, int a);
extern void func_02001a5c(void);
extern void func_ov002_02208a04(struct UnkStruct_0220932c *self, int bit);
extern int func_0207096c(void *p);
extern void func_ov002_02208df8(struct UnkStruct_022091cc *self);
extern int func_ov002_02208a14(struct UnkStruct_022091cc *self, int bit);
extern void func_ov002_02209b94(char *p, int i);
extern void func_02070a04(char *p, int a, int b);
extern void func_ov002_02208d74(struct UnkStruct_022091cc *self);

int func_ov002_02209324(u8 *p);

void func_ov002_02209518(struct UnkStruct_02209518 *self)
{
    int step;
    int d;

    if (self->unk_18 == 0) {
        func_ov002_0220958c(self);
        func_02002708(self->unk_1A);
    }
    step = data_ov002_0220bb84[self->unk_18];
    if (self->unk_19 != 0) {
        d = self->unk_08 - step;
    } else {
        d = self->unk_08 + step;
    }
    if (d > 0) {
        d = 0;
    }
    if (-d + func_ov002_02209324((u8 *) self) > 0xff) {
        d = func_ov002_02209324((u8 *) self) - 0xff;
    }
    func_ov002_02209868(self, d, self->unk_0C - step);
    self->unk_18 = self->unk_18 + 1;
    if (self->unk_18 >= 3) {
        func_ov002_0220968c(self, 3);
    }
}

void func_ov002_022094b4(struct UnkStruct_022094b4 *self)
{
    int d;

    if (self->unk_18 == 0) {
        if (self->unk_19 != 0) {
            d = self->unk_08 - 0xb;
        } else {
            d = self->unk_08 + 0xb;
        }
        if (d > 0) {
            d = 0;
        }
        if (-d + func_ov002_02209324((u8 *) self) > 0xff) {
            d = func_ov002_02209324((u8 *) self) - 0xff;
        }
        func_ov002_02209868((struct UnkStruct_02209518 *) self, d, self->unk_0C - 0xb);
        self->unk_18 = self->unk_18 + 1;
    } else {
        func_0200277c(self->unk_1A);
        func_ov002_0220968c((struct UnkStruct_02209518 *) self, 0);
    }
}

void func_ov002_02209464(struct UnkStruct_02209464 *self)
{
    int w;

    func_ov002_022083b8((char *) self + 0x3b0, self->unk_1A, -self->unk_08, -self->unk_0C);
    w = func_ov002_02208780((char *) self + 0x3b0);
    func_0208f210((char *) self + 0x26c, 0, w);
    func_0208aa60((char *) self + 0x2e4, 0, -(w >> 2));
}

void func_ov002_02209398(struct UnkStruct_02209398 *self)
{
    int t;

    if (self->unk_18 == 0) {
        func_ov002_0220958c((struct UnkStruct_02209518 *) self);
        func_02001a7c();
        func_02001a30(func_02002d50(self->unk_1A));
        func_02001a1c(-6);
        t = func_02002d8c(self->unk_1A);
        func_ov002_02208558((char *) self + 0x3b0, t, 5, 0, 0x30);
        func_02002708(self->unk_1A);
        func_ov002_02208a0c(self, 1);
        self->unk_21 = 2;
        func_ov002_02209464((struct UnkStruct_02209464 *) self);
        self->unk_18 = self->unk_18 + 1;
    } else {
        if (func_ov002_0220866c((char *) self + 0x3b0, 0)) {
            func_ov002_0220968c((struct UnkStruct_02209518 *) self, 3);
            if (self->unk_21 != 0) {
                self->unk_21 = 1;
            }
        }
        if (self->unk_21 != 0) {
            self->unk_21 = self->unk_21 - 1;
            if (self->unk_21 == 0) {
                func_0208a9e4((char *) self + 0x2e4, 0);
            }
        }
        func_ov002_02209464((struct UnkStruct_02209464 *) self);
    }
}

void func_ov002_0220932c(struct UnkStruct_0220932c *self)
{
    int t;

    if (self->unk_18 == 0) {
        t = func_02002d8c(self->unk_1A);
        func_ov002_0220851c((char *) self + 0x3b0, t, 3, 0, 0x30);
        func_ov002_02209464((struct UnkStruct_02209464 *) self);
        self->unk_18 = self->unk_18 + 1;
    }
    if (func_ov002_02208594((char *) self + 0x3b0, 0)) {
        func_02001a5c();
        func_ov002_02208a04(self, 1);
        func_0200277c(self->unk_1A);
        func_ov002_0220968c((struct UnkStruct_02209518 *) self, 0);
    } else {
        func_ov002_02209464((struct UnkStruct_02209464 *) self);
    }
}

int func_ov002_02209324(u8 *p)
{
    return (p[0x1b] + 4) << 3;
}

int func_ov002_02209318(u8 *p)
{
    return (p[0x1c] * 2 + 2) << 3;
}

void func_ov002_022092e0(struct UnkStruct_022092e0 *self)
{
    char *base;
    int best;
    int i;

    best = 0;
    i = 0;
    base = (char *) self + 0x28;
    for (; i < self->unk_1C; i++) {
        int v = func_0207096c(base + i * 0x74);
        if (v > best) {
            best = v;
        }
    }
    self->unk_1B = (u8) ((best + 7) >> 3);
}

void func_ov002_022091cc(struct UnkStruct_022091cc *self)
{
    func_ov002_02208df8(self);
    if (func_ov002_02208a14(self, 8)) {
        func_ov002_02208a04((struct UnkStruct_0220932c *) self, 8);
        func_ov002_02209b94((char *) self + 0x28 + self->unk_1F * 0x74, 0xf);
        func_02070a04((char *) self + 0x28 + self->unk_1F * 0x74, 0, 1);
    }
    switch (self->unk_17) {
        case 1:
            switch (self->unk_16) {
                case 0:
                    func_ov002_0220968c((struct UnkStruct_02209518 *) self, 1);
                    self->unk_17 = 0;
                    func_ov002_02208d74(self);
                    break;
                case 1:
                case 2:
                    self->unk_17 = 0;
                    break;
                case 3:
                    func_ov002_0220968c((struct UnkStruct_02209518 *) self, 4);
                    break;
            }
            break;
        case 2:
            switch (self->unk_16) {
                case 3:
                    func_ov002_0220968c((struct UnkStruct_02209518 *) self, 4);
                    self->unk_17 = 0;
                    break;
                case 1:
                    func_0200277c(self->unk_1A);
                    func_ov002_0220968c((struct UnkStruct_02209518 *) self, 0);
                    self->unk_17 = 0;
                    break;
                case 0:
                case 2:
                    self->unk_17 = 0;
                    break;
            }
            break;
    }
    switch (self->unk_16) {
        case 0:
        case 3:
            break;
        case 1:
            func_ov002_02209518((struct UnkStruct_02209518 *) self);
            break;
        case 4:
            func_ov002_022094b4((struct UnkStruct_022094b4 *) self);
            break;
        case 2:
            func_ov002_02209398((struct UnkStruct_02209398 *) self);
            break;
        case 5:
            func_ov002_0220932c((struct UnkStruct_0220932c *) self);
            break;
    }
}
