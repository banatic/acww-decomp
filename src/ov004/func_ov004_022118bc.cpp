/* func_ov004_022118bc @ 0x022118bc, 0xa8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_02252950.h"

typedef int (Obj_ov004_02252950::*Pmf)(void);

extern "C" int func_ov004_022118bc(Obj_ov004_02252950 *self, int i)
{
    {
        static Pmf tbl[] = {&Obj_ov004_02252950::func_ov004_02211820, &Obj_ov004_02252950::func_ov004_02211790,
                            &Obj_ov004_02252950::func_ov004_02211720, &Obj_ov004_02252950::func_ov004_022116f8,
                            &Obj_ov004_02252950::func_ov004_022116a4};
        if (i < 5) {
            if ((self->*(tbl[i]))()) {
                self->unk_858 = i;
                return 1;
            }
        }
    }
    return 0;
}
