/* func_02012c68 @ 0x02012c68, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 x, y, z;
} Pos;

typedef struct {
    u32 a, b;
} TableEntry;

struct UnkStruct_02012c68 {
    u8 pad_00[0x1c];
    u32 unk_1C;
    u32 unk_20;
    u8 pad_24[0x64];
    u32 unk_88;
    u32 unk_8C;
    u32 unk_90;
};

extern TableEntry data_021c172c[];

extern void func_020138a8(void *, void *);
extern int func_020134f8(void *, int);
extern void func_0204f818(u32 *, u32 *, const void *);
extern int func_0204ed58(void *, u32, u32);
extern void func_0204f794(Pos *, u32, u32);
extern void func_02013440(void *);
extern void func_02012e58(void *, void *);

int func_02012c68(struct UnkStruct_02012c68 *self, Pos *a1, void *a3)
{
    func_020138a8(self, a1);

    if (self->unk_88 != 0) {
        int idx = func_020134f8(self, self->unk_88);
        u32 local0 = 0, local1 = 0;

        func_0204f818(&local0, &local1, (const void *) a1);
        local0 += data_021c172c[idx].a;
        local1 += data_021c172c[idx].b;

        if (func_0204ed58(a3, local0, local1) == 0) {
            func_0204f794(a1, local0, local1);
            func_02013440(self);
            self->unk_88 = 0;
            self->unk_8C = 2;
            func_02012e58(self, a1);
            self->unk_90 = 4;
            return 0;
        }

        func_0204f794(a1, local0, local1);
        if (local0 == self->unk_1C && local1 == self->unk_20) {
            func_02012e58(self, a1);
        }
        return 0;
    }

    func_02013440(self);
    self->unk_88 = 0;
    self->unk_8C = 2;
    func_02012e58(self, a1);
    return 0;
}
