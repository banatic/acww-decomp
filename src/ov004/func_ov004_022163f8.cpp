/* func_ov004_022163f8 @ 0x022163f8, 0xa8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_022517bc19func_ov004_022163f8Ev
 */

#include "cpp/ov004/Obj_ov004_022517bc.h"

typedef void (Obj_ov004_022517bc::*Pmf)(void);

void Obj_ov004_022517bc::func_ov004_022163f8()
{
    static Pmf tbl[] = {&Obj_ov004_022517bc::func_ov004_022163f0, &Obj_ov004_022517bc::func_ov004_022163e0,
                        &Obj_ov004_022517bc::func_ov004_02216360, &Obj_ov004_022517bc::func_ov004_02216350,
                        &Obj_ov004_022517bc::func_ov004_02216248, &Obj_ov004_022517bc::func_ov004_02216214};
    int i = unk_8a4;
    if (i < 6) {
        (this->*(tbl[i]))();
    }
}
