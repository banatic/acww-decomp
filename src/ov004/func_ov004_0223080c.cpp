/* func_ov004_0223080c @ 0x0223080c, 0x9c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_02255674.h"

typedef int (Obj_ov004_02255674::*Pmf)(void);

extern "C" int func_ov004_0223080c(Obj_ov004_02255674 *self, int i)
{
    {
        static Pmf tbl[] = {&Obj_ov004_02255674::func_ov004_02230754, &Obj_ov004_02255674::func_ov004_022306d0,
                            &Obj_ov004_02255674::func_ov004_0223063c, &Obj_ov004_02255674::func_ov004_022305a0};
        if (i < 4) {
            if ((self->*(tbl[i]))()) {
                self->unk_6d8 = i;
                return 1;
            }
        }
    }
    return 0;
}
