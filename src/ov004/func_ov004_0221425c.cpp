/* func_ov004_0221425c @ 0x0221425c, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_022524a0.h"

typedef int (Obj_ov004_022524a0::*Pmf)(void);

extern "C" void func_ov004_0220fdc8(Obj_ov004_022524a0 *self, unsigned int i);

extern "C" int func_ov004_0221425c(Obj_ov004_022524a0 *self, unsigned int i)
{
    func_ov004_0220fdc8(self, i);
    {
        static Pmf tbl[] = {&Obj_ov004_022524a0::func_ov004_022141c0, &Obj_ov004_022524a0::func_ov004_02214160};
        if (i < 2) {
            if ((self->*(tbl[i]))()) {
                self->unk_844 = (unsigned char) i;
                return 1;
            }
        }
    }
    return 0;
}
