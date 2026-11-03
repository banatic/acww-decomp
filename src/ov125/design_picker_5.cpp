/* design_picker_5: 2 functions, module ov125
 * mwccarm 1.2/base -O4,s
 * func_ov125_022a0714 @ 0x022a0714, 0xe8 bytes, Thumb, emits _ZN18Obj_ov125_022a0ab819func_ov125_022a0714Ev
 * func_ov125_022a06f8 @ 0x022a06f8, 0x1c bytes, Thumb, emits _ZN18Obj_ov125_022a0ab819func_ov125_022a06f8Ev
 */

#include "cpp/ov125/Obj_ov125_022a0ab8.h"

typedef void (Obj_ov125_022a0ab8::*PMF)();

extern "C" void func_ov125_022a04c8(int arg);
extern "C" void func_ov125_022a04c0(int arg);

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

int Obj_ov125_022a0ab8::func_ov125_022a06f8()
{
    int arg = (int) this;
    func_ov125_022a04c8(arg);
    ((Obj_ov125_022a0ab8 *) arg)->func_ov125_022a0714();
    func_ov125_022a04c0(arg);
    return 1;
}
