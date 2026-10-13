/* func_ov004_0221ae7c @ 0x0221ae7c, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_0225328c.h"

extern "C" int func_ov004_0221ae7c(Obj_ov004_0225328c *obj, int idx)
{
    typedef int (Obj_ov004_0225328c::*PMF)();
    static PMF table[3] = {&Obj_ov004_0225328c::func_ov004_0221adfc, &Obj_ov004_0225328c::func_ov004_0221adb0,
                           &Obj_ov004_0225328c::func_ov004_0221ad88};

    if (idx < 3) {
        if ((obj->*table[idx])()) {
            obj->unk_134 = idx;
            return 1;
        }
    }
    return 0;
}
