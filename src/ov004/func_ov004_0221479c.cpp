/* func_ov004_0221479c @ 0x0221479c, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_0225282419func_ov004_0221479cEv
 */

#include "cpp/ov004/Obj_ov004_02252824.h"

typedef void (Obj_ov004_02252824::*Pmf)(void);

#define DISCARD_HANDLER(Class, Method) (Pmf) & Class::Method

void Obj_ov004_02252824::func_ov004_0221479c()
{
    static Pmf tbl[] = {&Obj_ov004_02252824::func_ov004_02214704, &Obj_ov004_02252824::func_ov004_02214610,
                        DISCARD_HANDLER(Obj_ov004_02252824, func_ov004_02214568), &Obj_ov004_02252824::func_ov004_02214474};
    unsigned char i = unk_844;
    if (i < 4) {
        (this->*(tbl[i]))();
    }
}

#undef DISCARD_HANDLER
