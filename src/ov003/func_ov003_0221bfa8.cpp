/* func_ov003_0221bfa8 @ 0x0221bfa8, 0xf0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov003_0223863019func_ov003_0221bfa8Ei
 */

#include "cpp/ov003/Obj_ov003_02238630.h"

typedef int (Obj_ov003_02238630::*PMF)();

int Obj_ov003_02238630::func_ov003_0221bfa8(int state)
{
    static PMF tbl[10] = {
        &Obj_ov003_02238630::func_ov003_0221bec4, &Obj_ov003_02238630::func_ov003_0221be7c,
        &Obj_ov003_02238630::func_ov003_0221bd90, &Obj_ov003_02238630::func_ov003_0221bd68,
        &Obj_ov003_02238630::func_ov003_0221bd34, &Obj_ov003_02238630::func_ov003_0221bcf8,
        &Obj_ov003_02238630::func_ov003_0221bc74, &Obj_ov003_02238630::func_ov003_0221bc3c,
        &Obj_ov003_02238630::func_ov003_0221bc00, &Obj_ov003_02238630::func_ov003_0221bb9c,
    };

    if (state < 10) {
        if ((this->*tbl[state])()) {
            state_2b4 = state;
            return 1;
        }
    }
    return 0;
}
