/* func_ov004_02219f58 @ 0x02219f58, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_02252e0019func_ov004_02219f58Ev
 */

#include "cpp/ov004/Obj_ov004_02252e00.h"

typedef void (Obj_ov004_02252e00::*Pmf)(void);

void Obj_ov004_02252e00::func_ov004_02219f58()
{
    static Pmf tbl[] = {&Obj_ov004_02252e00::func_ov004_02219f00, &Obj_ov004_02252e00::func_ov004_02219e54};
    unsigned char i = unk_844;
    if (i < 2) {
        (this->*(tbl[i]))();
    }
}
