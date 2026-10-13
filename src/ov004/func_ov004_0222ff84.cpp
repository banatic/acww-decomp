/* func_ov004_0222ff84 @ 0x0222ff84, 0x9c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_02255538.h"

typedef int (Obj_ov004_02255538::*Pmf)(void);

extern "C" int func_ov004_0222ff84(Obj_ov004_02255538 *self, unsigned int i)
{
    {
        static Pmf tbl[] = {&Obj_ov004_02255538::func_ov004_0222fef4, &Obj_ov004_02255538::func_ov004_0222fed4,
                            &Obj_ov004_02255538::func_ov004_0222fea8, &Obj_ov004_02255538::func_ov004_0222fe38};
        if (i < 4) {
            if ((self->*(tbl[i]))()) {
                self->unk_24c = (unsigned char) i;
                return 1;
            }
        }
    }
    return 0;
}
