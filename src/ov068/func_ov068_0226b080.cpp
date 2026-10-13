/* func_ov068_0226b080 @ 0x0226b080, 0x6c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_022771c019func_ov068_0226b080Ei
 */

#include "cpp/ov068/Obj_ov068_022771c0.h"

typedef void (Obj_ov068_022771c0::*PMF)(int);

int Obj_ov068_022771c0::func_ov068_0226b080(int a)
{
    static PMF tbl[2] = {&Obj_ov068_022771c0::func_ov068_0226b1d0, &Obj_ov068_022771c0::func_ov068_0226b0ec};

    if (state_1c < 2) {
        (this->*tbl[state_1c])(a);
    }
    return 0;
}
