/* func_ov112_022a0ab0 @ 0x022a0ab0, 0xd4 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022a0ab0 {
    u8 pad_00[0xbd];
    u8 unk_BD;
    u8 unk_BE;
    u8 unk_BF;
};

extern u16 data_021fbe40[2];

extern int func_ov002_02208014(void);
extern int func_ov002_02208008(struct UnkStruct_022a0ab0 *self);
extern unsigned char *func_ov002_02208098(struct UnkStruct_022a0ab0 *self, unsigned char value);
extern int func_ov112_0229f56c(struct UnkStruct_022a0ab0 *self, int arg);
extern unsigned char *func_ov112_0229ff38(struct UnkStruct_022a0ab0 *self);
extern void func_ov112_0229f8e4(struct UnkStruct_022a0ab0 *self);
extern void func_ov112_0229f668(struct UnkStruct_022a0ab0 *self);
extern void func_ov112_0229f2bc(struct UnkStruct_022a0ab0 *self);
extern void func_ov112_0229f488(struct UnkStruct_022a0ab0 *self);
extern void RtcSendPxiCommand(int cmd);
extern int func_ov112_022a0620(struct UnkStruct_022a0ab0 *self);
extern int func_ov112_022a06b8(struct UnkStruct_022a0ab0 *self);
extern void func_ov112_0229fe60(struct UnkStruct_022a0ab0 *self, int arg);
extern int func_ov112_022a0548(struct UnkStruct_022a0ab0 *self);
extern int func_ov112_022a05b0(struct UnkStruct_022a0ab0 *self);
extern int func_ov112_022a051c(struct UnkStruct_022a0ab0 *self);

void func_ov112_022a0ab0(struct UnkStruct_022a0ab0 *self)
{
    if (func_ov002_02208014() != 0) {
        func_ov112_0229ff38(self);
        return;
    }

    if (func_ov112_0229f56c(self, func_ov002_02208008(self)) != 0) {
        func_ov112_0229f8e4(self);
        func_ov112_0229f668(self);
        func_ov112_0229f2bc(self);
        func_ov112_0229f488(self);
        RtcSendPxiCommand(0xb);
        return;
    }

    if (func_ov112_022a0620(self) != 0) {
        return;
    }

    {
        u8 old = self->unk_BD;

        if (func_ov112_022a06b8(self) != 0) {
            if (old != self->unk_BD) {
                func_ov112_0229f2bc(self);
            }
            return;
        }
    }

    if ((data_021fbe40[1] & 1) != 0) {
        func_ov002_02208098(self, 0xd);
        func_ov112_0229fe60(self, 0x100);
        self->unk_BE = self->unk_BD;
        self->unk_BF = self->unk_BD;
    }

    if (func_ov112_022a0548(self) != 0) {
        return;
    }
    if (func_ov112_022a05b0(self) != 0) {
        return;
    }
    if (func_ov112_022a051c(self) != 0) {
        return;
    }
}
