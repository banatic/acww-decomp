/* func_ov003_0220c064 @ 0x0220c064, 0x8c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov003_0223801019func_ov003_0220c064Ei
 */

#include "cpp/ov003/Obj_ov003_02238010.h"

int Obj_ov003_02238010::func_ov003_0220c064(int state)
{
    typedef int (Obj_ov003_02238010::*PMF)();
    static PMF table[3] = {&Obj_ov003_02238010::func_ov003_0220bfe4, &Obj_ov003_02238010::func_ov003_0220bf70,
                           &Obj_ov003_02238010::func_ov003_0220bf48};

    if (state < 3) {
        if ((this->*table[state])()) {
            state_134 = state;
            return 1;
        }
    }
    return 0;
}
