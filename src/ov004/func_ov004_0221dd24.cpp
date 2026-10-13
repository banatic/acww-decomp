/* func_ov004_0221dd24 @ 0x0221dd24, 0xc4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_02253868.h"

typedef int (Obj_ov004_02253868::*Pmf)(void);

extern "C" int func_ov004_0221dd24(Obj_ov004_02253868 *self, int i)
{
    {
        static Pmf tbl[] = {&Obj_ov004_02253868::func_ov004_0221dc18, &Obj_ov004_02253868::func_ov004_0221d868,
                            &Obj_ov004_02253868::func_ov004_0221d784, &Obj_ov004_02253868::func_ov004_0221d6e0,
                            &Obj_ov004_02253868::func_ov004_0221d664, &Obj_ov004_02253868::func_ov004_0221d62c,
                            &Obj_ov004_02253868::func_ov004_0221d61c};
        if (i < 7) {
            if ((self->*(tbl[i]))()) {
                self->unk_898 = i;
                return 1;
            }
        }
    }
    return 0;
}
