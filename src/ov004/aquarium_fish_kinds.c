/* aquarium_fish_kinds: 10 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022370f4 @ 0x022370f4, 0x40 bytes, Thumb
 * func_ov004_02237094 @ 0x02237094, 0x60 bytes, Thumb
 * func_ov004_02236fa0 @ 0x02236fa0, 0xf4 bytes, Thumb
 * func_ov004_02236f34 @ 0x02236f34, 0x6c bytes, Thumb
 * func_ov004_02236f0c @ 0x02236f0c, 0x28 bytes, Thumb
 * func_ov004_02236e9c @ 0x02236e9c, 0x70 bytes, Thumb
 * func_ov004_02236e0c @ 0x02236e0c, 0x90 bytes, Thumb
 * func_ov004_02236cfc @ 0x02236cfc, 0x110 bytes, Thumb
 * func_ov004_02236c1c @ 0x02236c1c, 0xe0 bytes, Thumb
 * func_ov004_02236bd4 @ 0x02236bd4, 0x48 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02237094 {
    u8 pad_00[0x15c];
    int unk_15C;
    u8 pad_160[0x1e8 - 0x160];
    u8 unk_1E8;
    u8 pad_1E9[0x252 - 0x1e9];
    u8 unk_252;
    u8 pad_253[0x256 - 0x253];
    u8 unk_256;
};

struct UnkStruct_02236fa0 {
    u8 pad_00[0x158];
    int unk_158;
    int unk_15C;
    u8 pad_160[0x1a8 - 0x160];
    int unk_1A8;
    int unk_1AC;
    u8 pad_1B0[0x1c0 - 0x1b0];
    s16 unk_1C0;
    u8 pad_1C2[0x210 - 0x1c2];
    int unk_210;
    u8 pad_214[0x224 - 0x214];
    int unk_224;
    u8 pad_228[0x252 - 0x228];
    u8 unk_252;
    u8 pad_253[0x255 - 0x253];
    u8 unk_255;
    u8 unk_256;
    u8 pad_257[0x264 - 0x257];
    int unk_264;
    int unk_268;
    u8 pad_26C[0x270 - 0x26c];
    int unk_270;
};

struct UnkStruct_02236e0c {
    u8 pad_00[0x110];
    int unk_110;
    u8 pad_114[0x158 - 0x114];
    int unk_158;
    u8 pad_15C[0x1ac - 0x15c];
    int unk_1AC;
    u8 pad_1B0[0x1c0 - 0x1b0];
    s16 unk_1C0;
    u8 pad_1C2[0x20c - 0x1c2];
    int unk_20C;
    u8 unk_210;
    u8 pad_211[1];
    s16 unk_212;
    u8 pad_214[0x218 - 0x214];
    int unk_218;
    u8 unk_21C;
};

struct UnkStruct_02236c1c {
    u8 pad_00[0x110];
    int unk_110;
    u8 pad_114[0x158 - 0x114];
    int unk_158;
    u8 pad_15C[0x1a8 - 0x15c];
    int unk_1A8;
    u8 pad_1AC[0x1b0 - 0x1ac];
    int unk_1B0;
    u8 pad_1B4[0x1c0 - 0x1b4];
    u16 unk_1C0;
    u8 pad_1C2[0x208 - 0x1c2];
    s16 unk_208;
    u8 pad_20A[0x20c - 0x20a];
    int unk_20C;
    u8 pad_210[0x21c - 0x210];
    u8 unk_21C;
};

extern int func_ov004_02236464(void *self, void *buf);
extern void func_ov004_0223635c(void *self, void *buf);
extern int func_020e88dc(void *p, int a, int b);
extern int func_020ea9e4(void *a, void *b);
extern int func_0200322c(void *a, void *b);
extern int func_ov004_02239460(int a, int b);
extern int func_ov004_02239bb4(void *p, int a, int b);
extern int func_ov004_02239474(int a, int b);
extern int func_ov004_022394ac(int a, int b);
extern int _s32_div_f(int a, int b);
extern int func_ov004_02239424(void *a, void *b, void *c, int d);
extern int FX_MulFunc(int a, int b);
extern s16 FX_SinCosTable_[];
extern void func_02055dc8(void *, void *, void *);
extern void func_ov004_022354e0(void *);
extern void func_ov004_0223653c(char *arg0);

void func_ov004_02236fa0(struct UnkStruct_02236fa0 *self, int k);
void func_ov004_02236f34(char *self);
void func_ov004_02236e0c(struct UnkStruct_02236e0c *self);
void func_ov004_02236cfc(char *self);
void func_ov004_02236c1c(struct UnkStruct_02236c1c *self);

void func_ov004_022370f4(void *self)
{
    char buf[0x10];
    unsigned char *p;

    if (func_ov004_02236464(self, buf) != 0) {
        if (*((unsigned char *) self + 0x255) != 0) {
            if (*((unsigned char *) self + 0x256) != 3) {
                *((unsigned char *) self + 0x256) = 2;
            }
        } else {
            func_ov004_0223635c(self, buf);
        }
    }
}

void func_ov004_02237094(struct UnkStruct_02237094 *self)
{
    u8 st;
    u8 v;

    st = self->unk_256;
    switch (st) {
        case 1:
            func_ov004_02236fa0((struct UnkStruct_02236fa0 *) self, 0);
            v = self->unk_1E8;
            if (self->unk_252 != v && v != self->unk_15C) {
                self->unk_252 = v;
                self->unk_256 = 2;
            }
            break;
        case 2:
            func_ov004_02236fa0((struct UnkStruct_02236fa0 *) self, 1);
            break;
        case 3:
            func_ov004_02236f34((char *) self);
            break;
    }
}

void func_ov004_02236fa0(struct UnkStruct_02236fa0 *self, int k)
{
    if (self->unk_255 == 0) {
        self->unk_252 = self->unk_15C;
        self->unk_256 = 0;
    } else {
        if (self->unk_1AC > self->unk_268) {
            if (k != 0) {
                func_020e88dc(&self->unk_1AC, self->unk_268, self->unk_224 << 2);
            } else {
                func_020e88dc(&self->unk_1AC, self->unk_268, self->unk_224);
            }
        }
        if (func_020ea9e4(&self->unk_1A8, &self->unk_264) <= 0x800) {
            if (self->unk_1AC <= self->unk_268) {
                self->unk_256 = 3;
                self->unk_158 = 0;
                self->unk_270 = func_ov004_02239460(0x3c, 0x78);
            }
        } else {
            self->unk_1C0 = func_0200322c(&self->unk_1A8, &self->unk_264);
            if (k != 0) {
                func_ov004_02239bb4(&self->unk_1A8, self->unk_210 << 1, self->unk_1C0);
            } else {
                func_ov004_02239bb4(&self->unk_1A8, self->unk_210 >> 1, self->unk_1C0);
            }
        }
    }
}

void func_ov004_02236f34(char *self)
{
    // DECLS
    // ENDDECLS
    func_020e88dc(self + 0x1a8, *(int *) (self + 0x264), *(int *) (self + 0x210));
    func_020e88dc(self + 0x1b0, *(int *) (self + 0x26c), *(int *) (self + 0x210));
    if (*(int *) (self + 0x158) > *(int *) (self + 0x270)) {
        *(u8 *) (self + 0x256) = 0x0;
        *(void **) (self + 0x158) = 0x0;
        *(u8 *) (self + 0x1ee) = 0x2;
    }
}

void *func_ov004_02236f0c(char *self)
{
    // DECLS
    // ENDDECLS
    *(int *) (self + 0x1fc) = 0xc800;
    *(void **) (self + 0x200) = 0x0;
    *(int *) (self + 0x204) = 0x14a00;
    return self;
}

void func_ov004_02236e9c(char *self)
{
    u8 *st = (u8 *) (self + 0x21c);
    switch (*st) {
        case 2:
            func_ov004_02236e0c((struct UnkStruct_02236e0c *) self);
            break;
        case 4:
            func_ov004_02236cfc((char *) self);
            break;
        case 5:
            func_ov004_02236c1c((struct UnkStruct_02236c1c *) self);
            break;
        case 6:
            if (*(int *) (self + 0x158) >= *(u16 *) (self + 0x212)) {
                *(int *) (self + 0x158) = 0;
                *st = 2;
            }
            break;
    }
    *(int *) (self + 0x158) += 1;
}

void func_ov004_02236e0c(struct UnkStruct_02236e0c *self)
{
    self->unk_1C0 = self->unk_1C0 + func_ov004_02239474(0x5a, 0);
    self->unk_210 = func_ov004_02239460(0x14, 0x78);
    self->unk_212 = func_ov004_02239460(0x3c, 0xf0);
    self->unk_20C = _s32_div_f(func_ov004_022394ac(2, 4), 0x64);
    self->unk_158 = 0;
    self->unk_1AC = 0x700;
    self->unk_218 = 0x1000;
    self->unk_110 = self->unk_218;
    self->unk_21C = 4;
}

void func_ov004_02236cfc(char *self)
{
    // DECLS
    int v;
    // ENDDECLS

    func_ov004_02239424(self + 0x1c0, self + 0x1a8, self + 0x1fc, 0x1600);
    v = *(int *) (self + 0x20c);
    *(int *) (self + 0x1a8) += FX_MulFunc(v, FX_SinCosTable_[((int) *(u16 *) (self + 0x1c0) >> 4) << 1]);
    *(int *) (self + 0x1b0) += FX_MulFunc(v, FX_SinCosTable_[(((int) *(u16 *) (self + 0x1c0) >> 4) << 1) + 1]);
    *(s16 *) (self + 0x208) = (s16) (*(s16 *) (self + 0x208) + 0x2000);
    v = _s32_div_f(7 * v, 10);
    *(int *) (self + 0x1a8) += FX_MulFunc(v, FX_SinCosTable_[((int) *(u16 *) (self + 0x208) >> 4) << 1]);
    *(int *) (self + 0x1b0) += FX_MulFunc(v, FX_SinCosTable_[((int) *(u16 *) (self + 0x208) >> 4) << 1]);
    if (*(int *) (self + 0x158) >= *(u8 *) (self + 0x210)) {
        *(int *) (self + 0x158) = 0;
        *(u8 *) (self + 0x21c) = 5;
        *(int *) (self + 0x218) >>= 1;
        *(int *) (self + 0x110) = *(int *) (self + 0x218);
    }
}

void func_ov004_02236c1c(struct UnkStruct_02236c1c *self)
{
    int v;
    int w;

    v = self->unk_20C - (self->unk_158 << 3);
    if (v < 0) {
        v = 0;
        self->unk_158 = 0;
        self->unk_110 = 0;
        self->unk_21C = 6;
    }
    self->unk_1A8 = self->unk_1A8 + FX_MulFunc(v, FX_SinCosTable_[(self->unk_1C0 >> 4) * 2]);
    self->unk_1B0 = self->unk_1B0 + FX_MulFunc(v, FX_SinCosTable_[(self->unk_1C0 >> 4) * 2 + 1]);
    self->unk_208 = self->unk_208 + 0x2000;
    w = _s32_div_f(v * 7, 0xa);
    self->unk_1A8 = self->unk_1A8 + FX_MulFunc(w, FX_SinCosTable_[((u16) self->unk_208 >> 4) * 2]);
    self->unk_1B0 = self->unk_1B0 + FX_MulFunc(w, FX_SinCosTable_[((u16) self->unk_208 >> 4) * 2]);
}

void func_ov004_02236bd4(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self + 0x50) = self;
    *(u8 *) (self + 0x1e8) = *(int *) (self + 0x15c);
    *(u8 *) (self + 0x1e9) = *(int *) (self + 0x15c);
    *(u8 *) (self + 0x1c8) = 0x1;
    func_ov004_022354e0(self);
    func_02055dc8(self + 0x64, (void *) func_ov004_0223653c, self);
}
