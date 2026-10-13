/* func_ov004_022141f0 @ 0x022141f0, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_022524a019func_ov004_022141f0Ev
 */

#include "cpp/ov004/Obj_ov004_022524a0.h"

typedef void (Obj_ov004_022524a0::*Pmf)(void);

void Obj_ov004_022524a0::func_ov004_022141f0()
{
    static Pmf tbl[] = {&Obj_ov004_022524a0::func_ov004_02214198, &Obj_ov004_022524a0::func_ov004_0221412c};
    unsigned char i = unk_844;
    if (i < 2) {
        (this->*(tbl[i]))();
    }
}
