/* func_ov134_022995d4 @ 0x022995d4, 0xe0 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    char pad_00[0xa4];
    u8 unk_A4;
    char pad_A5[0x84c - 0xa5];
    char unk_84C;
    char pad_84D[0x2870 - 0x84d];
    char unk_2870;
    char pad_2871[0x288c - 0x2871];
    u16 unk_288C;
    u16 unk_288E;
    char pad_2890[0x28ae - 0x2890];
    u16 unk_28AE;
} UnkStruct_022995d4;

extern void MIi_CpuCopy16(void *src, void *dst, int n);
extern int func_020b9b6c(void *a, void *b, int c, int d);

void func_ov134_022995d4(UnkStruct_022995d4 *self, int t)
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

    MIi_CpuCopy16(&self->unk_2870, (char *) self + 0x2890, 0x20);
    c1 = self->unk_288C;
    r1 = (u8) (c1 & 0x1f);
    g1 = (u8) ((c1 & 0x3e0) >> 5);
    b1 = (u8) ((c1 & 0x7c00) >> 10);
    d = 3 - t;
    c2 = self->unk_288E;
    r = (u8) (((u8) (c2 & 0x1f) * t + r1 * d) / 3);
    g = (u8) (((u8) ((c2 & 0x3e0) >> 5) * t + g1 * d) / 3);
    b = (u8) (((u8) ((c2 & 0x7c00) >> 10) * t + b1 * d) / 3);
    self->unk_28AE = r | (g << 5) | (b << 10);
    func_020b9b6c(&self->unk_84C, (char *) self + 0x2890, self->unk_A4, 9);
}
