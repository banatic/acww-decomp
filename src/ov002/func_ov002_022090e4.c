/* func_ov002_022090e4 @ 0x022090e4, 0x2e bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022090e4 {
    u8 pad_00[0x1c];
    u8 unk_1C;
};

extern void func_ov002_0220914c(struct UnkStruct_022090e4 *self, int v);
extern void func_ov002_02208a0c(struct UnkStruct_022090e4 *self, int bit);
extern void func_0200467c(int cmd);

u8 func_ov002_022090e4(struct UnkStruct_022090e4 *self, int flag)
{
    int n = self->unk_1C - 1;

    func_ov002_0220914c(self, n);
    if (flag == 0) {
        func_ov002_02208a0c(self, 0x10);
    } else {
        func_0200467c(0x2a);
    }
    return n;
}
