/* func_01ffceb8 @ 0x01ffceb8, 0x108 bytes, ARM, module itcm
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_common_subs off

struct UnkStruct_01ffceb8 {
    unsigned char pad_00[0x51c];
    u32 idx;
};
struct UnkStruct_01ffceb8_2 {
    u32 cur;
    u16 tbl[2][0xc0];
    u16 unk_304;
    u16 unk_306;
};
struct Rec {
    int a;
    int b;
    s16 c;
    s16 d;
};
struct UnkStruct_01ffceb8_3 {
    u32 unk_00;
    u32 sel;
    struct Rec recs[2][0xc0];
    u16 pad_1208[4];
    u16 arr2[2][0xc0];
};
struct Db {
    u32 dispcnt;
    char pad_04[0x2c];
    s16 bg3pa;
    char pad_32[6];
    u32 unk_38;
    u32 unk_3C;
    char pad_40[0x10];
    u16 bldcnt;
    u16 bldalpha;
};
extern struct UnkStruct_01ffceb8 data_021f85b0;
extern u32 data_021f8ac4[];
extern struct UnkStruct_01ffceb8_2 data_021f6f70;
extern struct UnkStruct_01ffceb8_3 data_021f75b0;
void func_01ffceb8(void)
{
    volatile u16 *regs;
    volatile u16 *pltt;
    struct UnkStruct_01ffceb8_2 *p3;
    struct Rec *e;
    int val;
    int line;
    struct UnkStruct_01ffceb8_3 *s;
    regs = (volatile u16 *) 0x04000000;
    pltt = (volatile u16 *) 0x05000000;
    p3 = &data_021f6f70;
    line = regs[3] + data_021f8ac4[((volatile u32 *) (&data_021f85b0))[0x147]];
    if (line >= 0xc0) {
        line = 0xbf;
    }
    // Both arms assign the same addresses.
    if (line) {
        p3 = &data_021f6f70;
        s = &data_021f75b0;
    } else {
        p3 = &data_021f6f70;
        s = &data_021f75b0;
    }
    pltt[0x200] = p3->tbl[p3->cur][line];
    pltt[0] = p3->unk_306;
    e = &s->recs[s->sel][line];
    ((volatile struct Db *) (regs + 0x800))->bg3pa = e->c;
    val = e->a;
    ((volatile struct Db *) (regs + 0x800))->unk_38 = (u16) val;
    ((volatile struct Db *) (regs + 0x800))->unk_3C = (u16) e->b;
    if (line >= 0x97) {
        ((volatile struct Db *) (regs + 0x800))->dispcnt = ((volatile struct Db *) (regs + 0x800))->dispcnt & (~0x200);
        ((volatile struct Db *) (regs + 0x800))->bldcnt = 0x2048;
    }
    regs[0x829] = s->arr2[s->sel][line] ^ 0;
}
