/* func_ov003_0220cbb4 @ 0x0220cbb4, 0x70 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0220cbb4 {
    u8 pad_00[0x818];
    u32 unk_818;
    u8 pad_81C[0xc4];
    u32 unk_8E0;
    u32 unk_8E4;
};

extern int func_0200f290(struct UnkStruct_0220cbb4 *self, int param);
extern void func_0200f268(struct UnkStruct_0220cbb4 *self, int param);
extern void func_ov003_0220e8f4(struct UnkStruct_0220cbb4 *self, u32 *arr, int a, int b);

void func_ov003_0220cbb4(struct UnkStruct_0220cbb4 *self)
{
    if (func_0200f290(self, 0x16) == 0) {
        return;
    }

    switch (self->unk_818) {
        case 1: {
            u32 arr[2];
            arr[0] = self->unk_8E0;
            arr[1] = self->unk_8E4;
            func_ov003_0220e8f4(self, arr, 6, -1);
            func_0200f268(self, 0x16);
            func_0200f268(self, 0x13);
            break;
        }
        case 2:
            func_0200f268(self, 0x16);
            func_0200f268(self, 0x13);
            break;
        default:
            break;
    }
}
