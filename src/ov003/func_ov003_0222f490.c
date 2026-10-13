/* func_ov003_0222f490 @ 0x0222f490, 0x94 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0222f490 {
    u8 pad_00[0x24d];
    s8 unk_24D;
    u8 pad_24E[0x25c - 0x24e];
};

extern struct UnkStruct_0222f490 data_ov003_022617bc[];

int func_ov003_0222f490(int idx)
{
    u8 k = (u8) (idx & 0xf);
    struct UnkStruct_0222f490 *e = &data_ov003_022617bc[k];

    switch (e->unk_24D) {
        case 9:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 31:
        case 33:
        case 34:
        case 36:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 52:
            return 1;
        default:
            return 0;
    }
}
