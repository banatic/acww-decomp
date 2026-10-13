/* func_ov004_0221b570 @ 0x0221b570, 0x9c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_022533e0.h"

typedef int (Obj_ov004_022533e0::*Pmf)(void);

extern "C" int func_ov004_0221b570(Obj_ov004_022533e0 *self, int i)
{
    {
        static Pmf tbl[] = {&Obj_ov004_022533e0::func_ov004_0221b4e0, &Obj_ov004_022533e0::func_ov004_0221b3ac,
                            &Obj_ov004_022533e0::func_ov004_0221b384, &Obj_ov004_022533e0::func_ov004_0221b2b8};
        if (i < 4) {
            if ((self->*(tbl[i]))()) {
                self->unk_134 = i;
                return 1;
            }
        }
    }
    return 0;
}
