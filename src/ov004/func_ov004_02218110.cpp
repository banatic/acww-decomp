/* func_ov004_02218110 @ 0x02218110, 0x118 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_0225305819func_ov004_02218110Ev
 */

#include "cpp/ov004/Obj_ov004_02253058.h"

typedef void (Obj_ov004_02253058::*Pmf)(void);

void Obj_ov004_02253058::func_ov004_02218110()
{
    static Pmf tbl[] = {&Obj_ov004_02253058::func_ov004_02217f2c, &Obj_ov004_02253058::func_ov004_02217e0c,
                        &Obj_ov004_02253058::func_ov004_02217da8, &Obj_ov004_02253058::func_ov004_02217d68,
                        &Obj_ov004_02253058::func_ov004_02217cfc, &Obj_ov004_02253058::func_ov004_02217cb8,
                        &Obj_ov004_02253058::func_ov004_02217c70, &Obj_ov004_02253058::func_ov004_02217c58,
                        &Obj_ov004_02253058::func_ov004_02217c10, &Obj_ov004_02253058::func_ov004_02217bdc,
                        &Obj_ov004_02253058::func_ov004_02217b74, &Obj_ov004_02253058::func_ov004_02217af4,
                        &Obj_ov004_02253058::func_ov004_02217a38, &Obj_ov004_02253058::func_ov004_022179e8};
    unsigned char i = unk_85e;
    if (i < 14) {
        (this->*(tbl[i]))();
    }
}
