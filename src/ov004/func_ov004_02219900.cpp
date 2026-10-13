/* func_ov004_02219900 @ 0x02219900, 0x90 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_022525cc.h"

typedef int (Obj_ov004_022525cc::*Pmf)(void);

extern "C" void func_ov004_0220fdc8(Obj_ov004_022525cc *self, unsigned int i);

extern "C" int func_ov004_02219900(Obj_ov004_022525cc *self, unsigned int i)
{
    func_ov004_0220fdc8(self, i);
    {
        static Pmf tbl[] = {&Obj_ov004_022525cc::func_ov004_0221984c, &Obj_ov004_022525cc::func_ov004_022197e0,
                            &Obj_ov004_022525cc::func_ov004_0221977c};
        if (i < 3) {
            if ((self->*(tbl[i]))()) {
                self->unk_844 = (unsigned char) i;
                return 1;
            }
        }
    }
    return 0;
}
