/* func_020a1e08 @ 0x020a1e08, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_020a1e08 {
    u8 pad_00[0xa0]; // 0x00-0x9f
    u8 unk_A0;       // 0xa0
    u8 unk_A1;       // 0xa1
    u8 unk_A2;       // 0xa2
    u8 unk_A3;       // 0xa3
    s16 unk_A4;      // 0xa4
    u8 pad_A6[2];    // 0xa6-0xa7
    u32 unk_A8;      // 0xa8
    u8 pad_AC[4];    // 0xac-0xaf
    u32 unk_B0;      // 0xb0
    u32 unk_B4;      // 0xb4
};

extern s32 data_020d1bf0[];
extern int func_020a199c(struct UnkStruct_020a1e08 *, s32, s32, s32);

int func_020a1e08(struct UnkStruct_020a1e08 *p, int idx)
{
    s32 val, q, r, inc, res;

    val = data_020d1bf0[idx];
    q = val / 0x200;
    r = val % 0x200;

    while (p->unk_A2 <= q) {
        inc = 0x200;
        if (p->unk_A2 == q) {
            inc = r;
        }
        res = func_020a199c(p, p->unk_B0 + (s32) p->unk_A2 * 0x200, p->unk_B4 + (s32) p->unk_A2 * 0x200, inc);

        if (res == 0) {
            if (p->unk_A4 == -1) {
                p->unk_A4 = p->unk_A2;
            }
            p->unk_A8 += inc;
            if (p->unk_A2 == q) {
                p->unk_A0 = 4;
                p->unk_A2 = (u8) (p->unk_A2 + 1);
                return 3;
            }
        } else {
            if (p->unk_A8 != 0) {
                p->unk_A0 = 4;
                return 3;
            }
        }

        p->unk_A2 = (u8) (p->unk_A2 + 1);
    }

    if (p->unk_A2 > q) {
        p->unk_A0 = 5;
    }

    return 3;
}
