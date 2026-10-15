/* func_ov004_0221d664 @ 0x0221d664, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0221d664 {
    u8 pad_00[0x564];
    u8 sub[0x898 - 0x564];
    int phase;
};

extern u16 data_020c80f8;
extern int func_02019c90(void *p, int a, int b, u16 c);

int func_ov004_0221d664(struct UnkStruct_0221d664 *self)
{
    if (self->phase == 1 || self->phase == 2 || self->phase == 3) {
        func_02019c90(&self->sub, 2, 0, data_020c80f8);
    }
    return 1;
}
