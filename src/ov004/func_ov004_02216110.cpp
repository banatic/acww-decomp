/* func_ov004_02216110 @ 0x02216110, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_022517bc19func_ov004_02216110Ev
 */

#include "cpp/ov004/Obj_ov004_022517bc.h"

typedef void (Obj_ov004_022517bc::*Pmf)(void);

#define DISCARD_HANDLER(Class, Method) (Pmf) & Class::Method

void Obj_ov004_022517bc::func_ov004_02216110()
{
    static Pmf tbl[] = {&Obj_ov004_022517bc::func_ov004_0221605c, DISCARD_HANDLER(Obj_ov004_022517bc, func_ov004_02215f8c)};
    unsigned char i = unk_8a0;
    if (i < 2) {
        (this->*(tbl[i]))();
    }
}

#undef DISCARD_HANDLER
