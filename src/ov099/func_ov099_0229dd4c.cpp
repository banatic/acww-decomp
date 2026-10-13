/* func_ov099_0229dd4c @ 0x0229dd4c, 0xa0 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov099_0229e04019func_ov099_0229dd4cEv
 */

#include "cpp/ov099/Obj_ov099_0229e040.h"

typedef void (Obj_ov099_0229e040::*PMF)();

int Obj_ov099_0229e040::func_ov099_0229dd4c()
{
    static PMF table[5] = {&Obj_ov099_0229e040::func_ov099_0229db94, &Obj_ov099_0229e040::func_ov099_0229db24,
                           &Obj_ov099_0229e040::func_ov099_0229dae8, &Obj_ov099_0229e040::func_ov099_0229da84,
                           &Obj_ov099_0229e040::func_ov099_0229da34};
    func_ov099_0229d910();
    (this->*table[state])();
    func_ov099_0229d8d8();
    return 1;
}
