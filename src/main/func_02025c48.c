/* func_02025c48 @ 0x02025c48, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Pair {
    u32 lo;
    u32 hi;
};

struct UnkStruct_02025c48 {
    u8 pad_00[0x830];
    u32 unk_830;
};

struct UnkStruct_02025c48_2 {
    u8 pad_00[0x100];
    struct UnkStruct_02025c48 *ptr; // 0x100
    u8 unk_104[0x1E];               // 0x104
    u8 unk_122;                     // 0x122
    u8 pad_123[0x41];               // 0x123
    u32 unk_164;                    // 0x164
};

struct UnkStruct_02025c48_3 {
    u8 *ptr;
    u8 byte;
};

extern struct Pair data_020d92f8;
extern u32 data_020d9dd4[];

extern int func_0209b914(int);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(struct UnkStruct_02025c48_2 *, u8 *, u8 *, int, int, int offset, int scale, int, int);

void func_02025c48(struct UnkStruct_02025c48_2 *a, struct UnkStruct_02025c48_3 *out)
{
    struct Pair d = data_020d92f8;
    int idx = func_0209b914(a->unk_164);
    if (idx < 7) {
        d.lo = data_020d9dd4[idx];
    }
    if (d.lo != 0) {
        int x = func_020036e8(func_0208150c(a->ptr->unk_830));
        func_0202da38(a, a->unk_104, &a->unk_122, 0x1e, x, d.lo, ((u8 *) &d)[4], 0, 0);
    }
    out->ptr = a->unk_104;
    out->byte = a->unk_122;
}
