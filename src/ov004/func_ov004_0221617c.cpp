/* func_ov004_0221617c @ 0x0221617c, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_022517bc.h"

typedef int (Obj_ov004_022517bc::*Pmf)(void);

extern "C" int func_ov004_0220fdc8(Obj_ov004_022517bc *self, unsigned int i, int parameter2);

extern "C" int func_ov004_0221617c(Obj_ov004_022517bc *self, unsigned int i, int arg2)
{
    func_ov004_0220fdc8(self, i, arg2);
    {
        static Pmf tbl[] = {&Obj_ov004_022517bc::func_ov004_022160b0, &Obj_ov004_022517bc::func_ov004_02215ff0};
        if (i < 2) {
            if ((self->*(tbl[i]))()) {
                self->unk_8a0 = (unsigned char) i;
                return 1;
            }
        }
    }
    return 0;
}
