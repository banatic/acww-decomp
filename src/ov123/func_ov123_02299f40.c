/* func_ov123_02299f40 @ 0x02299f40, 0x152 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_common_subs off

typedef struct {
    char pad_00[0xa4];
    u8 unk_A4;
    char pad_A5[3];
    u8 unk_A8;
    u8 unk_A9;
    char pad_AA[3];
    u8 unk_AD;
    u8 unk_AE;
} UnkStruct_02299f40;

extern void func_ov123_0229a094(UnkStruct_02299f40 *self, int a, int b);
extern void func_ov123_0229ab80(UnkStruct_02299f40 *self, int a, int b, int c, int d, int e, int f);
extern void func_ov123_0229a180(UnkStruct_02299f40 *self, int a, int b, int c);
extern void func_ov123_0229a148(UnkStruct_02299f40 *self, int a, int b);

void func_ov123_02299f40(UnkStruct_02299f40 *self)
{
    u32 a8;
    u32 a9;
    u32 angle_a8;
    u32 x_max;
    u32 y_max;
    u32 r4;
    u32 r6;
    u32 r7;

    if (self->unk_A4 == 8) {
        func_ov123_0229a094(self, self->unk_A8, self->unk_A9);
        func_ov123_0229a094(self, self->unk_AD, self->unk_AE);
        func_ov123_0229ab80(self, self->unk_A8, self->unk_A9, self->unk_AD, self->unk_AE, 1, 3);
        return;
    }

    r4 = self->unk_AD;
    a8 = self->unk_A8;
    if (a8 >= r4) {
        r7 = 2;
        angle_a8 = 0;
        x_max = a8;
    } else {
        r7 = 0;
        angle_a8 = 2;
        x_max = r4;
        r4 = a8;
    }

    r6 = self->unk_AE;
    a9 = self->unk_A9;
    if (a9 >= r6) {
        angle_a8++;
        y_max = a9;
    } else {
        r7++;
        y_max = r6;
        r6 = a9;
    }

    func_ov123_0229a180(self, a8, a9, angle_a8);
    func_ov123_0229a180(self, self->unk_AD, self->unk_AE, r7);

    r7 = r4;
    while (r7 <= x_max) {
        func_ov123_0229a148(self, r7, r6);
        r7 = (u8) (r7 + 2);
    }

    if (r6 != y_max) {
        r7 = r4;
        if ((y_max - r6) & 1) {
            r7 = (u8) (r4 + 1);
        }
        while (r7 <= x_max) {
            func_ov123_0229a148(self, r7, y_max);
            r7 = (u8) (r7 + 2);
        }
    }

    r7 = r6 + 2;
    r6 = (u8) r7;
    while (r6 < y_max) {
        func_ov123_0229a148(self, r4, r6);
        r6 = (u8) (r6 + 2);
    }

    if (r4 != x_max) {
        r6 = (u8) r7;
        if ((x_max - r4) & 1) {
            r6 = (u8) (r6 - 1);
        }
        while (r6 < y_max) {
            func_ov123_0229a148(self, x_max, r6);
            r6 = (u8) (r6 + 2);
        }
    }
}
