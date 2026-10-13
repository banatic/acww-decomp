/* func_ov004_0222f640 @ 0x0222f640, 0xa8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_022553d819func_ov004_0222f640Ev
 */

#include "cpp/ov004/Obj_ov004_022553d8.h"

typedef void (Obj_ov004_022553d8::*Pmf)(void);

void Obj_ov004_022553d8::func_ov004_0222f640()
{
    static Pmf tbl[] = {&Obj_ov004_022553d8::func_ov004_0222f638, &Obj_ov004_022553d8::func_ov004_0222f5cc,
                        &Obj_ov004_022553d8::func_ov004_0222f590, &Obj_ov004_022553d8::func_ov004_0222f568,
                        &Obj_ov004_022553d8::func_ov004_0222f524, &Obj_ov004_022553d8::func_ov004_0222f4fc};
    int i = unk_61c;
    if (i < 6) {
        (this->*(tbl[i]))();
    }
}
