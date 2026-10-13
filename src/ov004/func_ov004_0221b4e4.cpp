/* func_ov004_0221b4e4 @ 0x0221b4e4, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_022533e019func_ov004_0221b4e4Ev
 */

#include "cpp/ov004/Obj_ov004_022533e0.h"

typedef void (Obj_ov004_022533e0::*Pmf)(void);

void Obj_ov004_022533e0::func_ov004_0221b4e4()
{
    static Pmf tbl[] = {&Obj_ov004_022533e0::func_ov004_0221b4b0, &Obj_ov004_022533e0::func_ov004_0221b388,
                        &Obj_ov004_022533e0::func_ov004_0221b354, &Obj_ov004_022533e0::func_ov004_0221b294};
    int i = unk_134;
    if (i < 4) {
        (this->*(tbl[i]))();
    }
}
