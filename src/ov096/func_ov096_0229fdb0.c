/* func_ov096_0229fdb0 @ 0x0229fdb0, 0x48 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229fdb0 {
    char pad_00[0xb6];
    u8 unk_B6;
};

extern void RtcSendPxiCommand(u32 cmd);
extern void func_ov096_0229c434(struct UnkStruct_0229fdb0 *self);
extern u16 func_ov096_0229f0dc(struct UnkStruct_0229fdb0 *self, u8 b);
extern int func_02095aec(u16 *p);
extern void func_ov096_0229f5ac(struct UnkStruct_0229fdb0 *self, u8 b);
extern void func_ov002_02208098(struct UnkStruct_0229fdb0 *self, int arg);

void func_ov096_0229fdb0(struct UnkStruct_0229fdb0 *self)
{
    u16 temp;
    RtcSendPxiCommand(0x40);
    func_ov096_0229c434(self);
    temp = func_ov096_0229f0dc(self, self->unk_B6);
    if (func_02095aec(&temp) != 0) {
        func_ov096_0229f5ac(self, self->unk_B6);
        func_ov002_02208098(self, 0x2f);
    }
}
