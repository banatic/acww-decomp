/* func_ov146_0229a9b8 @ 0x0229a9b8, 0x110 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229a9b8 {
    char pad_00[0xa8];
    int unk_A8;
    char pad_AC[0xae - 0xac];
    s16 unk_AE;
    u8 unk_B0;
    char pad_B1[0xbb - 0xb1];
    u8 unk_BB;
};

extern int func_ov002_02208054(struct UnkStruct_0229a9b8 *self, int a);
extern void func_ov146_0229a744(struct UnkStruct_0229a9b8 *self);
extern void func_ov146_0229a6a4(struct UnkStruct_0229a9b8 *self);
extern void func_ov146_0229a6dc(struct UnkStruct_0229a9b8 *self);
extern int func_ov146_02299e9c(struct UnkStruct_0229a9b8 *self, int b);
extern void RtcSendPxiCommand(int cmd);
extern int func_ov146_02299cbc(struct UnkStruct_0229a9b8 *self, int a, int b);
extern void func_ov002_02208098(struct UnkStruct_0229a9b8 *self, int n);
extern void func_ov002_0220a574(void *p);

extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;

void func_ov146_0229a9b8(struct UnkStruct_0229a9b8 *self)
{
    int r4;
    int r6;
    int cond;
    int idx;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov146_0229a744(self);
        return;
    }

    cond = (data_021fbdd8 != 0 && data_021fbddc != 0);
    if (cond == 0) {
        return;
    }

    r4 = data_021f6c58;
    r6 = data_021f6c54;

    if (r6 >= 0xa9 && r6 <= 0xbc) {
        if (r4 >= 0x39) {
            if (r4 < 0x75) {
                func_ov146_0229a6a4(self);
                return;
            }

            if (r4 >= 0x8b && r4 < 0xc7) {
                if (self->unk_B0 == 8) {
                    func_ov146_0229a6dc(self);
                    return;
                }
            }
        }
    }

    if (r4 >= 0x18 && r4 <= 0xe0 && r6 >= 0x38 && r6 < 0x98) {
        idx = self->unk_AE + ((r6 - (0x38 - (self->unk_A8 & 0xf))) >> 4);
        if (idx < 0x20) {
            r4 = *(u8 *) ((char *) self + idx + 0xea);
            if (func_ov146_02299e9c(self, r4) != 0) {
                if (self->unk_BB != r4) {
                    self->unk_BB = r4;
                    RtcSendPxiCommand(0x29);
                }
            }
        }
        return;
    }

    if (func_ov146_02299cbc(self, r4, r6) != 0) {
        func_ov002_02208098(self, 1);
        return;
    }

    if (r4 >= 0xe6 && r4 <= 0xee && r6 >= 0x38 && r6 <= 0x88) {
        func_ov002_0220a574((char *) self + 0x1fb4);
        func_ov002_02208098(self, 2);
    }
}
