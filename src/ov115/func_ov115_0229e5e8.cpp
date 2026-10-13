/* func_ov115_0229e5e8 @ 0x0229e5e8, 0xcc bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov115_0229e8b819func_ov115_0229e5e8Ev
 */

#include "cpp/ov115/Obj_ov115_0229e8b8.h"

typedef int (Obj_ov115_0229e8b8::*PMF)();

int Obj_ov115_0229e8b8::func_ov115_0229e5e8()
{
    static PMF table[9] = {&Obj_ov115_0229e8b8::func_ov115_0229e228, &Obj_ov115_0229e8b8::func_ov115_0229e1f0,
                           &Obj_ov115_0229e8b8::func_ov115_0229e168, &Obj_ov115_0229e8b8::func_ov115_0229e140,
                           &Obj_ov115_0229e8b8::func_ov115_0229e0e8, &Obj_ov115_0229e8b8::func_ov115_0229e0c0,
                           &Obj_ov115_0229e8b8::func_ov115_0229e074, &Obj_ov115_0229e8b8::func_ov115_0229e010,
                           &Obj_ov115_0229e8b8::func_ov115_0229dfc0};
    int idx = subState;
    return (this->*table[idx])();
}
