/* func_ov004_0220c144 @ 0x0220c144, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_0224fc4c.h"

extern "C" int func_ov004_0220c144(Obj_ov004_0224fc4c *obj, int idx)
{
    static int (Obj_ov004_0224fc4c::*pmf[3])() = {&Obj_ov004_0224fc4c::func_ov004_0220c0c4,
                                                  &Obj_ov004_0224fc4c::func_ov004_0220c078,
                                                  &Obj_ov004_0224fc4c::func_ov004_0220c050};
    if (idx < 3) {
        if ((obj->*pmf[idx])()) {
            obj->unk_134 = idx;
            return 1;
        }
    }
    return 0;
}
