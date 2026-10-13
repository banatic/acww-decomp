/* func_ov004_0222f908 @ 0x0222f908, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_022553d819func_ov004_0222f908Ev
 */

#include "cpp/ov004/Obj_ov004_022553d8.h"

typedef void (Obj_ov004_022553d8::*Pmf)(void);

void Obj_ov004_022553d8::func_ov004_0222f908()
{
    static Pmf tbl[] = {&Obj_ov004_022553d8::func_ov004_0222f8cc, &Obj_ov004_022553d8::func_ov004_0222f854,
                        &Obj_ov004_022553d8::func_ov004_0222f818, &Obj_ov004_022553d8::func_ov004_0222f7a0};
    unsigned char i = unk_24c;
    if (i < 4) {
        (this->*(tbl[i]))();
    }
}
