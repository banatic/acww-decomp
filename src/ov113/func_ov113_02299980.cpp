/* func_ov113_02299980 @ 0x02299980, 0x24 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov002/AnimState.h"

struct UnkStruct_02299980 {
    char pad_00[0x2b20];
    AnimState state;
};

extern "C" void func_ov113_02299980(UnkStruct_02299980 *self)
{
    func_ov002_0220a374(&self->state, 0);
    self->state.v3();
}
