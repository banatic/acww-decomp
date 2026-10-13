/* func_020946ec @ 0x020946ec, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O2,s
 */

#include "types.h"

typedef struct {
    char pad_00[4];
    int unk_04;
    int unk_08;
    int unk_0C;
} Inner2;

typedef struct {
    Inner2 *unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
} Pointed;

typedef struct {
    char pad_00[0x18];
    Pointed *unk_18;
    char pad2[4];
    int unk_20;
    int unk_24;
    int unk_28;
    char pad_2C[0x10];
    u16 unk_3C;
    u16 unk_3E;
    u16 unk_40;
} UnkStruct_020946ec_2;

typedef struct {
    char pad_00[4];
    u8 raw[4];
    char pad2[4];
    UnkStruct_020946ec_2 *unk_0C;
} UnkStruct_020946ec;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    short unk_0C;
} UnkStruct_020946ec_3;

extern UnkStruct_020946ec_3 data_021d5658;
extern u8 data_021d52d8[];
extern int func_02090db0(void *obj);
extern void func_020ea6e0(void *a, int b);
extern void MI_CpuCopy8(const void *src, void *dest, u32 size);

void func_020946ec(UnkStruct_020946ec *self)
{
    u8 buf[4];
    int vals[3];
    u8 *p;
    u8 *q;
    int count;
    UnkStruct_020946ec_3 *dp;
    UnkStruct_020946ec_2 *inner;

    dp = &data_021d5658;
    p = (u8 *) self + 4;
    q = buf;
    count = 4;
    do {
        *q++ = *p++;
        count--;
    } while (count != 0);
    vals[0] = 0;
    vals[1] = 0xb50;
    vals[2] = 0xb50;
    inner = self->unk_0C;
    inner->unk_20 = dp->unk_00 + inner->unk_18->unk_00->unk_04;
    inner->unk_24 = dp->unk_04 + inner->unk_18->unk_00->unk_08;
    inner->unk_28 = dp->unk_08 + inner->unk_18->unk_00->unk_0C;
    func_02090db0(self->unk_0C);
    func_020ea6e0(vals, dp->unk_0C);
    {
        int v0 = vals[0];
        int v1 = vals[1];
        int v2 = vals[2];
        inner = self->unk_0C;
        inner->unk_3C = (u16) v0;
        inner->unk_3E = (u16) v1;
        inner->unk_40 = (u16) v2;
    }
    MI_CpuCopy8(dp, &data_021d52d8[buf[0] * 0x1c], 0x1c);
}
