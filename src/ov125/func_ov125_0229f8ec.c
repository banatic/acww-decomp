/* func_ov125_0229f8ec @ 0x0229f8ec, 0x3c bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229f8ec {
    u8 pad_00[0x87c];
    u8 cur;
};

extern void func_ov125_0229f75c(struct UnkStruct_0229f8ec *obj, int arg);

int func_ov125_0229f8ec(struct UnkStruct_0229f8ec *obj, u32 a, u32 b)
{
    u8 c = obj->cur;
    if (c < a) {
        goto fail;
    }
    if (c > b) {
        goto fail;
    }
    if (c == b) {
        func_ov125_0229f75c(obj, 8);
        obj->cur = (u8) a;
    } else {
        obj->cur = (u8) (c + 1);
    }
    return 1;
fail:
    return 0;
}
