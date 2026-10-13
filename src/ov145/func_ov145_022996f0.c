/* func_ov145_022996f0 @ 0x022996f0, 0xe0 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    char pad_00[0xb20];
    char unk_B20;
    char pad_B21[0x24c6 - 0xb21];
    char unk_24C6;
    char pad_24C7[0x24d4 - 0x24c7];
    u16 unk_24D4;
    char pad_24D6[0x24e4 - 0x24d6];
    u16 unk_24E4;
    u16 unk_24E6;
    char pad_24E8[0x2504 - 0x24e8];
    u16 unk_2504;
} UnkStruct_022996f0;

extern void MIi_CpuCopy16(void *src, void *dst, int n);
extern void func_020b9b6c(void *a, void *b, int c, int d);

void func_ov145_022996f0(UnkStruct_022996f0 *self, int t)
{
    u16 c1;
    int d;
    u8 r1;
    u8 g1;
    u8 b1;
    u16 c2;
    u8 g;
    u8 b;
    u8 r;

    MIi_CpuCopy16(&self->unk_24C6, &self->unk_24E6, 0x20);
    c1 = self->unk_24D4;
    r1 = (u8) (c1 & 0x1f);
    g1 = (u8) ((c1 & 0x3e0) >> 5);
    b1 = (u8) ((c1 & 0x7c00) >> 10);
    d = 3 - t;
    c2 = self->unk_24E4;
    r = (u8) (((u8) (c2 & 0x1f) * t + r1 * d) / 3);
    g = (u8) (((u8) ((c2 & 0x3e0) >> 5) * t + g1 * d) / 3);
    b = (u8) (((u8) ((c2 & 0x7c00) >> 10) * t + b1 * d) / 3);
    self->unk_2504 = r | (g << 5) | (b << 10);
    func_020b9b6c(&self->unk_B20, &self->unk_24E6, 4, 3);
}
