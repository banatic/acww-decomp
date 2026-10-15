/* func_ov004_0223a818 @ 0x0223a818, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0223a818 {
    s16 unk_00;
    u8 pad_02[0x154 - 2];
    int unk_154;
    int unk_158;
    int unk_15C;
};

extern u8 data_ov004_022595b8;
extern void *func_02003e80(int h);
extern void func_020e9fc8(int h);
extern void func_ov004_0223ac14(void *p);

void func_ov004_0223a818(struct UnkStruct_0223a818 *self)
{
    self->unk_00 = -1;
    self->unk_154 = 0;
    if (data_ov004_022595b8 != 0) {
        if (self->unk_158 != 0) {
            if (self->unk_15C != 0) {
                func_02003e80(self->unk_15C);
                self->unk_15C = 0;
            }
            func_020e9fc8(self->unk_158);
            self->unk_158 = 0;
        }
    }
    func_ov004_0223ac14((u8 *) self + 4);
    func_ov004_0223ac14((u8 *) self + 0xac);
}
