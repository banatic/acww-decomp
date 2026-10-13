/* func_ov002_022094b4 @ 0x022094b4, 0x64 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022094b4 {
    u8 pad_00[8];
    int unk_08;
    int unk_0C;
    u8 pad_10[0x8];
    u8 unk_18;
    u8 unk_19;
    u8 unk_1A;
};

extern int func_ov002_02209324(struct UnkStruct_022094b4 *self);
extern void func_ov002_02209868(struct UnkStruct_022094b4 *self, int a, int b);
extern void func_0200277c(int v);
extern void func_ov002_0220968c(struct UnkStruct_022094b4 *self, int v);

void func_ov002_022094b4(struct UnkStruct_022094b4 *self)
{
    int d;

    if (self->unk_18 == 0) {
        if (self->unk_19 != 0) {
            d = self->unk_08 - 0xb;
        } else {
            d = self->unk_08 + 0xb;
        }
        if (d > 0) {
            d = 0;
        }
        if (-d + func_ov002_02209324(self) > 0xff) {
            d = func_ov002_02209324(self) - 0xff;
        }
        func_ov002_02209868(self, d, self->unk_0C - 0xb);
        self->unk_18 = self->unk_18 + 1;
    } else {
        func_0200277c(self->unk_1A);
        func_ov002_0220968c(self, 0);
    }
}
