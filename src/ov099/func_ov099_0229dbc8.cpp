/* func_ov099_0229dbc8 @ 0x0229dbc8, 0x184 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov099_0229e04019func_ov099_0229dbc8Ev
 */

#include "cpp/ov099/Obj_ov099_0229e040.h"

typedef void (Obj_ov099_0229e040::*PMF)();

int Obj_ov099_0229e040::func_ov099_0229dbc8()
{
    func_ov099_0229d948();

    static struct {
        PMF a[16];
        PMF b[5];
    } tbl = {{&Obj_ov099_0229e040::func_ov099_0229d814, &Obj_ov099_0229e040::func_ov099_0229d7a4,
              &Obj_ov099_0229e040::func_ov099_0229d718, &Obj_ov099_0229e040::func_ov099_0229d698,
              &Obj_ov099_0229e040::func_ov099_0229d5c0, &Obj_ov099_0229e040::func_ov099_0229d518,
              &Obj_ov099_0229e040::func_ov099_0229d49c, &Obj_ov099_0229e040::func_ov099_0229d44c,
              &Obj_ov099_0229e040::func_ov099_0229d400, &Obj_ov099_0229e040::func_ov099_0229d3e0,
              &Obj_ov099_0229e040::func_ov099_0229d3b8, &Obj_ov099_0229e040::func_ov099_0229d388,
              &Obj_ov099_0229e040::func_ov099_0229d358, &Obj_ov099_0229e040::func_ov099_0229d304,
              &Obj_ov099_0229e040::func_ov099_0229d2bc, &Obj_ov099_0229e040::func_ov099_0229d278},
             {&Obj_ov099_0229e040::func_ov099_0229d240, &Obj_ov099_0229e040::func_ov099_0229d204,
              &Obj_ov099_0229e040::func_ov099_0229d1c0, &Obj_ov099_0229e040::func_ov099_0229d1a0,
              &Obj_ov099_0229e040::func_ov099_0229d168}};

    (this->*tbl.a[subState])();

    func_ov099_0229d940();
    return 1;
}
