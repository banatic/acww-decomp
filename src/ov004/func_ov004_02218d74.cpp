/* func_ov004_02218d74 @ 0x02218d74, 0xa0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_022510b4.h"

typedef int (Obj_ov004_022510b4::*Pmf)(void);

extern "C" int func_ov004_0220fdc8(Obj_ov004_022510b4 *self, unsigned int i, int parameter2);

extern "C" int func_ov004_02218d74(Obj_ov004_022510b4 *self, unsigned int i, int arg2)
{
    func_ov004_0220fdc8(self, i, arg2);
    {
        static Pmf tbl[] = {&Obj_ov004_022510b4::func_ov004_02218cb4, &Obj_ov004_022510b4::func_ov004_02218c3c,
                            &Obj_ov004_022510b4::func_ov004_02218be0, &Obj_ov004_022510b4::func_ov004_02218b5c};
        if (i < 4) {
            if ((self->*(tbl[i]))()) {
                self->unk_845 = (unsigned char) i;
                return 1;
            }
        }
    }
    return 0;
}
