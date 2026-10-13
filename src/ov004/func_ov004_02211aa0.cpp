/* func_ov004_02211aa0 @ 0x02211aa0, 0xa0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_02252950.h"

typedef int (Obj_ov004_02252950::*Pmf)(void);

extern "C" void func_ov004_0220fdc8(Obj_ov004_02252950 *self, unsigned int i);

extern "C" int func_ov004_02211aa0(Obj_ov004_02252950 *self, unsigned int i)
{
    func_ov004_0220fdc8(self, i);
    {
        static Pmf tbl[] = {&Obj_ov004_02252950::func_ov004_022119f8, &Obj_ov004_02252950::func_ov004_022119d0,
                            &Obj_ov004_02252950::func_ov004_022119a0, &Obj_ov004_02252950::func_ov004_02211978};
        if (i < 4) {
            if ((self->*(tbl[i]))()) {
                self->unk_854 = (unsigned char) i;
                return 1;
            }
        }
    }
    return 0;
}
