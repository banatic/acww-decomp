/* func_ov004_0221dc70 @ 0x0221dc70, 0xb4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_0225386819func_ov004_0221dc70Ev
 */

#include "cpp/ov004/Obj_ov004_02253868.h"

typedef void (Obj_ov004_02253868::*Pmf)(void);

void Obj_ov004_02253868::func_ov004_0221dc70()
{
    static Pmf tbl[] = {&Obj_ov004_02253868::func_ov004_0221d92c, &Obj_ov004_02253868::func_ov004_0221d7e0,
                        &Obj_ov004_02253868::func_ov004_0221d73c, &Obj_ov004_02253868::func_ov004_0221d698,
                        &Obj_ov004_02253868::func_ov004_0221d660, &Obj_ov004_02253868::func_ov004_0221d620,
                        &Obj_ov004_02253868::func_ov004_0221d5fc};
    int i = unk_898;
    if (i < 7) {
        (this->*(tbl[i]))();
    }
}
