/* func_ov004_0221ae00 @ 0x0221ae00, 0x7c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_0225328c19func_ov004_0221ae00Ev
 */

#include "cpp/ov004/Obj_ov004_0225328c.h"

void Obj_ov004_0225328c::func_ov004_0221ae00()
{
    static void (Obj_ov004_0225328c::*pmfs[3])() = {&Obj_ov004_0225328c::func_ov004_0221adf8,
                                                    &Obj_ov004_0225328c::func_ov004_0221ad8c,
                                                    &Obj_ov004_0225328c::func_ov004_0221ad58};
    int i = unk_134;
    if (i >= 3) {
        return;
    }
    (this->*pmfs[i])();
}
