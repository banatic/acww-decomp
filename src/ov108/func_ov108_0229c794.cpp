/* func_ov108_0229c794 @ 0x0229c794, 0x24 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov002/AnimState.h"

struct UnkStruct_0229c794 {
    char pad_00[0x2498];
    AnimState state;
};

extern "C" void func_ov108_0229c794(UnkStruct_0229c794 *self)
{
    func_ov002_0220a374(&self->state, 0);
    self->state.v3();
}
