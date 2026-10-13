/* func_ov004_02230780 @ 0x02230780, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_0225567419func_ov004_02230780Ev
 */

#include "cpp/ov004/Obj_ov004_02255674.h"

typedef void (Obj_ov004_02255674::*Pmf)(void);

void Obj_ov004_02255674::func_ov004_02230780()
{
    static Pmf tbl[] = {&Obj_ov004_02255674::func_ov004_02230750, &Obj_ov004_02255674::func_ov004_022306a8,
                        &Obj_ov004_02255674::func_ov004_02230620, &Obj_ov004_02255674::func_ov004_02230538};
    int i = unk_6d8;
    if (i < 4) {
        (this->*(tbl[i]))();
    }
}
