/* func_ov004_0222fef8 @ 0x0222fef8, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_0225553819func_ov004_0222fef8Ev
 */

#include "cpp/ov004/Obj_ov004_02255538.h"

typedef void (Obj_ov004_02255538::*Pmf)(void);

void Obj_ov004_02255538::func_ov004_0222fef8()
{
    static Pmf tbl[] = {&Obj_ov004_02255538::func_ov004_0222fef0, &Obj_ov004_02255538::func_ov004_0222feac,
                        &Obj_ov004_02255538::func_ov004_0222fe50, &Obj_ov004_02255538::func_ov004_0222fddc};
    unsigned char i = unk_24c;
    if (i < 4) {
        (this->*(tbl[i]))();
    }
}
