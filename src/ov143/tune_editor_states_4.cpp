/* tune_editor_states_4: 2 functions, module ov143
 * mwccarm 1.2/base -O4,s
 * func_ov143_0229ac10 @ 0x0229ac10, 0xe8 bytes, Thumb, emits _ZN18Obj_ov143_0229b1c019func_ov143_0229ac10Ev
 * func_ov143_0229abf4 @ 0x0229abf4, 0x1c bytes, Thumb, emits _ZN18Obj_ov143_0229b1c019func_ov143_0229abf4Ev
 */

#include "cpp/ov143/Obj_ov143_0229b1c0.h"

extern "C" void func_ov143_0229a94c(int);
extern "C" void func_ov143_0229a944(int);

void Obj_ov143_0229b1c0::func_ov143_0229ac10()
{
    static void (Obj_ov143_0229b1c0::*table[11])() = {
        &Obj_ov143_0229b1c0::func_ov143_0229a76c, &Obj_ov143_0229b1c0::func_ov143_0229a6f8,
        &Obj_ov143_0229b1c0::func_ov143_0229a67c, &Obj_ov143_0229b1c0::func_ov143_0229a5cc,
        &Obj_ov143_0229b1c0::func_ov143_0229a5a4, &Obj_ov143_0229b1c0::func_ov143_0229a570,
        &Obj_ov143_0229b1c0::func_ov143_0229a54c, &Obj_ov143_0229b1c0::func_ov143_0229a4e0,
        &Obj_ov143_0229b1c0::func_ov143_0229a438, &Obj_ov143_0229b1c0::func_ov143_0229a374,
        &Obj_ov143_0229b1c0::func_ov143_0229a334};
    (this->*table[subState])();
}

int Obj_ov143_0229b1c0::func_ov143_0229abf4()
{
    int arg = (int) this;
    func_ov143_0229a94c(arg);
    ((Obj_ov143_0229b1c0 *) arg)->func_ov143_0229ac10();
    func_ov143_0229a944(arg);
    return 1;
}
