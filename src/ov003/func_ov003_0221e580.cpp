/* func_ov003_0221e580 @ 0x0221e580, 0xa8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov003_0223948c19func_ov003_0221e580Ei
 */

#include "cpp/ov003/Obj_ov003_0223948c.h"

int Obj_ov003_0223948c::func_ov003_0221e580(int state)
{
    typedef int (Obj_ov003_0223948c::*PMF)();
    static PMF table[5] = {&Obj_ov003_0223948c::func_ov003_0221e4e4, &Obj_ov003_0223948c::func_ov003_0221e4a4,
                           &Obj_ov003_0223948c::func_ov003_0221e46c, &Obj_ov003_0223948c::func_ov003_0221e45c,
                           &Obj_ov003_0223948c::func_ov003_0221e424};
    if (state < 5) {
        if ((this->*table[state])() != 0) {
            state_2b4 = state;
            return 1;
        }
    }
    return 0;
}
