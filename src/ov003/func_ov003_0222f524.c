/* func_ov003_0222f524 @ 0x0222f524, 0x4c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0222f524 {
    u8 pad_00[0x24d];
    s8 unk_24D;
    u8 pad_24E[6];
    u8 unk_254;
    u8 unk_255;
    u8 pad_256[0x25c - 0x256];
};

extern struct UnkStruct_0222f524 data_ov003_022617bc[];

int func_ov003_0222f524(u8 *out, int idx)
{
    u8 k = (u8) (idx & 0xf);
    struct UnkStruct_0222f524 *e = &data_ov003_022617bc[k];
    int v = e->unk_24D;

    if (v >= 0) {
        if (e->unk_254 >= e->unk_255) {
            *out = 1;
        } else {
            *out = 0;
        }
    }
    return v;
}
