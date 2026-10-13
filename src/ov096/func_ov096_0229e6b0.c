/* func_ov096_0229e6b0 @ 0x0229e6b0, 0x6c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229e6b0 {
    u8 pad_00[0xac];
    volatile u16 unk_AC;
    u8 unk_AE[2];
    u8 unk_B0;
    u8 unk_B1;
    u8 unk_B2[2];
    u8 unk_B4;
} UnkStruct_0229e6b0;

extern int func_ov096_0229daec(UnkStruct_0229e6b0 *self, u16 id);

int func_ov096_0229e6b0(UnkStruct_0229e6b0 *self)
{
    volatile u16 id;

    if (self->unk_B1 != 2) {
        return 0;
    }
    if (self->unk_B0 != 0) {
        return 0;
    }
    id = self->unk_AC;
    {
        unsigned int ok = 0;
        u16 hi = id;
        u16 lo = id;
        if (lo >= 0x1492 && hi <= 0x14fd) {
            ok = 1;
        }
        if (ok > 0) {
            if (self->unk_B4 == 0x25) {
                return 0;
            }
        }
    }
    return func_ov096_0229daec(self, self->unk_AC);
}
