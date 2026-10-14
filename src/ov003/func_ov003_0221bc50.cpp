/* func_ov003_0221bc50 @ 0x0221bc50, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov003_0223863019func_ov003_0221bc50Ev
 */

#include "cpp/ov003/Obj_ov003_02238630.h"

struct UnkStruct_0221bc50 {
    int pad_00;
    int unk_04;
};

void Obj_ov003_02238630::func_ov003_0221bc50()
{
    UnkStruct_0221bc50 *p = (UnkStruct_0221bc50 *) unk_40;
    if (p != 0) {
        if (p->unk_04 == 0) {
            func_ov003_0221bfa8(7);
        }
    }
}
