/* func_ov004_02213ee0 @ 0x02213ee0, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_02252374.h"

typedef int (Obj_ov004_02252374::*Pmf)(void);

extern "C" int func_ov004_0220fdc8(Obj_ov004_02252374 *self, unsigned int i, int parameter2);

extern "C" int func_ov004_02213ee0(Obj_ov004_02252374 *self, unsigned int i, int arg2)
{
    func_ov004_0220fdc8(self, i, arg2);
    {
        static Pmf tbl[] = {&Obj_ov004_02252374::func_ov004_02213e24, &Obj_ov004_02252374::func_ov004_02213d84};
        if (i < 2) {
            if ((self->*(tbl[i]))()) {
                self->unk_874 = (unsigned char) i;
                return 1;
            }
        }
    }
    return 0;
}
