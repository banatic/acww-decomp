/* func_ov047_02260c9c @ 0x02260c9c, 0x8c bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0204bcdc(void *);
extern int func_0204bc64(void *);

struct UnkStruct_02260c9c {
    u8 pad_00[0xce];
    u16 unk_CE;
    u32 unk_D0;
};

void func_ov047_02260c9c(struct UnkStruct_02260c9c *self)
{
    u16 tmp;
    unsigned int first_match;
    unsigned int in_range;
    u16 v;
    int adj;

    if (func_0204bcdc(&self->unk_CE) != 0) {
        tmp = 0xfff1;
        first_match = (func_0204bc64(&self->unk_CE) == func_0204bc64(&tmp)) ? 1u : 0u;
    } else {
        first_match = (self->unk_CE == 0xfff1) ? 1u : 0u;
    }
    if (first_match != 0) {
        return;
    }

    in_range = 0;
    v = self->unk_CE;
    if (v >= 0x12e8 && v <= 0x131f) {
        in_range = 1;
    }
    if (in_range) {
        adj = v - 0x12e8;
    } else {
        adj = -1;
    }
    self->unk_D0 = (u8) (adj + 0xaa);
}
