/* func_ov125_022a0714 @ 0x022a0714, 0xe8 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov125_022a0ab819func_ov125_022a0714Ev
 */

#include "cpp/ov125/Obj_ov125_022a0ab8.h"

typedef void (Obj_ov125_022a0ab8::*PMF)();

void Obj_ov125_022a0ab8::func_ov125_022a0714()
{
    static PMF tbl[11] = {&Obj_ov125_022a0ab8::func_ov125_022a02b4, &Obj_ov125_022a0ab8::func_ov125_022a0214,
                          &Obj_ov125_022a0ab8::func_ov125_022a012c, &Obj_ov125_022a0ab8::func_ov125_022a00ac,
                          &Obj_ov125_022a0ab8::func_ov125_022a0060, &Obj_ov125_022a0ab8::func_ov125_022a0030,
                          &Obj_ov125_022a0ab8::func_ov125_022a0000, &Obj_ov125_022a0ab8::func_ov125_0229ffc4,
                          &Obj_ov125_022a0ab8::func_ov125_0229ff80, &Obj_ov125_022a0ab8::func_ov125_0229ff60,
                          &Obj_ov125_022a0ab8::func_ov125_0229fefc};

    (this->*tbl[subState])();
}
