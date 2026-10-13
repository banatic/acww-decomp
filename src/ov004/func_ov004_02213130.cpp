/* func_ov004_02213130 @ 0x02213130, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_02251564.h"

typedef int (Obj_ov004_02251564::*Pmf)(void);

extern "C" void func_ov004_0220fdc8(Obj_ov004_02251564 *self, unsigned int i);

extern "C" int func_ov004_02213130(Obj_ov004_02251564 *self, unsigned int i)
{
    func_ov004_0220fdc8(self, i);
    {
        static Pmf tbl[] = {&Obj_ov004_02251564::func_ov004_022130c0, &Obj_ov004_02251564::func_ov004_02213010};
        if (i < 2) {
            if ((self->*(tbl[i]))()) {
                self->unk_844 = (unsigned char) i;
                return 1;
            }
        }
    }
    return 0;
}
