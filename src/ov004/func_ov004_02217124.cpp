/* func_ov004_02217124 @ 0x02217124, 0x10c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_0225211c.h"

typedef int (Obj_ov004_0225211c::*Pmf)(void);

extern "C" int func_ov004_02217124(Obj_ov004_0225211c *self, int i)
{
    {
        static Pmf tbl[] = {&Obj_ov004_0225211c::func_ov004_02217024, &Obj_ov004_0225211c::func_ov004_0221701c,
                            &Obj_ov004_0225211c::func_ov004_02216fb0, &Obj_ov004_0225211c::func_ov004_02216f6c,
                            &Obj_ov004_0225211c::func_ov004_02216f34, &Obj_ov004_0225211c::func_ov004_02216ed4,
                            &Obj_ov004_0225211c::func_ov004_02216eb4, &Obj_ov004_0225211c::func_ov004_02216e50,
                            &Obj_ov004_0225211c::func_ov004_02216e0c, &Obj_ov004_0225211c::func_ov004_02216d1c,
                            &Obj_ov004_0225211c::func_ov004_02216cf4, &Obj_ov004_0225211c::func_ov004_02216c8c};
        if (i < 12) {
            if ((self->*(tbl[i]))()) {
                self->unk_864 = i;
                return 1;
            }
        }
    }
    return 0;
}
