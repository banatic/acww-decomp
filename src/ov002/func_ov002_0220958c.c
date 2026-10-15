/* func_ov002_0220958c @ 0x0220958c, 0x100 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

struct UnkStruct_0220958c {
    u8 pad_00[0x10];
    int unk_10;
    u8 pad_14[6];
    u8 unk_1A;
    u8 unk_1B;
    u8 unk_1C;
    u8 pad_1D[7];
    void *unk_24;
};

extern void MIi_CpuClear16(u16 data, void *destp, u32 size);
extern void MIi_CpuCopy16(const void *srcp, void *destp, u32 size);

static inline void MI_CpuFill16(void *dest, u16 data, u32 size)
{
    vu16 tmp = (vu16) data;
    MIi_CpuClear16(tmp, dest, size);
}

static inline void MI_CpuCopy16(const void *src, void *dest, u32 size)
{
    MIi_CpuCopy16(src, dest, size);
}

extern void func_020029e8(int a, int b);
extern void func_020028bc(int a, int b, int c, int d);
extern void *func_02064b2c(void *a, void *g, int c, int d);
extern int func_02002b40(void *n, int a, int b, int c);
extern void func_020e993c(void *g, void *n);
extern void *data_021fbe94;

void func_ov002_0220958c(struct UnkStruct_0220958c *self)
{
    int i;
    int rows;
    int k;
    void *g;
    char *n;
    u16 tmp;
    u16 *src;
    u16 *dst;
    char *s;
    char *d;

    func_020029e8(self->unk_1A, self->unk_10);
    func_020028bc(self->unk_1A, 0, 0, 0);
    g = data_021fbe94;
    n = (char *) func_02064b2c(self->unk_24, g, -4, 0);
    if (self->unk_1C != 5) {
        tmp = *(u16 *) (n + 0x22);
        src = (u16 *) (n + 0x280);
        dst = (u16 *) (n + (self->unk_1C << 7));
        dst[0] = src[0];
        dst[1] = src[1];
        dst[0xf] = src[0xf];
        dst[0x10] = src[0x10];
        MI_CpuCopy16(n + 0x2c0, n + ((self->unk_1C * 2 + 1) << 6), 0x40);
        k = self->unk_1C;
        MI_CpuFill16(n + ((k * 2 + 2) << 6), tmp, (5 - k) << 7);
    }
    if (self->unk_1B != 0xd) {
        d = n + (self->unk_1B + 1) * 2;
        s = n + 0x1c;
        rows = self->unk_1C * 2 + 2;
        MI_CpuCopy16(s, d, 0x1e);
        d += 0x42;
        s += 0x42;
        for (i = 1; i < rows - 1; i++) {
            MI_CpuCopy16(s, d, 0x1e);
            d += 0x40;
            s += 0x40;
        }
        MI_CpuCopy16(s - 2, d - 2, 0x1e);
    }
    func_02002b40(n, self->unk_1A, 0x800, 0);
    func_020e993c(g, n);
}
