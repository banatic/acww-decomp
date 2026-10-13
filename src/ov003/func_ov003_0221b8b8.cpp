/* func_ov003_0221b8b8 @ 0x0221b8b8, 0x8c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov003_0223843419func_ov003_0221b8b8Ei
 */

#include "cpp/ov003/Obj_ov003_02238434.h"

int Obj_ov003_02238434::func_ov003_0221b8b8(int state)
{
    static int (Obj_ov003_02238434::*table[3])() = {&Obj_ov003_02238434::func_ov003_0221b838,
                                                    &Obj_ov003_02238434::func_ov003_0221b818,
                                                    &Obj_ov003_02238434::func_ov003_0221b808};
    if (state < 3) {
        if ((this->*table[state])()) {
            state_2b4 = state;
            return 1;
        }
    }
    return 0;
}
