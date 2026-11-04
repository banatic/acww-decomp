/* paged_choice_7: 3 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_02209114 @ 0x02209114, 0x36 bytes, Thumb
 * func_ov002_022090e4 @ 0x022090e4, 0x2e bytes, Thumb
 * func_ov002_022090b0 @ 0x022090b0, 0x34 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02209114 {
    u8 pad_00[0x1c];
    u8 unk_1C;
};

struct UnkStruct_022090e4 {
    u8 pad_00[0x1c];
    u8 unk_1C;
};

extern void func_ov002_0220914c(struct UnkStruct_02209114 *self, int v);
extern void func_ov002_02208a0c(struct UnkStruct_02209114 *self, int bit);
extern void func_0200467c(int cmd);
extern int func_ov002_02208a8c(void *self, int a, u8 b);

void func_ov002_02209114(struct UnkStruct_02209114 *self, int v, int flag)
{
    func_ov002_0220914c(self, v);
    if (flag == 0) {
        func_ov002_02208a0c(self, 0x10);
    } else if (self->unk_1C - 1 == v) {
        func_0200467c(0x2a);
    } else {
        func_0200467c(0x29);
    }
}

u8 func_ov002_022090e4(struct UnkStruct_022090e4 *self, int flag)
{
    int n = self->unk_1C - 1;

    func_ov002_0220914c((struct UnkStruct_02209114 *) self, n);
    if (flag == 0) {
        func_ov002_02208a0c((struct UnkStruct_02209114 *) self, 0x10);
    } else {
        func_0200467c(0x2a);
    }
    return n;
}

void func_ov002_022090b0(char *self, int v)
{
    func_ov002_0220914c((struct UnkStruct_02209114 *) self, v);
    if (func_ov002_02208a8c(self, *(u8 *) (self + 0x20), v) == 0xf) {
        func_0200467c(0x2a);
    } else {
        func_0200467c(0x29);
    }
}
