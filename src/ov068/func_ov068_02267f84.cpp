/* func_ov068_02267f84 @ 0x02267f84, 0x9c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_022771c019func_ov068_02267f84Ei
 */

#include "cpp/ov068/Obj_ov068_022771c0.h"

int Obj_ov068_022771c0::func_ov068_02267f84(int arg)
{
    static void (Obj_ov068_022771c0::*const table[5])(int) = {
        &Obj_ov068_022771c0::func_ov068_0226840c, &Obj_ov068_022771c0::func_ov068_0226831c,
        &Obj_ov068_022771c0::func_ov068_02268254, &Obj_ov068_022771c0::func_ov068_022680a4,
        &Obj_ov068_022771c0::func_ov068_02268020};

    if (state_1c >= 5) {
        goto done;
    }

    (this->*table[state_1c])(arg);

done:
    return 0;
}
