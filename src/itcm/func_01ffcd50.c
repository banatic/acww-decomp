/* func_01ffcd50 @ 0x01ffcd50, 0x168 bytes, ARM, module itcm
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_01ffcd50 {
    unsigned char pad_00[0x51c];
    u32 idx;
};
struct UnkStruct_01ffcd50_2 {
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
struct UnkStruct_01ffcd50_3 {
    u32 unk_00;
    u32 sel;
    struct Rec recs[2][0xc0];
    u16 pad_1208[4];
    u16 arr2[2][0xc0];
};

extern struct UnkStruct_01ffcd50 data_021f85b0;
extern u32 data_021f8ac4[];
extern struct UnkStruct_01ffcd50_2 data_021f6f70;
extern struct UnkStruct_01ffcd50_3 data_021f75b0;

void func_01ffcd50(void)
{
    int line;
    u32 n;
    u32 sel;
    struct Rec *rec;
    volatile u16 t;

    // The frame producer may change the bias; sample it before VCOUNT.
    n = *(volatile u32 *) &data_021f8ac4[data_021f85b0.idx];
    line = *(volatile u16 *) 0x04000006;
    line += n;
    if (line >= 0xc0) {
        line = 0xbf;
    }
    t = data_021f6f70.unk_304;
    *(volatile u16 *) 0x05000400 = t;
    n = data_021f6f70.cur;
    *(volatile u16 *) 0x05000000 = data_021f6f70.tbl[n][line];
    sel = data_021f75b0.sel;
    rec = &data_021f75b0.recs[sel][line];
    *(volatile u16 *) 0x04000030 = (u16) rec->c;
    *(volatile u32 *) 0x04000038 = rec->a;
    *(volatile u32 *) 0x0400003c = rec->b;
    if (line >= 0xa8) {
        *(volatile u32 *) 0x04000000 &= ~0xa00;
        *(volatile u16 *) 0x04000050 = 0x2040;
    } else if (line >= 0x97) {
        *(volatile u32 *) 0x04000000 = *(volatile u32 *) 0x04000000 & ~0x200;
        *(volatile u16 *) 0x04000050 = 0x2048;
    }
    *(volatile u16 *) 0x04000052 = data_021f75b0.arr2[data_021f75b0.sel][line];
}
