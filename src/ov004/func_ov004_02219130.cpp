/* func_ov004_02219130 @ 0x02219130, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_022518e819func_ov004_02219130Ev
 */

#include "cpp/ov004/Obj_ov004_022518e8.h"

typedef void (Obj_ov004_022518e8::*Pmf)(void);

void Obj_ov004_022518e8::func_ov004_02219130()
{
    static Pmf tbl[] = {&Obj_ov004_022518e8::func_ov004_022190b4, &Obj_ov004_022518e8::func_ov004_02219034,
                        &Obj_ov004_022518e8::func_ov004_02218fb4, &Obj_ov004_022518e8::func_ov004_02218f28};
    unsigned char i = unk_845;
    if (i < 4) {
        (this->*(tbl[i]))();
    }
}
