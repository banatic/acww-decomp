/* func_ov002_02209044 @ 0x02209044, 0x58 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02209044 {
    u8 pad_00[0x1c];
    u8 unk_1C;
};

extern int func_ov002_022088cc(void *pad);
extern int func_ov002_022088bc(void *pad);

int func_ov002_02209044(struct UnkStruct_02209044 *self, void *pad, u8 *cur, u8 limit)
{
    if (pad != 0) {
        if (func_ov002_022088cc(pad)) {
            if (*cur > limit) {
                *cur = *cur - 1;
            } else {
                *cur = self->unk_1C - 1;
            }
            return 1;
        }
        if (func_ov002_022088bc(pad)) {
            if (*cur + 1 < self->unk_1C) {
                *cur = *cur + 1;
            } else {
                *cur = limit;
            }
            return 1;
        }
    }
    return 0;
}
