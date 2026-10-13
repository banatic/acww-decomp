/* func_ov004_02219c00 @ 0x02219c00, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_02251a1419func_ov004_02219c00Ev
 */

#include "cpp/ov004/Obj_ov004_02251a14.h"

typedef void (Obj_ov004_02251a14::*Pmf)(void);

void Obj_ov004_02251a14::func_ov004_02219c00()
{
    static Pmf tbl[] = {&Obj_ov004_02251a14::func_ov004_02219ba4, &Obj_ov004_02251a14::func_ov004_02219b38};
    unsigned char i = unk_844;
    if (i < 2) {
        (this->*(tbl[i]))();
    }
}
