/* func_ov002_022092e0 @ 0x022092e0, 0x38 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022092e0 {
    u8 pad_00[0x1b];
    u8 unk_1B;
    u8 unk_1C;
};

extern int func_0207096c(void *p);

void func_ov002_022092e0(struct UnkStruct_022092e0 *self)
{
    char *base;
    int best;
    int i;

    best = 0;
    i = 0;
    base = (char *) self + 0x28;
    for (; i < self->unk_1C; i++) {
        int v = func_0207096c(base + i * 0x74);
        if (v > best) {
            best = v;
        }
    }
    self->unk_1B = (u8) ((best + 7) >> 3);
}
