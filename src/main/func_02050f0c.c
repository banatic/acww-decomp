/* func_02050f0c @ 0x02050f0c, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02051458(void *o);
extern void DC_FlushRange(int a, int b);
extern void MI_CpuCopy8(int a, int b, int c);
extern u8 data_021c8344[];
extern void (*data_020cb920[])(int, int, int);
extern void (*data_020cb938[])(int, int, int);

struct UnkStruct_02050f0c {
    u32 pad_00[6];
    u32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
    u32 unk_2C;
    u32 unk_30;
    u32 unk_34;
    u8 unk_38[0x18];
    u32 unk_50;
    u8 unk_54;
    u8 unk_55;
    u8 unk_56;
    u8 unk_57;
    u32 unk_58;
    u32 unk_5C;
    u32 unk_60;
};

void func_02050f0c(struct UnkStruct_02050f0c *o)
{
    u32 i;
    int r4;
    u32 r7;

    func_02051458(o);
    if (o->unk_5C == 0) {
        r7 = o->unk_60;
    } else {
        r7 = o->unk_5C << 5;
    }
    if (r7 > 0x400) {
        r7 = 0x400;
    }
    r4 = 0;
    if (o->unk_18 != -1) {
        r4 = o->unk_18 << 5;
    } else if (o->unk_1C != 0) {
        r4 = 0;
    }
    for (i = 0; i < o->unk_24; i++) {
        DC_FlushRange((int) data_021c8344, r7);
        if ((o->unk_50 - 2) <= 1) {
            data_020cb920[o->unk_2C]((int) data_021c8344, r4, r7);
        }
        if (o->unk_50 == 1 || o->unk_50 == 3) {
            data_020cb938[o->unk_2C]((int) data_021c8344, r4, r7);
        }
        if (o->unk_50 == 0) {
            MI_CpuCopy8((int) data_021c8344, o->unk_1C + r4, r7);
        }
        if (o->unk_55 != 0) {
            r4 += 0x400;
        } else {
            r4 += o->unk_60;
        }
    }
}
