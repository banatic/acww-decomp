/* func_ov122_022a0848 @ 0x022a0848, 0xe0 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022a0848 {
    u8 pad_00[0x9c];
    u32 unk_9C;
    u32 unk_A0;
    u8 pad_A4[8];
    u8 unk_AC;
    u8 unk_AD;
    u8 unk_AE;
};

extern struct {
    u16 _pad0;
    u16 flags;
} data_021fbe40;

extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(struct UnkStruct_022a0848 *self);
extern int func_ov122_0229f684(struct UnkStruct_022a0848 *self, int a, int b);
extern void func_ov122_0229f940(struct UnkStruct_022a0848 *self);
extern void func_ov122_0229f9a8(struct UnkStruct_022a0848 *self);
extern void func_ov122_0229f1b4(struct UnkStruct_022a0848 *self);
extern void func_ov122_022a14c0(struct UnkStruct_022a0848 *self);
extern int func_ov122_022a0168(struct UnkStruct_022a0848 *self);
extern int func_ov122_022a0204(struct UnkStruct_022a0848 *self);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov122_0229efd8(struct UnkStruct_022a0848 *self, int a);
extern int func_ov122_022a0098(struct UnkStruct_022a0848 *self);
extern int func_ov122_022a00fc(struct UnkStruct_022a0848 *self);
extern int func_ov122_022a006c(struct UnkStruct_022a0848 *self);
extern unsigned char *func_ov122_022a0054(struct UnkStruct_022a0848 *self);
extern void RtcSendPxiCommand(int cmd);

void func_ov122_022a0848(struct UnkStruct_022a0848 *self)
{
    int t;
    u32 r4;
    u32 r6;

    if (func_ov002_02208014(self) != 0) {
        func_ov122_022a0054(self);
        return;
    }

    t = func_ov002_02208008(self);
    if (func_ov122_0229f684(self, t, 1) != 0) {
        func_ov122_0229f940(self);
        func_ov122_0229f9a8(self);
        func_ov122_0229f1b4(self);
        func_ov122_022a14c0(self);
        RtcSendPxiCommand(0xb);
        return;
    }

    if (func_ov122_022a0168(self) != 0) {
        return;
    }

    r4 = self->unk_9C;
    r6 = self->unk_A0;

    if (func_ov122_022a0204(self) != 0) {
        if ((r4 != self->unk_9C) || (r6 != self->unk_A0)) {
            func_ov122_0229f1b4(self);
        }
        return;
    }

    if ((data_021fbe40.flags & 1) != 0) {
        func_ov002_02208098((void *) (self), 0xd);
        func_ov122_0229efd8(self, 8);
        self->unk_AD = self->unk_AC;
        self->unk_AE = self->unk_AC;
    }

    if (func_ov122_022a0098(self) != 0) {
        return;
    }
    if (func_ov122_022a00fc(self) != 0) {
        return;
    }
    if (func_ov122_022a006c(self) != 0) {
        return;
    }
}
