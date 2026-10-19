/* func_ov002_022096d8 @ 0x022096d8, 0x34 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022096d8 {
    u8 pad_00[0x17];
    u8 unk_17;
};

extern void func_ov002_02208a0c(struct UnkStruct_022096d8 *self, int bit);
extern int func_ov002_02208a14(struct UnkStruct_022096d8 *self, int bit);
extern void func_ov002_02208a04(struct UnkStruct_022096d8 *self, int bit);
extern void func_0200467c(int cmd);

void func_ov002_022096d8(struct UnkStruct_022096d8 *self, int flag)
{
    self->unk_17 = 2;
    if (flag) {
        func_ov002_02208a0c(self, 4);
    }
    if (func_ov002_02208a14(self, 0x10)) {
        func_ov002_02208a04(self, 0x10);
    } else {
        func_0200467c(0x14);
    }
}
