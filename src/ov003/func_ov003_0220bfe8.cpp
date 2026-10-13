/* func_ov003_0220bfe8 @ 0x0220bfe8, 0x7c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov003_0223801019func_ov003_0220bfe8Ev
 */

#include "cpp/ov003/Obj_ov003_02238010.h"

void Obj_ov003_02238010::func_ov003_0220bfe8()
{
    static void (Obj_ov003_02238010::*pmfs[3])() = {&Obj_ov003_02238010::func_ov003_0220bfe0,
                                                    &Obj_ov003_02238010::func_ov003_0220bf4c,
                                                    &Obj_ov003_02238010::func_ov003_0220bf18};
    int i = state_134;
    if (i >= 3) {
        return;
    }
    (this->*pmfs[i])();
}
