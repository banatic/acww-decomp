/* func_ov004_0222e73c @ 0x0222e73c, 0xf0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_02254fc8.h"

typedef int (Obj_ov004_02254fc8::*Pmf)(void);

extern "C" int func_ov004_0222e73c(Obj_ov004_02254fc8 *self, int i)
{
    {
        static Pmf tbl[] = {&Obj_ov004_02254fc8::func_ov004_0222e644, &Obj_ov004_02254fc8::func_ov004_0222e5a0,
                            &Obj_ov004_02254fc8::func_ov004_0222e4f8, &Obj_ov004_02254fc8::func_ov004_0222e44c,
                            &Obj_ov004_02254fc8::func_ov004_0222e220, &Obj_ov004_02254fc8::func_ov004_0222e1b4,
                            &Obj_ov004_02254fc8::func_ov004_0222e124, &Obj_ov004_02254fc8::func_ov004_0222e44c,
                            &Obj_ov004_02254fc8::func_ov004_0222e0a0, &Obj_ov004_02254fc8::func_ov004_0222df3c};
        if (i < 10) {
            if ((self->*(tbl[i]))()) {
                self->unk_efc = i;
                return 1;
            }
        }
    }
    return 0;
}
