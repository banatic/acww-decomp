/* func_ov068_02274f18 @ 0x02274f18, 0x6c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_02277f3c19func_ov068_02274f18Ev
 */

#include "cpp/ov068/Obj_ov068_02277f3c.h"

void Obj_ov068_02277f3c::func_ov068_02274f18()
{
    static void (Obj_ov068_02277f3c::*pmfs[2])() = {&Obj_ov068_02277f3c::func_ov068_02274efc,
                                                    &Obj_ov068_02277f3c::func_ov068_02274ee0};
    if (unk_24c < 2) {
        (this->*pmfs[unk_24c])();
    }
}
