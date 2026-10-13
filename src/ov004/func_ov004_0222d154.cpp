/* func_ov004_0222d154 @ 0x0222d154, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_02254e4c19func_ov004_0222d154Ev
 */

#include "cpp/ov004/Obj_ov004_02254e4c.h"

typedef void (Obj_ov004_02254e4c::*Pmf)(void);

void Obj_ov004_02254e4c::func_ov004_0222d154()
{
    static Pmf tbl[] = {&Obj_ov004_02254e4c::func_ov004_0222d0bc, &Obj_ov004_02254e4c::func_ov004_0222cfbc,
                        &Obj_ov004_02254e4c::func_ov004_0222cf18, &Obj_ov004_02254e4c::func_ov004_0222ce1c};
    unsigned char i = unk_24c;
    if (i < 4) {
        (this->*(tbl[i]))();
    }
}
