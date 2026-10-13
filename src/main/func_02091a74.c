/* func_02091a74 @ 0x02091a74, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02091a74 {
    u8 pad_00[0x10];
    short unk_10;
};

struct Blk {
    u8 v[4];
};

struct UnkStruct_02091a74_2 {
    u8 data[0x1c];
};

extern struct UnkStruct_02091a74 data_021d5658;
extern struct UnkStruct_02091a74_2 data_021d52d8[];
extern char data_020d1828[];
extern char data_020d1834[];
extern char data_020d1744[];

extern void func_02094c38(void *a, void *b, void *c);
extern void MI_CpuCopy8(void *a, void *b, int c);

void func_02091a74(void *self)
{
    struct Blk buf;
    struct UnkStruct_02091a74 *gp = (struct UnkStruct_02091a74 *) &data_021d5658;

    buf = *(struct Blk *) ((u8 *) self + 4);

    func_02094c38(self, gp->unk_10 != 3 ? data_020d1828 : data_020d1834, data_020d1744);

    MI_CpuCopy8(gp, &data_021d52d8[buf.v[0]], 28);
}