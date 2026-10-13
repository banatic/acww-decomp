/* func_ov004_02213504 @ 0x02213504, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_02251b4019func_ov004_02213504Ev
 */

#include "cpp/ov004/Obj_ov004_02251b40.h"

typedef void (Obj_ov004_02251b40::*Pmf)(void);

void Obj_ov004_02251b40::func_ov004_02213504()
{
    static Pmf tbl[] = {&Obj_ov004_02251b40::func_ov004_022134dc, &Obj_ov004_02251b40::func_ov004_022134cc,
                        &Obj_ov004_02251b40::func_ov004_0221342c, &Obj_ov004_02251b40::func_ov004_022133f8};
    int i = unk_844;
    if (i < 4) {
        (this->*(tbl[i]))();
    }
}
