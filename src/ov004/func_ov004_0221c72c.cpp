/* func_ov004_0221c72c @ 0x0221c72c, 0x118 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_0225367419func_ov004_0221c72cEv
 */

#include "cpp/ov004/Obj_ov004_02253674.h"

typedef void (Obj_ov004_02253674::*Pmf)(void);

#define DISCARD_HANDLER(Class, Method) (Pmf) & Class::Method

void Obj_ov004_02253674::func_ov004_0221c72c()
{
    static Pmf tbl[] = {&Obj_ov004_02253674::func_ov004_0221c494, &Obj_ov004_02253674::func_ov004_0221c40c,
                        &Obj_ov004_02253674::func_ov004_0221c39c, &Obj_ov004_02253674::func_ov004_0221c310,
                        &Obj_ov004_02253674::func_ov004_0221c2d8, &Obj_ov004_02253674::func_ov004_0221c298,
                        &Obj_ov004_02253674::func_ov004_0221c274, DISCARD_HANDLER(Obj_ov004_02253674, func_ov004_0221c264),
                        &Obj_ov004_02253674::func_ov004_0221c0f0, &Obj_ov004_02253674::func_ov004_0221c0cc,
                        &Obj_ov004_02253674::func_ov004_0221c088, &Obj_ov004_02253674::func_ov004_0221c080,
                        &Obj_ov004_02253674::func_ov004_0221c078, &Obj_ov004_02253674::func_ov004_0221c040};
    int i = unk_898;
    if (i < 14) {
        (this->*(tbl[i]))();
    }
}

#undef DISCARD_HANDLER
