/* func_ov105_0229cd9c @ 0x0229cd9c, 0x20 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov002/AnimState.h"

struct UnkStruct_0229cd9c {
    char pad_00[0x24a4];
    AnimState state;
};

extern "C" void func_ov105_0229cd9c(UnkStruct_0229cd9c *self)
{
    func_ov002_0220a0ec(&self->state);
    self->state.v3();
}
