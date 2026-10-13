/* func_ov004_02217580 @ 0x02217580, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_0225211c19func_ov004_02217580Ev
 */

#include "cpp/ov004/Obj_ov004_0225211c.h"

typedef void (Obj_ov004_0225211c::*Pmf)(void);

void Obj_ov004_0225211c::func_ov004_02217580()
{
    static Pmf tbl[] = {&Obj_ov004_0225211c::func_ov004_02217420, &Obj_ov004_0225211c::func_ov004_022173b8,
                        &Obj_ov004_0225211c::func_ov004_02217330, &Obj_ov004_0225211c::func_ov004_022172ac};
    unsigned char i = unk_860;
    if (i < 4) {
        (this->*(tbl[i]))();
    }
}
