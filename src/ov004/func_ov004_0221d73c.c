/* func_ov004_0221d73c @ 0x0221d73c, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0221d73c {
    u8 pad_00[0x564];
    u8 sub[0xa4c - 0x564];
    u8 cnt;
};

extern u16 data_020c80f8;
extern int func_02019c90(void *p, int a, int b, u16 c);
extern int func_ov004_0221dd24(struct UnkStruct_0221d73c *self, int a);

void func_ov004_0221d73c(struct UnkStruct_0221d73c *self)
{
    if (self->cnt != 0) {
        self->cnt--;
    }
    if (self->cnt != 0) {
        if (self->cnt == 1) {
            func_02019c90(&self->sub, 1, 0, data_020c80f8);
        }
    } else {
        func_ov004_0221dd24(self, 0);
    }
}
