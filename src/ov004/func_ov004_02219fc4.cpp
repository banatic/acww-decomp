/* func_ov004_02219fc4 @ 0x02219fc4, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_02252e00.h"

typedef int (Obj_ov004_02252e00::*Pmf)(void);

extern "C" int func_ov004_0220fdc8(Obj_ov004_02252e00 *self, unsigned int i, int parameter2);

extern "C" int func_ov004_02219fc4(Obj_ov004_02252e00 *self, unsigned int i, int arg2)
{
    func_ov004_0220fdc8(self, i, arg2);
    {
        static Pmf tbl[] = {&Obj_ov004_02252e00::func_ov004_02219f28, &Obj_ov004_02252e00::func_ov004_02219ed8};
        if (i < 2) {
            if ((self->*(tbl[i]))()) {
                self->unk_844 = (unsigned char) i;
                return 1;
            }
        }
    }
    return 0;
}
