/* func_ov101_0229dd54 @ 0x0229dd54, 0xa0 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov101_0229e07819func_ov101_0229dd54Ev
 */

#include "cpp/ov101/Obj_ov101_0229e078.h"

extern "C" void func_ov101_0229d8e0(Obj_ov101_0229e078 *self);
extern "C" void func_ov101_0229d8a8(Obj_ov101_0229e078 *self);

int Obj_ov101_0229e078::func_ov101_0229dd54()
{
    static void (Obj_ov101_0229e078::*tbl[5])() = {
        &Obj_ov101_0229e078::func_ov101_0229db60, &Obj_ov101_0229e078::func_ov101_0229dad4,
        &Obj_ov101_0229e078::func_ov101_0229da98, &Obj_ov101_0229e078::func_ov101_0229da38,
        &Obj_ov101_0229e078::func_ov101_0229d9ec};

    func_ov101_0229d8e0(this);
    (this->*tbl[state])();
    func_ov101_0229d8a8(this);

    return 1;
}
