/* func_ov002_02209ce8 @ 0x02209ce8, 0x20 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02209ce8 {
    u8 pad_00[0x14];
    u8 unk_14;
    u8 unk_15;
};

int func_ov002_02209ce8(struct UnkStruct_02209ce8 *p)
{
    return (p->unk_15 == 2 || p->unk_15 == 3) && p->unk_14 != 0;
}
