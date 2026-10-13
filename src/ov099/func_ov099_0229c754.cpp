/* func_ov099_0229c754 @ 0x0229c754, 0x24 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov002/AnimState.h"

struct UnkStruct_0229c754 {
    char pad_00[0x2274];
    AnimState state;
};

extern "C" void func_ov099_0229c754(UnkStruct_0229c754 *self)
{
    func_ov002_0220a374(&self->state, 0);
    self->state.v3();
}
