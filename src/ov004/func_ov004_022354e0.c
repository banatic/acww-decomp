/* func_ov004_022354e0 @ 0x022354e0, 0x114 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 unk_00, unk_01, unk_02, unk_03, unk_04, unk_05, unk_06, unk_07, unk_08, unk_09, unk_0A;
    u8 pad_0B[6];
} Rec;

extern const Rec data_ov004_02247929[];

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
