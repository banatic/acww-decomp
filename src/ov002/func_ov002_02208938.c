/* func_ov002_02208938 @ 0x02208938, 0x84 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 data_021fbe40[2];

struct UnkStruct_02208938 {
    u8 pad_00[4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    u8 unk_0E;
    u8 unk_0F;
};

void func_ov002_02208938(struct UnkStruct_02208938 *p)
{
    u8 old_e;
    u8 *pF;

    old_e = p->unk_0E;

    p->unk_0E = (u8) (data_021fbe40[0] & 0xF0);

    pF = &p->unk_0F;
    p->unk_0F = (u8) (p->unk_0F | (u8) (data_021fbe40[1] & 0xF0));

    if (p->unk_0E == 0 || old_e != p->unk_0E) {
        p->unk_0F = (u8) (data_021fbe40[1] & 0xF0);
        p->unk_0A = p->unk_04;
        p->unk_0C = p->unk_04;
    } else {
        if (p->unk_0C > 0) {
            p->unk_0C--;
        } else {
            *pF = (u8) (*pF | (p->unk_0E & 0xF0));
            p->unk_0A = (s16) (p->unk_0A - p->unk_08);
            if (p->unk_0A < p->unk_06) {
                p->unk_0A = p->unk_06;
            }
            p->unk_0C = p->unk_0A;
        }
    }
}
