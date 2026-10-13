/* func_02012d84 @ 0x02012d84, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Limit {
    u32 minX;
    u32 minY;
};

struct UnkStruct_02012d84 {
    u8 pad_00[0x1c];
    u32 unk_1C;
    u32 unk_20;
    u8 pad_24[0x64];
    u32 unk_88;
    u32 unk_8C;
    u32 unk_90;
};

struct TableEntry {
    u32 a;
    u32 b;
};

extern struct TableEntry data_021c172c[];

extern void func_020138a8(void *, void *, void *, void *);
extern void func_0204f818(u32 *, u32 *, void *);
extern int func_0204ed58(void *, u32, u32);
extern void func_0204f794(void *, u32, u32);
extern int func_02078ec0(u32, u32, void *);
extern void func_02012e58(void *, void *);
extern void func_02013440(void *);

int func_02012d84(void *a0, void *a1, struct Limit *a2, void *a3)
{
    struct UnkStruct_02012d84 *self = (struct UnkStruct_02012d84 *) a0;

    func_020138a8(a0, a1, a2, a3);

    if (self->unk_90 < 4) {
        u32 idx = self->unk_90;
        u32 step0;
        u32 step1;
        struct TableEntry *e;
        u32 local0;
        u32 local1;
        int flag;

        e = &data_021c172c[idx];
        step0 = e->a;
        step1 = e->b;
        local0 = 0;
        local1 = 0;

        func_0204f818(&local0, &local1, a1);

        while (local0 < a2->minX && local1 < a2->minY) {
            local0 += step0;
            local1 += step1;

            flag = (self->unk_1C == local0 && self->unk_20 == local1) ? 1 : 0;

            if (flag || func_0204ed58(a3, local0, local1) != 0) {
                func_0204f794(a1, local0, local1);
                func_02012e58(self, a1);
                break;
            }

            if (func_02078ec0(local0, local1, a3) != 0) {
                func_0204f794(a1, local0, local1);
                break;
            }
        }
    } else {
        func_02013440(self);
        self->unk_88 = 0;
        self->unk_8C = 2;
        func_02012e58(self, a1);
    }

    return 0;
}
