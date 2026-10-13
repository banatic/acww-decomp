/* func_ov068_02269278 @ 0x02269278, 0x9c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_022771c019func_ov068_02269278Ei
 */

#include "cpp/ov068/Obj_ov068_022771c0.h"

int Obj_ov068_022771c0::func_ov068_02269278(int arg)
{
    static void (Obj_ov068_022771c0::*const table[5])(int) = {
        &Obj_ov068_022771c0::func_ov068_02269684, &Obj_ov068_022771c0::func_ov068_02269548,
        &Obj_ov068_022771c0::func_ov068_02269450, &Obj_ov068_022771c0::func_ov068_022693f0,
        &Obj_ov068_022771c0::func_ov068_02269314};

    if (state_1c >= 5) {
        goto done;
    }

    (this->*table[state_1c])(arg);

done:
    return 0;
}
