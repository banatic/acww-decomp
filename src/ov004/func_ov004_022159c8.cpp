/* func_ov004_022159c8 @ 0x022159c8, 0xa0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_02250f88.h"

typedef int (Obj_ov004_02250f88::*Pmf)(void);

extern "C" int func_ov004_0220fdc8(Obj_ov004_02250f88 *self, unsigned int i, int parameter2);

extern "C" int func_ov004_022159c8(Obj_ov004_02250f88 *self, unsigned int i, int arg2)
{
    func_ov004_0220fdc8(self, i, arg2);
    {
        static Pmf tbl[] = {&Obj_ov004_02250f88::func_ov004_022158f0, &Obj_ov004_02250f88::func_ov004_02215874,
                            &Obj_ov004_02250f88::func_ov004_022157fc, &Obj_ov004_02250f88::func_ov004_02215788};
        if (i < 4) {
            if ((self->*(tbl[i]))()) {
                self->unk_865 = (unsigned char) i;
                return 1;
            }
        }
    }
    return 0;
}
