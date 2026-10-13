/* func_ov004_0222f6e8 @ 0x0222f6e8, 0xb8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_022553d8.h"

typedef int (Obj_ov004_022553d8::*Pmf)(void);

extern "C" int func_ov004_0222f6e8(Obj_ov004_022553d8 *self, int i)
{
    {
        static Pmf tbl[] = {&Obj_ov004_022553d8::func_ov004_0222f63c, &Obj_ov004_022553d8::func_ov004_0222f5f0,
                            &Obj_ov004_022553d8::func_ov004_0222f5c8, &Obj_ov004_022553d8::func_ov004_0222f584,
                            &Obj_ov004_022553d8::func_ov004_0222f54c, &Obj_ov004_022553d8::func_ov004_0222f518};
        if (i < 6) {
            if ((self->*(tbl[i]))()) {
                self->unk_61c = i;
                return 1;
            }
        }
    }
    return 0;
}
