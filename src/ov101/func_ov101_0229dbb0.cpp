/* func_ov101_0229dbb0 @ 0x0229dbb0, 0x1a4 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov101_0229e07819func_ov101_0229dbb0Ev
 */

#include "cpp/ov101/Obj_ov101_0229e078.h"

typedef void (Obj_ov101_0229e078::*PMF)();

void Obj_ov101_0229e078::func_ov101_0229dbb0()
{
    static struct {
        PMF a[16];
        PMF b[8];
    } table = {{&Obj_ov101_0229e078::func_ov101_0229d7c0, &Obj_ov101_0229e078::func_ov101_0229d720,
                &Obj_ov101_0229e078::func_ov101_0229d704, &Obj_ov101_0229e078::func_ov101_0229d6bc,
                &Obj_ov101_0229e078::func_ov101_0229d624, &Obj_ov101_0229e078::func_ov101_0229d5a8,
                &Obj_ov101_0229e078::func_ov101_0229d4b4, &Obj_ov101_0229e078::func_ov101_0229d410,
                &Obj_ov101_0229e078::func_ov101_0229d398, &Obj_ov101_0229e078::func_ov101_0229d34c,
                &Obj_ov101_0229e078::func_ov101_0229d2fc, &Obj_ov101_0229e078::func_ov101_0229d2c4,
                &Obj_ov101_0229e078::func_ov101_0229d29c, &Obj_ov101_0229e078::func_ov101_0229d26c,
                &Obj_ov101_0229e078::func_ov101_0229d240, &Obj_ov101_0229e078::func_ov101_0229d1f0},
               {&Obj_ov101_0229e078::func_ov101_0229d1a8, &Obj_ov101_0229e078::func_ov101_0229d168,
                &Obj_ov101_0229e078::func_ov101_0229d134, &Obj_ov101_0229e078::func_ov101_0229d0f8,
                &Obj_ov101_0229e078::func_ov101_0229d0a8, &Obj_ov101_0229e078::func_ov101_0229d088,
                &Obj_ov101_0229e078::func_ov101_0229d054, &Obj_ov101_0229e078::func_ov101_0229cff0}};
    (this->*table.a[subState])();
}
