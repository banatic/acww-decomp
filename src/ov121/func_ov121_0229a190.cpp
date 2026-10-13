/* func_ov121_0229a190 @ 0x0229a190, 0x20 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov002/AnimState.h"

struct UnkStruct_0229a190 {
    char pad_00[0x3a8];
    AnimState state;
};

extern "C" void func_ov121_0229a190(UnkStruct_0229a190 *self)
{
    func_ov002_0220a0ec(&self->state);
    self->state.v3();
}
