/* func_ov009_022638d0 @ 0x022638d0, 0xd0 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov009_022658dc19func_ov009_022638d0Ev
 */

#include "cpp/ov009/Obj_ov009_022658dc.h"

typedef void (Obj_ov009_022658dc::*PMF)();

void Obj_ov009_022658dc::func_ov009_022638d0()
{
    static PMF tbl[9] = {
        &Obj_ov009_022658dc::func_ov009_022638c8, &Obj_ov009_022658dc::func_ov009_022637ec,
        &Obj_ov009_022658dc::func_ov009_02263790, &Obj_ov009_022658dc::func_ov009_02263748,
        &Obj_ov009_022658dc::func_ov009_02263718, &Obj_ov009_022658dc::func_ov009_02263658,
        &Obj_ov009_022658dc::func_ov009_0226357c, &Obj_ov009_022658dc::func_ov009_0226354c,
        &Obj_ov009_022658dc::func_ov009_022634f0,
    };
    if (state_27c < 9) {
        (this->*tbl[state_27c])();
    }
}
