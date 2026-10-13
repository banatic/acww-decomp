/* func_ov068_02267a90 @ 0x02267a90, 0x7c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_022771c019func_ov068_02267a90Ei
 */

#include "cpp/ov068/Obj_ov068_022771c0.h"

typedef void (Obj_ov068_022771c0::*PMF)(int);

int Obj_ov068_022771c0::func_ov068_02267a90(int a)
{
    static PMF tbl[3] = {&Obj_ov068_022771c0::func_ov068_02267b8c, &Obj_ov068_022771c0::func_ov068_02267b3c,
                         &Obj_ov068_022771c0::func_ov068_02267b0c};

    if (state_1c < 3) {
        (this->*tbl[state_1c])(a);
    }
    return 0;
}
