/* func_ov004_02215cdc @ 0x02215cdc, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_02251438.h"

typedef int (Obj_ov004_02251438::*Pmf)(void);

extern "C" void func_ov004_0220fdc8(Obj_ov004_02251438 *self, unsigned int i);

extern "C" int func_ov004_02215cdc(Obj_ov004_02251438 *self, unsigned int i)
{
    func_ov004_0220fdc8(self, i);
    {
        static Pmf tbl[] = {&Obj_ov004_02251438::func_ov004_02215c34, &Obj_ov004_02251438::func_ov004_02215bd0};
        if (i < 2) {
            if ((self->*(tbl[i]))()) {
                self->unk_844 = (unsigned char) i;
                return 1;
            }
        }
    }
    return 0;
}
