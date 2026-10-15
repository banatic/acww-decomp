/* func_ov004_0221215c @ 0x0221215c, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_022509ac19func_ov004_0221215cEv
 */

#include "cpp/ov004/Obj_ov004_022509ac.h"

typedef void (Obj_ov004_022509ac::*Pmf)(void);

#define DISCARD_HANDLER(Class, Method) (Pmf) & Class::Method

void Obj_ov004_022509ac::func_ov004_0221215c()
{
    static Pmf tbl[] = {DISCARD_HANDLER(Obj_ov004_022509ac, func_ov004_022120e8),
                        DISCARD_HANDLER(Obj_ov004_022509ac, func_ov004_0221206c)};
    unsigned char i = unk_89c;
    if (i < 2) {
        (this->*(tbl[i]))();
    }
}

#undef DISCARD_HANDLER
