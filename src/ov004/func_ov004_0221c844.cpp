/* func_ov004_0221c844 @ 0x0221c844, 0x128 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_02253674.h"

typedef int (Obj_ov004_02253674::*Pmf)(void);

extern "C" int func_ov004_0221c844(Obj_ov004_02253674 *self, int i)
{
    {
        static Pmf tbl[] = {&Obj_ov004_02253674::func_ov004_0221c6d4, &Obj_ov004_02253674::func_ov004_0221c410,
                            &Obj_ov004_02253674::func_ov004_0221c3fc, &Obj_ov004_02253674::func_ov004_0221c38c,
                            &Obj_ov004_02253674::func_ov004_0221c2dc, &Obj_ov004_02253674::func_ov004_0221c2a4,
                            &Obj_ov004_02253674::func_ov004_0221c294, &Obj_ov004_02253674::func_ov004_0221c270,
                            &Obj_ov004_02253674::func_ov004_0221c224, &Obj_ov004_02253674::func_ov004_0221c0ec,
                            &Obj_ov004_02253674::func_ov004_0221c0bc, &Obj_ov004_02253674::func_ov004_0221c084,
                            &Obj_ov004_02253674::func_ov004_0221c07c, &Obj_ov004_02253674::func_ov004_0221c074};
        if (i < 14) {
            if ((self->*(tbl[i]))()) {
                self->unk_898 = i;
                return 1;
            }
        }
    }
    return 0;
}
