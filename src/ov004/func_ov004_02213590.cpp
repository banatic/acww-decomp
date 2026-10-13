/* func_ov004_02213590 @ 0x02213590, 0x9c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_02251b40.h"

typedef int (Obj_ov004_02251b40::*Pmf)(void);

extern "C" int func_ov004_02213590(Obj_ov004_02251b40 *self, int i)
{
    {
        static Pmf tbl[] = {&Obj_ov004_02251b40::func_ov004_02213500, &Obj_ov004_02251b40::func_ov004_022134d8,
                            &Obj_ov004_02251b40::func_ov004_02213450, &Obj_ov004_02251b40::func_ov004_02213428};
        if (i < 4) {
            if ((self->*(tbl[i]))()) {
                self->unk_844 = i;
                return 1;
            }
        }
    }
    return 0;
}
