/* func_ov107_0229e048 @ 0x0229e048, 0xa0 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov107_0229e3b819func_ov107_0229e048Ev
 */

#include "cpp/ov107/Obj_ov107_0229e3b8.h"

extern "C" void func_ov107_0229dbb4(Obj_ov107_0229e3b8 *self);
extern "C" void func_ov107_0229db7c(Obj_ov107_0229e3b8 *self);

int Obj_ov107_0229e3b8::func_ov107_0229e048()
{
    static void (Obj_ov107_0229e3b8::*tbl[5])() = {
        &Obj_ov107_0229e3b8::func_ov107_0229de54, &Obj_ov107_0229e3b8::func_ov107_0229ddc4,
        &Obj_ov107_0229e3b8::func_ov107_0229dd88, &Obj_ov107_0229e3b8::func_ov107_0229dd28,
        &Obj_ov107_0229e3b8::func_ov107_0229dcdc};

    func_ov107_0229dbb4(this);
    (this->*tbl[state])();
    func_ov107_0229db7c(this);
    return 1;
}
