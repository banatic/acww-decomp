/* func_ov003_0222ea84 @ 0x0222ea84, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0222ea84 {
    u8 pad_00[0x24d];
    s8 unk_24D;
    u8 pad_24E[2];
    u8 unk_250;
    u8 unk_251;
    u8 pad_252[0xa];
};

extern struct UnkStruct_0222ea84 data_ov003_02260e4c[];

u8 func_ov003_0222ea84(int i)
{
    struct UnkStruct_0222ea84 *e = &data_ov003_02260e4c[i];

    if (e->unk_24D < 0) {
        e->unk_251 = 0xa;
        e->unk_250 = 0;
    }
    return e->unk_250;
}
