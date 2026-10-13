/* func_ov103_0229c588 @ 0x0229c588, 0x30 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229c588 {
    u8 pad_00[0x2da8];
    u8 state;
};

extern void func_ov103_0229c640(struct UnkStruct_0229c588 *self);
extern void func_ov103_0229c32c(struct UnkStruct_0229c588 *self);
extern void func_ov103_0229cfa0(struct UnkStruct_0229c588 *self);

void func_ov103_0229c588(struct UnkStruct_0229c588 *self)
{
    switch (self->state) {
        case 0:
            func_ov103_0229c640(self);
            break;
        case 1:
            func_ov103_0229c32c(self);
            break;
        case 3:
        default:
            func_ov103_0229cfa0(self);
            break;
    }
}
