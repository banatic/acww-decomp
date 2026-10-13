/* func_ov004_02212d78 @ 0x02212d78, 0x98 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_0225130c19func_ov004_02212d78Ev
 */

#include "cpp/ov004/Obj_ov004_0225130c.h"

typedef void (Obj_ov004_0225130c::*Pmf)(void);

void Obj_ov004_0225130c::func_ov004_02212d78()
{
    static Pmf tbl[] = {&Obj_ov004_0225130c::func_ov004_02212d1c, &Obj_ov004_0225130c::func_ov004_02212c90,
                        &Obj_ov004_0225130c::func_ov004_02212bb0, &Obj_ov004_0225130c::func_ov004_02212ab8,
                        &Obj_ov004_0225130c::func_ov004_02212a14};
    unsigned char i = unk_847;
    if (i < 5) {
        (this->*(tbl[i]))();
    }
}
