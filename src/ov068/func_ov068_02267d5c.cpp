/* func_ov068_02267d5c @ 0x02267d5c, 0x64 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_022771c019func_ov068_02267d5cEi
 */

#include "cpp/ov068/Obj_ov068_022771c0.h"

int Obj_ov068_022771c0::func_ov068_02267d5c(int arg)
{
    static void (Obj_ov068_022771c0::*pmf[1])(int) = {&Obj_ov068_022771c0::func_ov068_02268020};
    if (state_1c < 1) {
        (this->*pmf[state_1c])(arg);
    }
    return 0;
}
