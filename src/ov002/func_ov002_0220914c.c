/* func_ov002_0220914c @ 0x0220914c, 0x2a bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0220914c {
    u8 pad_00[0x1e];
    u8 unk_1E;
    u8 unk_1F;
};

extern void func_ov002_02208a0c(struct UnkStruct_0220914c *self, int bit);
extern int func_0206fe54(void);

void func_ov002_0220914c(struct UnkStruct_0220914c *self, u8 v)
{
    func_ov002_02208a0c(self, 8);
    if (func_0206fe54()) {
        self->unk_1E = 2;
    } else {
        self->unk_1E = 5;
    }
    self->unk_1F = v;
}
