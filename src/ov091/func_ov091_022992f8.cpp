/* func_ov091_022992f8 @ 0x022992f8, 0x74 bytes, Thumb, module ov091
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov091_0229953019func_ov091_022992f8Ev
 */

#include "cpp/ov091/Obj_ov091_02299530.h"

extern "C" void func_ov091_02299054(Obj_ov091_02299530 *p);
extern "C" void func_ov091_02299050(Obj_ov091_02299530 *p);

int Obj_ov091_02299530::func_ov091_022992f8()
{
    func_ov091_02299054(this);
    static void (Obj_ov091_02299530::*pmfTable[2])() = {&Obj_ov091_02299530::func_ov091_02299004,
                                                        &Obj_ov091_02299530::func_ov091_02298fb4};
    (this->*pmfTable[subState])();
    func_ov091_02299050(this);
    return 1;
}
