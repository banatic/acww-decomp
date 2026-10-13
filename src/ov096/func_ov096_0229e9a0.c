/* func_ov096_0229e9a0 @ 0x0229e9a0, 0x58 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229e9a0 {
    u8 pad_00[0xac];
    u16 ac;
    u8 pad_AE[2];
    u8 b0;
    u8 b1;
} UnkStruct_0229e9a0;

extern u16 func_ov096_0229f0dc(UnkStruct_0229e9a0 *self, UnkStruct_0229e9a0 *other);
extern u8 func_ov096_0229f088(UnkStruct_0229e9a0 *self, UnkStruct_0229e9a0 *other);
extern void func_ov096_0229f5ac(UnkStruct_0229e9a0 *self, UnkStruct_0229e9a0 *other);
extern void func_ov094_0229a99c(void *ptr, int a, int b);
extern void func_ov096_0229e258(UnkStruct_0229e9a0 *self);

void func_ov096_0229e9a0(UnkStruct_0229e9a0 *self, UnkStruct_0229e9a0 *other)
{
    self->b1 = 2;
    self->ac = func_ov096_0229f0dc(self, other);
    self->b0 = func_ov096_0229f088(self, other);
    func_ov096_0229f5ac(self, other);
    func_ov094_0229a99c((char *) self + 0x358, self->ac, self->b0);
    func_ov096_0229e258(self);
}
