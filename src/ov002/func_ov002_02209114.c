/* func_ov002_02209114 @ 0x02209114, 0x36 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02209114 {
    u8 pad_00[0x1c];
    u8 unk_1C;
};

extern void func_ov002_0220914c(struct UnkStruct_02209114 *self, int v);
extern void func_ov002_02208a0c(struct UnkStruct_02209114 *self, int bit);
extern void RtcSendPxiCommand(int cmd);

void func_ov002_02209114(struct UnkStruct_02209114 *self, int v, int flag)
{
    func_ov002_0220914c(self, v);
    if (flag == 0) {
        func_ov002_02208a0c(self, 0x10);
    } else if (self->unk_1C - 1 == v) {
        RtcSendPxiCommand(0x2a);
    } else {
        RtcSendPxiCommand(0x29);
    }
}
