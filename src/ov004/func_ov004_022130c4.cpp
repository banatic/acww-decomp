/* func_ov004_022130c4 @ 0x022130c4, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_0225156419func_ov004_022130c4Ev
 */

#include "cpp/ov004/Obj_ov004_02251564.h"

typedef void (Obj_ov004_02251564::*Pmf)(void);

void Obj_ov004_02251564::func_ov004_022130c4()
{
    static Pmf tbl[] = {&Obj_ov004_02251564::func_ov004_02213074, &Obj_ov004_02251564::func_ov004_02213008};
    unsigned char i = unk_844;
    if (i < 2) {
        (this->*(tbl[i]))();
    }
}
