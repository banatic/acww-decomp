/* func_ov004_02212e10 @ 0x02212e10, 0xac bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_0225130c.h"

typedef int (Obj_ov004_0225130c::*Pmf)(void);

extern "C" int func_ov004_0220fdc8(Obj_ov004_0225130c *self, unsigned int i, int parameter2);

extern "C" int func_ov004_02212e10(Obj_ov004_0225130c *self, unsigned int i, int arg2)
{
    func_ov004_0220fdc8(self, i, arg2);
    {
        static Pmf tbl[] = {&Obj_ov004_0225130c::func_ov004_02212d44, &Obj_ov004_0225130c::func_ov004_02212ce4,
                            &Obj_ov004_0225130c::func_ov004_02212c64, &Obj_ov004_0225130c::func_ov004_02212b70,
                            &Obj_ov004_0225130c::func_ov004_02212a84};
        if (i < 5) {
            if ((self->*(tbl[i]))()) {
                self->unk_847 = (unsigned char) i;
                return 1;
            }
        }
    }
    return 0;
}
