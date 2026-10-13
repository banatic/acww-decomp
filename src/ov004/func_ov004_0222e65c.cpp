/* func_ov004_0222e65c @ 0x0222e65c, 0xe0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_02254fc819func_ov004_0222e65cEv
 */

#include "cpp/ov004/Obj_ov004_02254fc8.h"

typedef void (Obj_ov004_02254fc8::*Pmf)(void);

void Obj_ov004_02254fc8::func_ov004_0222e65c()
{
    static Pmf tbl[] = {&Obj_ov004_02254fc8::func_ov004_0222e5a4, &Obj_ov004_02254fc8::func_ov004_0222e4fc,
                        &Obj_ov004_02254fc8::func_ov004_0222e450, &Obj_ov004_02254fc8::func_ov004_0222e25c,
                        &Obj_ov004_02254fc8::func_ov004_0222e1b8, &Obj_ov004_02254fc8::func_ov004_0222e128,
                        &Obj_ov004_02254fc8::func_ov004_0222e0b8, &Obj_ov004_02254fc8::func_ov004_0222e25c,
                        &Obj_ov004_02254fc8::func_ov004_0222df4c, &Obj_ov004_02254fc8::func_ov004_0222deb4};
    int i = unk_efc;
    if (i < 10) {
        (this->*(tbl[i]))();
    }
}
