/* func_ov144_0229a17c @ 0x0229a17c, 0x1c bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov002/AnimState.h"

struct UnkStruct_0229a17c {
    char pad_00[0xc4];
    AnimState state;
};

extern "C" void func_ov144_0229a17c(UnkStruct_0229a17c *self)
{
    func_ov002_0220a374(&self->state, 0);
    self->state.v3();
}
