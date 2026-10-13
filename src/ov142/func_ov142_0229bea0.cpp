/* func_ov142_0229bea0 @ 0x0229bea0, 0xcc bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov142_0229c3e819func_ov142_0229bea0Ev
 */

#include "cpp/ov142/Obj_ov142_0229c3e8.h"

typedef int (Obj_ov142_0229c3e8::*PMF)();

int Obj_ov142_0229c3e8::func_ov142_0229bea0()
{
    static PMF table[8] = {&Obj_ov142_0229c3e8::func_ov142_0229bcfc, &Obj_ov142_0229c3e8::func_ov142_0229bc9c,
                           &Obj_ov142_0229c3e8::func_ov142_0229bc64, &Obj_ov142_0229c3e8::func_ov142_0229bc34,
                           &Obj_ov142_0229c3e8::func_ov142_0229bbf4, &Obj_ov142_0229c3e8::func_ov142_0229bbc4,
                           &Obj_ov142_0229c3e8::func_ov142_0229bb84, &Obj_ov142_0229c3e8::func_ov142_0229bb54};
    func_ov142_0229b99c();
    {
        int idx = state;
        (this->*table[idx])();
    }
    func_ov142_0229b974();
    return 1;
}
