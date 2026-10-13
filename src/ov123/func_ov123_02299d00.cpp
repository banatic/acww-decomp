/* func_ov123_02299d00 @ 0x02299d00, 0x24 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov002/AnimState.h"

struct UnkStruct_02299d00 {
    char pad_00[0x1cc];
    AnimState state;
};

extern "C" void func_ov123_02299d00(UnkStruct_02299d00 *self)
{
    func_ov002_0220a374(&self->state, 0);
    self->state.v3();
}
