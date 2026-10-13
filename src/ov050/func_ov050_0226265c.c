/* func_ov050_0226265c @ 0x0226265c, 0x6c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char data_021dc7a8[];
extern char data_021ebcd4[];

extern int func_02060d3c(char *ptr);
extern void func_02060d24(char *ptr, int val);
extern void func_02015fb0(void *self, int val, int arg2, int arg3, int arg4, int arg5);

struct UnkStruct_0226265c {
    u8 pad_00[0xd0];
    u32 unk_D0;
};

void func_ov050_0226265c(struct UnkStruct_0226265c *self)
{
    int res1, res2, val;
    char *base, *other;
    base = data_021dc7a8;
    other = data_021ebcd4;
    res1 = func_02060d3c(other);
    if (res1 < 0x579) {
        self->unk_D0 = 0x36;
        return;
    }
    res2 = func_02060d3c(other);
    func_02060d24(other, res2 - 0x578);
    val = func_02060d3c(base + 0xf52c);
    func_02015fb0(self, val, 2, 10, 0, 0);
    self->unk_D0 = 0x34;
}
