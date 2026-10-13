/* func_ov003_0221a244 @ 0x0221a244, 0x118 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov003_022382ac19func_ov003_0221a244Ev
 */

#include "cpp/ov003/Obj_ov003_022382ac.h"

typedef void (Obj_ov003_022382ac::*PMF)();

void Obj_ov003_022382ac::func_ov003_0221a244()
{
    static PMF table[14] = {
        &Obj_ov003_022382ac::func_ov068_0226f854, &Obj_ov003_022382ac::func_ov068_0226f648,
        &Obj_ov003_022382ac::func_ov068_0226f504, &Obj_ov003_022382ac::func_ov068_0226f49c,
        &Obj_ov003_022382ac::func_ov068_0226f3b0, &Obj_ov003_022382ac::func_ov068_0226f298,
        &Obj_ov003_022382ac::func_ov068_0226f178, &Obj_ov003_022382ac::func_ov068_0226effc,
        &Obj_ov003_022382ac::func_ov068_0226ee54, &Obj_ov003_022382ac::func_ov003_0221a1dc,
        &Obj_ov003_022382ac::func_ov068_0226ed9c, &Obj_ov003_022382ac::func_ov003_0221a128,
        &Obj_ov003_022382ac::func_ov068_0226eca8, &Obj_ov003_022382ac::func_ov068_0226ebc4,
    };
    int index = state_39c;
    if (index >= 14) {
        return;
    }
    (this->*table[index])();
}
