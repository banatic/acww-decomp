/* func_ov004_02214828 @ 0x02214828, 0xa0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_02252824.h"

typedef int (Obj_ov004_02252824::*Pmf)(void);

extern "C" void func_ov004_0220fdc8(Obj_ov004_02252824 *self, unsigned int i);

extern "C" int func_ov004_02214828(Obj_ov004_02252824 *self, unsigned int i)
{
    func_ov004_0220fdc8(self, i);
    {
        static Pmf tbl[] = {&Obj_ov004_02252824::func_ov004_0221472c, &Obj_ov004_02252824::func_ov004_02214680,
                            &Obj_ov004_02252824::func_ov004_02214598, &Obj_ov004_02252824::func_ov004_022144e0};
        if (i < 4) {
            if ((self->*(tbl[i]))()) {
                self->unk_844 = (unsigned char) i;
                return 1;
            }
        }
    }
    return 0;
}
