/* func_ov068_02269128 @ 0x02269128, 0x64 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_022771c019func_ov068_02269128Ei
 */

#include "cpp/ov068/Obj_ov068_022771c0.h"

typedef void (Obj_ov068_022771c0::*PMF_Type)(int);

int Obj_ov068_022771c0::func_ov068_02269128(int arg)
{
    static PMF_Type table[1] = {&Obj_ov068_022771c0::func_ov068_0226918c};
    unsigned char idx = state_1c;
    if (idx < 1) {
        (this->*table[idx])(arg);
    }
    return 0;
}
