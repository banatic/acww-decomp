/* func_ov123_0229bb74 @ 0x0229bb74, 0xfc bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xa2];
    u8 unk_A2;
    u8 pad_A3;
    u8 pad_A4[6];
    u8 unk_AA;
    u8 unk_AB;
    u8 unk_AC;
} UnkStruct_0229bb74;

extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(UnkStruct_0229bb74 *self);
extern void func_ov123_0229b6d0(UnkStruct_0229bb74 *self);
extern int func_ov123_02299adc(UnkStruct_0229bb74 *self, int arg);
extern void func_ov123_02299c04(UnkStruct_0229bb74 *self);
extern void func_ov123_02299cc0(UnkStruct_0229bb74 *self);
extern void RtcSendPxiCommand(u32 cmd);
extern void func_ov123_0229b65c(UnkStruct_0229bb74 *self);
extern int func_ov123_022998c0(UnkStruct_0229bb74 *self);
extern void func_ov123_02299980(UnkStruct_0229bb74 *self);
extern void func_ov123_02299d00(UnkStruct_0229bb74 *self);
extern void func_ov123_0229b598(UnkStruct_0229bb74 *self);
extern void func_ov123_0229b5cc(UnkStruct_0229bb74 *self);

extern struct {
    u8 pad[2];
    u16 flags;
} data_021fbe40;

void func_ov123_0229bb74(UnkStruct_0229bb74 *self)
{
    if (func_ov002_02208014(self)) {
        func_ov123_0229b6d0(self);
        return;
    }
    if (func_ov123_02299adc(self, func_ov002_02208008(self))) {
        if (self->unk_AC == 0) {
            self->unk_AB = self->unk_AA;
        }
        func_ov123_02299c04(self);
        return;
    } else {
        u16 flags = data_021fbe40.flags;
        if (flags & 1) {
            func_ov123_02299cc0(self);
            return;
        }
        if (flags & 0x800) {
            RtcSendPxiCommand(0x864);
            if (self->unk_AC == 0) {
                self->unk_AC = 1;
                self->unk_AA = self->unk_A2 + 13;
            } else {
                self->unk_AC = 2;
            }
            func_ov123_0229b65c(self);
            return;
        }
        if (func_ov123_022998c0(self) != 0) {
            return;
        }
        flags = data_021fbe40.flags;
        if (flags & 0x400) {
            func_ov123_02299980(self);
            return;
        }
        if (flags & 2) {
            func_ov123_02299d00(self);
            func_ov123_0229b598(self);
            return;
        }
        if (flags & 8) {
            func_ov123_02299d00(self);
            func_ov123_0229b5cc(self);
            return;
        }
        return;
    }
}
