/* func_ov004_02235698 @ 0x02235698, 0x90 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02235698 {
    u8 pad_00[0x15c];
    int unk_15C;
    u8 pad_160[0x1c9 - 0x160];
    u8 unk_1C9;
    u8 pad_1CA[0x1e8 - 0x1ca];
    u8 unk_1E8;
    u8 unk_1E9;
    u8 pad_1EA[0x1f0 - 0x1ea];
    u8 unk_1F0;
    u8 unk_1F1;
    u8 pad_1F2[0x1f4 - 0x1f2];
    int unk_1F4;
    int unk_1F8;
};

void func_ov004_02235698(struct UnkStruct_02235698 *self)
{
    int v;
    int a;
    int b;

    v = self->unk_15C;
    a = self->unk_1E8;
    if (a != v) {
        if (((1 << (a & 0x1f)) & *(int *) ((u8 *) self + (a >> 5) * 4 + 0x1f4)) == 0) {
            self->unk_1E8 = v;
        }
        b = self->unk_1E9;
        if (((1 << (b & 0x1f)) & *(int *) ((u8 *) self + (b >> 5) * 4 + 0x1f4)) == 0) {
            self->unk_1E9 = self->unk_15C;
            self->unk_1C9 = 0;
        }
    }
    self->unk_1F4 = 0;
    self->unk_1F8 = 0;
    self->unk_1F1 = 0;
    self->unk_1F0 = 0;
}
