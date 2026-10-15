/* func_ov004_02218228 @ 0x02218228, 0x12c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_02253058.h"

typedef int (Obj_ov004_02253058::*Pmf)(void);

extern "C" int func_ov004_0220fdc8(Obj_ov004_02253058 *self, unsigned int i, int parameter2);

extern "C" int func_ov004_02218228(Obj_ov004_02253058 *self, unsigned int i, int arg2)
{
    func_ov004_0220fdc8(self, i, arg2);
    {
        static Pmf tbl[] = {&Obj_ov004_02253058::func_ov004_02218100, &Obj_ov004_02253058::func_ov004_02217eb8,
                            &Obj_ov004_02253058::func_ov004_02217e08, &Obj_ov004_02253058::func_ov004_02217d98,
                            &Obj_ov004_02253058::func_ov004_02217d00, &Obj_ov004_02253058::func_ov004_02217cf8,
                            &Obj_ov004_02253058::func_ov004_02217cb4, &Obj_ov004_02253058::func_ov004_02217c6c,
                            &Obj_ov004_02253058::func_ov004_02217c14, &Obj_ov004_02253058::func_ov004_02217c0c,
                            &Obj_ov004_02253058::func_ov004_02217bd8, &Obj_ov004_02253058::func_ov004_02217b70,
                            &Obj_ov004_02253058::func_ov004_02217ac4, &Obj_ov004_02253058::func_ov004_02217a28};
        if (i < 14) {
            if ((self->*(tbl[i]))()) {
                self->unk_85e = (unsigned char) i;
                return 1;
            }
        }
    }
    return 0;
}
