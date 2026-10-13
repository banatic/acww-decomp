/* func_ov004_02227888 @ 0x02227888, 0x74 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02227888 {
    u8 pad_00[0x2d0];
    u8 sub[0x704 - 0x2d0];
    int state;
};

extern void func_020109a0(struct UnkStruct_02227888 *self, int a, int b, int c);
extern void func_02010f5c(struct UnkStruct_02227888 *self);
extern int func_02056f28(void *p, int slot);
extern void func_0200f888(struct UnkStruct_02227888 *self);

void func_ov004_02227888(struct UnkStruct_02227888 *self, int flag)
{
    if (flag != 0 && self->state != 0x3e) {
        func_020109a0(self, 0x3e, 3, 0);
    }
    func_02010f5c(self);
    if (self->state == 0x3e) {
        if (func_02056f28(&self->sub, 1) || func_02056f28(&self->sub, 6) || func_02056f28(&self->sub, 0xb) ||
            func_02056f28(&self->sub, 0x10)) {
            func_0200f888(self);
        }
    }
}
