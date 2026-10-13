/* func_ov009_022640d8 @ 0x022640d8, 0xb4 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov009_022658dc8vfunc_74Ev
 */

#include "cpp/ov009/Obj_ov009_022658dc.h"

typedef void (Obj_ov009_022658dc::*PMF)();

void Obj_ov009_022658dc::vfunc_74()
{
    static PMF tbl[7] = {
        &Obj_ov009_022658dc::func_ov009_02263fbc, &Obj_ov009_022658dc::func_ov009_02263de8,
        &Obj_ov009_022658dc::func_ov009_02263c14, &Obj_ov009_022658dc::func_ov009_02263b78,
        &Obj_ov009_022658dc::func_ov009_02263ab0, &Obj_ov009_022658dc::func_ov009_02263a98,
        &Obj_ov009_022658dc::func_ov009_02263a80,
    };

    unsigned char t = state_134;
    if (t >= 7) {
        return;
    }
    (this->*tbl[t])();
}
