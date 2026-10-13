/* func_020568dc @ 0x020568dc, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_020568dc {
    u8 pad_00[0x18];
    u32 unk_18;
    u8 pad_1C[0x04];
    u32 unk_20;
    u16 unk_24;
    u8 unk_26;
    u32 unk_28;
};

void func_020568dc(struct UnkStruct_020568dc *s)
{
    s->unk_18 = 0;
    s->unk_24 = 0;
    s->unk_26 = 0;
    s->unk_28 = 0;
    s->unk_20 = 0;
}
