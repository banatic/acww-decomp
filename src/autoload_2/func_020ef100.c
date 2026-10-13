/* func_020ef100 @ 0x020ef100, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

extern int func_020eecb0(int val);

struct UnkStruct_020ef100 {
    u8 pad_00[0x15];
    u8 b;         // offset 0x15
    u8 pad_16[6]; // 0x16..0x1b
    u32 i;        // offset 0x1c
};

int func_020ef100(struct UnkStruct_020ef100 *self)
{
    int val;

    if (self->b == 0xff) {
        goto else_l;
    }

    val = func_020eecb0(self->b);
    if (val != -1) {
        goto store;
    }
    return 0;

else_l:
    val = 0xff;

store:
    self->i = val;
    return 1;
}
