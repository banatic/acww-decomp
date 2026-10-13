/* func_ov004_0221593c @ 0x0221593c, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_02250f8819func_ov004_0221593cEv
 */

#include "cpp/ov004/Obj_ov004_02250f88.h"

typedef void (Obj_ov004_02250f88::*Pmf)(void);

void Obj_ov004_02250f88::func_ov004_0221593c()
{
    static Pmf tbl[] = {&Obj_ov004_02250f88::func_ov004_022158c8, &Obj_ov004_02250f88::func_ov004_02215844,
                        &Obj_ov004_02250f88::func_ov004_022157d4, &Obj_ov004_02250f88::func_ov004_02215758};
    unsigned char i = unk_865;
    if (i < 4) {
        (this->*(tbl[i]))();
    }
}
