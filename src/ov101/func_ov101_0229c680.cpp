/* func_ov101_0229c680 @ 0x0229c680, 0x20 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov002/AnimState.h"

struct UnkStruct_0229c680 {
    char pad_00[0x229c];
    AnimState state;
};

extern "C" void func_ov101_0229c680(UnkStruct_0229c680 *self)
{
    func_ov002_0220a0ec(&self->state);
    self->state.v3();
}
