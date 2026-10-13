/* func_ov004_02219514 @ 0x02219514, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_0225224819func_ov004_02219514Ev
 */

#include "cpp/ov004/Obj_ov004_02252248.h"

typedef void (Obj_ov004_02252248::*Pmf)(void);

void Obj_ov004_02252248::func_ov004_02219514()
{
    static Pmf tbl[] = {&Obj_ov004_02252248::func_ov004_022194a0, &Obj_ov004_02252248::func_ov004_02219438,
                        &Obj_ov004_02252248::func_ov004_022193cc, &Obj_ov004_02252248::func_ov004_02219368};
    unsigned char i = unk_844;
    if (i < 4) {
        (this->*(tbl[i]))();
    }
}
