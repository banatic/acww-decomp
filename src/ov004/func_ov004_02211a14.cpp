/* func_ov004_02211a14 @ 0x02211a14, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_0225295019func_ov004_02211a14Ev
 */

#include "cpp/ov004/Obj_ov004_02252950.h"

typedef void (Obj_ov004_02252950::*Pmf)(void);

void Obj_ov004_02252950::func_ov004_02211a14()
{
    static Pmf tbl[] = {&Obj_ov004_02252950::func_ov004_022119f4, &Obj_ov004_02252950::func_ov004_022119bc,
                        &Obj_ov004_02252950::func_ov004_0221199c, &Obj_ov004_02252950::func_ov004_02211964};
    unsigned char i = unk_854;
    if (i < 4) {
        (this->*(tbl[i]))();
    }
}
