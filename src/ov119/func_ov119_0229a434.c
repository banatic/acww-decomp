/* func_ov119_0229a434 @ 0x0229a434, 0x36 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229a434 {
    u8 pad_00[0xb3];
    u8 b3;
};

extern void func_ov119_0229a49c(struct UnkStruct_0229a434 *self);
extern void func_ov119_0229a46c(struct UnkStruct_0229a434 *self);

void func_ov119_0229a434(struct UnkStruct_0229a434 *self)
{
    self->b3++;
    if (self->b3 == 10) {
        func_ov119_0229a49c(self);
    } else if (self->b3 >= 25) {
        func_ov119_0229a46c(self);
        self->b3 = 0;
    }
}
