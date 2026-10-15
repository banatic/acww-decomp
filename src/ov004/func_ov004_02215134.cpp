/* func_ov004_02215134 @ 0x02215134, 0x90 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_02252ba8.h"

typedef int (Obj_ov004_02252ba8::*Pmf)(void);

extern "C" int func_ov004_0220fdc8(Obj_ov004_02252ba8 *self, unsigned int i, int parameter2);

extern "C" int func_ov004_02215134(Obj_ov004_02252ba8 *self, unsigned int i, int arg2)
{
    func_ov004_0220fdc8(self, i, arg2);
    {
        static Pmf tbl[] = {&Obj_ov004_02252ba8::func_ov004_02215020, &Obj_ov004_02252ba8::func_ov004_02214df8,
                            &Obj_ov004_02252ba8::func_ov004_02214cd8};
        if (i < 3) {
            if ((self->*(tbl[i]))()) {
                self->unk_862 = (unsigned char) i;
                return 1;
            }
        }
    }
    return 0;
}
