/* func_ov004_0221e1a0 @ 0x0221e1a0, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0221e1a0 {
    u8 pad_00[0x89c];
    u8 sub[4];
};

extern int func_0202e364(struct UnkStruct_0221e1a0 *self);
extern void func_0201c280(struct UnkStruct_0221e1a0 *self, void *p);
extern void func_ov004_0221defc(void *p, struct UnkStruct_0221e1a0 *self);
extern void func_ov004_0221dd24(struct UnkStruct_0221e1a0 *self, int a);
extern struct UnkStruct_0221e1a0 *data_ov004_02257bc4;

int func_ov004_0221e1a0(struct UnkStruct_0221e1a0 *self)
{
    if (!func_0202e364(self)) {
        return 0;
    }
    data_ov004_02257bc4 = self;
    func_0201c280(self, &self->sub);
    func_ov004_0221defc(&self->sub, self);
    func_ov004_0221dd24(self, 0);
    return 1;
}
