/* func_ov004_02219884 @ 0x02219884, 0x7c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_022525cc19func_ov004_02219884Ev
 */

#include "cpp/ov004/Obj_ov004_022525cc.h"

typedef void (Obj_ov004_022525cc::*Pmf)(void);

#define DISCARD_HANDLER(Class, Method) (Pmf) & Class::Method

void Obj_ov004_022525cc::func_ov004_02219884()
{
    static Pmf tbl[] = {&Obj_ov004_022525cc::func_ov004_02219824, DISCARD_HANDLER(Obj_ov004_022525cc, func_ov004_022197b0),
                        DISCARD_HANDLER(Obj_ov004_022525cc, func_ov004_0221974c)};
    unsigned char i = unk_844;
    if (i < 3) {
        (this->*(tbl[i]))();
    }
}

#undef DISCARD_HANDLER
