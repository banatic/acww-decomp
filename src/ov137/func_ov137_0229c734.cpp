/* func_ov137_0229c734 @ 0x0229c734, 0x1c bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov002/AnimState.h"

struct UnkStruct_0229c734 {
    char pad_00[0x94];
    AnimState state;
};

extern "C" void func_ov137_0229c734(UnkStruct_0229c734 *self)
{
    func_ov002_0220a374(&self->state, 0);
    self->state.v3();
}
