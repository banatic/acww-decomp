/* func_ov004_022164a0 @ 0x022164a0, 0xb8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_022517bc.h"

typedef int (Obj_ov004_022517bc::*Pmf)(void);

extern "C" int func_ov004_022164a0(Obj_ov004_022517bc *self, int i)
{
    {
        static Pmf tbl[] = {&Obj_ov004_022517bc::func_ov004_022163f4, &Obj_ov004_022517bc::func_ov004_022163ec,
                            &Obj_ov004_022517bc::func_ov004_022163c4, &Obj_ov004_022517bc::func_ov004_0221635c,
                            &Obj_ov004_022517bc::func_ov004_0221626c, &Obj_ov004_022517bc::func_ov004_02216244};
        if (i < 6) {
            if ((self->*(tbl[i]))()) {
                self->unk_8a4 = i;
                return 1;
            }
        }
    }
    return 0;
}
