/* func_ov068_0227191c @ 0x0227191c, 0x44 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0227191c {
    char pad_00[0x240];
    short unk_240;
    char pad_242[0x251 - 0x242];
    u8 unk_251;
};
extern int func_ov003_02235b54(struct UnkStruct_0227191c *, int, int);
extern int func_ov003_02233c70(int, int);

void func_ov068_0227191c(struct UnkStruct_0227191c *self, unsigned short *out)
{
    int base;

    if (func_ov003_02235b54(self, 0xa0, 0xe38) != 0) {
        base = -0x8000;
        base += func_ov003_02233c70(0xc, 1);
        self->unk_240 = (short) base;
        self->unk_251 = 0xf;
        *out = 0;
    }
}
