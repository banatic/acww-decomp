/* func_ov004_022121c8 @ 0x022121c8, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_022509ac.h"

typedef int (Obj_ov004_022509ac::*Pmf)(void);

extern "C" int func_ov004_0220fdc8(Obj_ov004_022509ac *self, unsigned int i, int parameter2);

extern "C" int func_ov004_022121c8(Obj_ov004_022509ac *self, unsigned int i, int arg2)
{
    func_ov004_0220fdc8(self, i, arg2);
    {
        static Pmf tbl[] = {&Obj_ov004_022509ac::func_ov004_02212124, &Obj_ov004_022509ac::func_ov004_022120b0};
        if (i < 2) {
            if ((self->*(tbl[i]))()) {
                self->unk_89c = (unsigned char) i;
                return 1;
            }
        }
    }
    return 0;
}
