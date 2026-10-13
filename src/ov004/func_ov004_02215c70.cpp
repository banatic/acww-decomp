/* func_ov004_02215c70 @ 0x02215c70, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_0225143819func_ov004_02215c70Ev
 */

#include "cpp/ov004/Obj_ov004_02251438.h"

typedef void (Obj_ov004_02251438::*Pmf)(void);

void Obj_ov004_02251438::func_ov004_02215c70()
{
    static Pmf tbl[] = {&Obj_ov004_02251438::func_ov004_02215c0c, &Obj_ov004_02251438::func_ov004_02215ba8};
    unsigned char i = unk_844;
    if (i < 2) {
        (this->*(tbl[i]))();
    }
}
