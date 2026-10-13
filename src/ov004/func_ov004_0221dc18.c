/* func_ov004_0221dc18 @ 0x0221dc18, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0221dc18 {
    u8 pad_00[0x3b0];
    u8 sub[0x564 - 0x3b0];
    u8 sub2[4];
};

extern u16 data_020c80f8;
extern int data_020c814c;
extern int data_021fbee8;
extern int func_02019c6c(void *p, int a, u16 b);
extern void func_0201ad18(void *p, int a, int b, int c, void *d, int e, int f, int g);

int func_ov004_0221dc18(struct UnkStruct_0221dc18 *self)
{
    if (func_02019c6c(&self->sub2, 1, data_020c80f8)) {
        func_0201ad18(&self->sub, 1, 0, 0, &data_021fbee8, 4, data_020c814c, 1);
        return 1;
    }
    return 0;
}
