/* aquarium_fish: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02235698 @ 0x02235698, 0x90 bytes, Thumb
 * func_ov004_022355f4 @ 0x022355f4, 0xa4 bytes, Thumb
 * func_ov004_022354e0 @ 0x022354e0, 0x114 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02235698 {
    u8 pad_00[0x15c];
    int unk_15C;
    u8 pad_160[0x1c9 - 0x160];
    u8 unk_1C9;
    u8 pad_1CA[0x1e8 - 0x1ca];
    u8 unk_1E8;
    u8 unk_1E9;
    u8 pad_1EA[0x1f0 - 0x1ea];
    u8 unk_1F0;
    u8 unk_1F1;
    u8 pad_1F2[0x1f4 - 0x1f2];
    int unk_1F4;
    int unk_1F8;
};

struct UnkStruct_022355f4 {
    u8 pad_00[0x40];
    u8 unk_40;
    u8 pad_41[0x1c0 - 0x41];
    s16 unk_1C0;
    u8 pad_1C2[0x1f0 - 0x1c2];
    u8 unk_1F0;
    u8 pad_1F1[0x22f - 0x1f1];
    u8 unk_22F;
};

typedef struct {
    u8 unk_00, unk_01, unk_02, unk_03, unk_04, unk_05, unk_06, unk_07, unk_08, unk_09, unk_0A;
    u8 pad_0B[6];
} Rec;

typedef struct UnkStruct_022354e0 {
    u8 unk_00[0x15c];
    volatile int idx; // 0x15c
    u8 p1[0x1cc - 0x160];
    int unk_1CC; // 0x1cc
    u8 p2[0x204 - 0x1d0];
    u8 unk_204, unk_205, unk_206, unk_207; // 0x204
    u8 p3[0x210 - 0x208];
    int unk_210; // 0x210
    int unk_214;
    int unk_218;
    u8 p4[0x224 - 0x21c];
    int unk_224; // 0x224
    int unk_228;
    u8 p5[0x230 - 0x22c];
    u16 unk_230; // 0x230
} UnkStruct_022354e0;

extern int func_020e89dc(void *p, int a, int b);
extern const Rec data_ov004_02247929[];

void func_ov004_02235698(struct UnkStruct_02235698 *self)
{
    int v;
    int a;
    int b;

    v = self->unk_15C;
    a = self->unk_1E8;
    if (a != v) {
        if (((1 << (a & 0x1f)) & *(int *) ((u8 *) self + (a >> 5) * 4 + 0x1f4)) == 0) {
            self->unk_1E8 = v;
        }
        b = self->unk_1E9;
        if (((1 << (b & 0x1f)) & *(int *) ((u8 *) self + (b >> 5) * 4 + 0x1f4)) == 0) {
            self->unk_1E9 = self->unk_15C;
            self->unk_1C9 = 0;
        }
    }
    self->unk_1F4 = 0;
    self->unk_1F8 = 0;
    self->unk_1F1 = 0;
    self->unk_1F0 = 0;
}

void func_ov004_022355f4(struct UnkStruct_022355f4 *self)
{
    int v;

    if (self->unk_40 != 0) {
        return;
    }
    if (self->unk_22F != 0) {
        return;
    }
    if (self->unk_1F0 == 0) {
        return;
    }
    v = self->unk_1C0;
    if (v >= 0) {
        if (v < 0) {
            v = -v;
        }
        if (v >= 0x4000) {
            func_020e89dc(&self->unk_1C0, 0x471c, 0x222);
        } else {
            func_020e89dc(&self->unk_1C0, 0x38e4, 0x222);
        }
    } else {
        if (v < 0) {
            v = -v;
        }
        if (v <= -0x4000) {
            func_020e89dc(&self->unk_1C0, -0x471c, 0x222);
        } else {
            func_020e89dc(&self->unk_1C0, -0x38e4, 0x222);
        }
    }
}

void func_ov004_022354e0(UnkStruct_022354e0 *self)
{
    // DECLS
    // ENDDECLS
    self->unk_210 = ((int) data_ov004_02247929[self->idx].unk_02 << 12) >> 10;
    self->unk_214 = ((int) data_ov004_02247929[self->idx].unk_00 << 12) >> 12;
    self->unk_218 = ((int) data_ov004_02247929[self->idx].unk_01 << 12) >> 13;
    self->unk_204 = data_ov004_02247929[self->idx].unk_03;
    self->unk_205 = data_ov004_02247929[self->idx].unk_04;
    self->unk_206 = data_ov004_02247929[self->idx].unk_05;
    self->unk_207 = data_ov004_02247929[self->idx].unk_06;
    self->unk_230 = data_ov004_02247929[self->idx].unk_07;
    self->unk_224 = ((int) data_ov004_02247929[self->idx].unk_08 << 12) >> 10;
    self->unk_1CC = (((int) data_ov004_02247929[self->idx].unk_09 << 12) >> 5) - 0x1000;
    self->unk_228 = (((int) data_ov004_02247929[self->idx].unk_0A << 12) >> 6) - 0x1000;
}
