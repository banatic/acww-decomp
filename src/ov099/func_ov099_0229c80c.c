/* func_ov099_0229c80c @ 0x0229c80c, 0x40 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229c80c {
    u8 pad_00[0x2900];
    u16 unk_2900;
    u8 unk_2902;
    u8 unk_2903;
};

extern void func_ov099_0229c880(struct UnkStruct_0229c80c *s, void *t);
extern void func_ov099_0229ce28(struct UnkStruct_0229c80c *s, void *t, unsigned short a, unsigned char b);

void func_ov099_0229c80c(struct UnkStruct_0229c80c *s, void *t)
{
    if (s->unk_2903 == 1) {
        // empty
    } else if (s->unk_2903 == 2) {
        u16 a = s->unk_2900;
        u8 b = s->unk_2902;
        func_ov099_0229c880(s, t);
        func_ov099_0229ce28(s, t, a, b);
    }
}
