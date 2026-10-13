/* func_ov004_022150b8 @ 0x022150b8, 0x7c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_02252ba819func_ov004_022150b8Ev
 */

#include "cpp/ov004/Obj_ov004_02252ba8.h"

typedef void (Obj_ov004_02252ba8::*Pmf)(void);

void Obj_ov004_02252ba8::func_ov004_022150b8()
{
    static Pmf tbl[] = {&Obj_ov004_02252ba8::func_ov004_02214fc8, &Obj_ov004_02252ba8::func_ov004_02214d34,
                        &Obj_ov004_02252ba8::func_ov004_02214c50};
    unsigned char i = unk_862;
    if (i < 3) {
        (this->*(tbl[i]))();
    }
}
