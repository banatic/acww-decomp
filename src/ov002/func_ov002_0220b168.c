/* func_ov002_0220b168 @ 0x0220b168, 0x3c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0220b168 {
    u8 pad_00[0x75];
    volatile u8 unk_75;
};

extern void func_ov002_0220b2d0(struct UnkStruct_0220b168 *self, int a, int b);

int func_ov002_0220b168(struct UnkStruct_0220b168 *self)
{
    if (self->unk_75 == 0) {
        func_ov002_0220b2d0(self, 0xe, 0);
    }
    if (self->unk_75 + 1 < 3) {
        self->unk_75 = self->unk_75 + 1;
    } else {
        return 0;
    }
    return 1;
}
