/* func_ov004_02222178 @ 0x02222178, 0xd4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_022541d8.h"

typedef int (Obj_ov004_022541d8::*Pmf)(void);

extern "C" int func_ov004_02222178(Obj_ov004_022541d8 *self, int i)
{
    {
        static Pmf tbl[] = {&Obj_ov004_022541d8::func_ov004_02222098, &Obj_ov004_022541d8::func_ov004_02221dd8,
                            &Obj_ov004_022541d8::func_ov004_02221d34, &Obj_ov004_022541d8::func_ov004_02221cfc,
                            &Obj_ov004_022541d8::func_ov004_02221cec, &Obj_ov004_022541d8::func_ov004_02221cbc,
                            &Obj_ov004_022541d8::func_ov004_02221c84, &Obj_ov004_022541d8::func_ov004_02221c7c};
        if (i < 8) {
            if ((self->*(tbl[i]))()) {
                self->unk_89c = i;
                return 1;
            }
        }
    }
    return 0;
}
