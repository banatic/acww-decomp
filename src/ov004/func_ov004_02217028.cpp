/* func_ov004_02217028 @ 0x02217028, 0xfc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_0225211c19func_ov004_02217028Ev
 */

#include "cpp/ov004/Obj_ov004_0225211c.h"

typedef void (Obj_ov004_0225211c::*Pmf)(void);

void Obj_ov004_0225211c::func_ov004_02217028()
{
    static Pmf tbl[] = {&Obj_ov004_0225211c::func_ov004_02217020, &Obj_ov004_0225211c::func_ov004_02217010,
                        &Obj_ov004_0225211c::func_ov004_02216f80, &Obj_ov004_0225211c::func_ov004_02216f50,
                        &Obj_ov004_0225211c::func_ov004_02216f18, &Obj_ov004_0225211c::func_ov004_02216eb8,
                        &Obj_ov004_0225211c::func_ov004_02216ea8, &Obj_ov004_0225211c::func_ov004_02216e20,
                        &Obj_ov004_0225211c::func_ov004_02216df0, &Obj_ov004_0225211c::func_ov004_02216cf8,
                        &Obj_ov004_0225211c::func_ov004_02216cd0, &Obj_ov004_0225211c::func_ov004_02216c60};
    int i = unk_864;
    if (i < 12) {
        (this->*(tbl[i]))();
    }
}
