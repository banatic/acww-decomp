/* func_ov004_022195a0 @ 0x022195a0, 0xa0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_02252248.h"

typedef int (Obj_ov004_02252248::*Pmf)(void);

extern "C" void func_ov004_0220fdc8(Obj_ov004_02252248 *self, unsigned int i);

extern "C" int func_ov004_022195a0(Obj_ov004_02252248 *self, unsigned int i)
{
    func_ov004_0220fdc8(self, i);
    {
        static Pmf tbl[] = {&Obj_ov004_02252248::func_ov004_022194e0, &Obj_ov004_02252248::func_ov004_02219468,
                            &Obj_ov004_02252248::func_ov004_0221940c, &Obj_ov004_02252248::func_ov004_02219398};
        if (i < 4) {
            if ((self->*(tbl[i]))()) {
                self->unk_844 = (unsigned char) i;
                return 1;
            }
        }
    }
    return 0;
}
