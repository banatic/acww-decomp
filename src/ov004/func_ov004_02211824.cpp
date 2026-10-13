/* func_ov004_02211824 @ 0x02211824, 0x98 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_0225295019func_ov004_02211824Ev
 */

#include "cpp/ov004/Obj_ov004_02252950.h"

typedef void (Obj_ov004_02252950::*Pmf)(void);

void Obj_ov004_02252950::func_ov004_02211824()
{
    static Pmf tbl[] = {&Obj_ov004_02252950::func_ov004_022117b0, &Obj_ov004_02252950::func_ov004_02211764,
                        &Obj_ov004_02252950::func_ov004_022116fc, &Obj_ov004_02252950::func_ov004_022116c4,
                        &Obj_ov004_02252950::func_ov004_0221167c};
    int i = unk_858;
    if (i < 5) {
        (this->*(tbl[i]))();
    }
}
