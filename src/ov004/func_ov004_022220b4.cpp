/* func_ov004_022220b4 @ 0x022220b4, 0xc4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_022541d819func_ov004_022220b4Ev
 */

#include "cpp/ov004/Obj_ov004_022541d8.h"

typedef void (Obj_ov004_022541d8::*Pmf)(void);

void Obj_ov004_022541d8::func_ov004_022220b4()
{
    static Pmf tbl[] = {&Obj_ov004_022541d8::func_ov004_02221e0c, &Obj_ov004_022541d8::func_ov004_02221d64,
                        &Obj_ov004_022541d8::func_ov004_02221d30, &Obj_ov004_022541d8::func_ov004_02221cf0,
                        &Obj_ov004_022541d8::func_ov004_02221ccc, &Obj_ov004_022541d8::func_ov004_02221c88,
                        &Obj_ov004_022541d8::func_ov004_02221c80, &Obj_ov004_022541d8::func_ov004_02221c70};
    int i = unk_89c;
    if (i < 8) {
        (this->*(tbl[i]))();
    }
}
