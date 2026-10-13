/* func_ov004_0222cb88 @ 0x0222cb88, 0x9c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_02254c58.h"

typedef int (Obj_ov004_02254c58::*Pmf)(void);

extern "C" int func_ov004_0222cb88(Obj_ov004_02254c58 *self, unsigned int i)
{
    {
        static Pmf tbl[] = {&Obj_ov004_02254c58::func_ov004_0222cac4, &Obj_ov004_02254c58::func_ov004_0222ca78,
                            &Obj_ov004_02254c58::func_ov004_0222c9fc, &Obj_ov004_02254c58::func_ov004_0222c964};
        if (i < 4) {
            if ((self->*(tbl[i]))()) {
                self->unk_24c = (unsigned char) i;
                return 1;
            }
        }
    }
    return 0;
}
