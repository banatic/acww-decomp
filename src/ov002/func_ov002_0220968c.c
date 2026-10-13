/* func_ov002_0220968c @ 0x0220968c, 0x4a bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0220968c {
    u8 pad_00[0x16];
    u8 unk_16;
    u8 pad_17;
    u8 unk_18;
};

extern int func_ov002_02208a14(struct UnkStruct_0220968c *self, int bit);
extern void func_ov002_02208a04(struct UnkStruct_0220968c *self, int bit);

void func_ov002_0220968c(struct UnkStruct_0220968c *self, int mode)
{
    if (func_ov002_02208a14(self, 2) && mode == 1) {
        mode = 2;
        func_ov002_02208a04(self, mode);
    } else if (func_ov002_02208a14(self, 4) && mode == 4) {
        mode = 5;
        func_ov002_02208a04(self, 4);
    }
    self->unk_16 = mode;
    self->unk_18 = 0;
}
