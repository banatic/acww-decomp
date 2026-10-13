/* func_ov002_02209518 @ 0x02209518, 0x74 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02209518 {
    u8 pad_00[8];
    int unk_08;
    int unk_0C;
    u8 pad_10[0x8];
    u8 unk_18;
    u8 unk_19;
    u8 unk_1A;
};

extern const int data_ov002_0220bb84[];
extern void func_ov002_0220958c(struct UnkStruct_02209518 *self);
extern void func_02002708(int v);
extern int func_ov002_02209324(struct UnkStruct_02209518 *self);
extern void func_ov002_02209868(struct UnkStruct_02209518 *self, int a, int b);
extern void func_ov002_0220968c(struct UnkStruct_02209518 *self, int v);

void func_ov002_02209518(struct UnkStruct_02209518 *self)
{
    int step;
    int d;

    if (self->unk_18 == 0) {
        func_ov002_0220958c(self);
        func_02002708(self->unk_1A);
    }
    step = data_ov002_0220bb84[self->unk_18];
    if (self->unk_19 != 0) {
        d = self->unk_08 - step;
    } else {
        d = self->unk_08 + step;
    }
    if (d > 0) {
        d = 0;
    }
    if (-d + func_ov002_02209324(self) > 0xff) {
        d = func_ov002_02209324(self) - 0xff;
    }
    func_ov002_02209868(self, d, self->unk_0C - step);
    self->unk_18 = self->unk_18 + 1;
    if (self->unk_18 >= 3) {
        func_ov002_0220968c(self, 3);
    }
}
