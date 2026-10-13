/* func_ov100_0229e954 @ 0x0229e954, 0xbc bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov100_0229ecb819func_ov100_0229e954Ev
 */

#include "cpp/ov100/Obj_ov100_0229ecb8.h"

extern "C" void func_ov100_0229e374(Obj_ov100_0229ecb8 *);
extern "C" void func_ov100_0229e33c(Obj_ov100_0229ecb8 *);

int Obj_ov100_0229ecb8::func_ov100_0229e954()
{
    static void (Obj_ov100_0229ecb8::*table[7])() = {
        &Obj_ov100_0229ecb8::func_ov100_0229e77c, &Obj_ov100_0229ecb8::func_ov100_0229e6ec,
        &Obj_ov100_0229ecb8::func_ov100_0229e668, &Obj_ov100_0229ecb8::func_ov100_0229e62c,
        &Obj_ov100_0229ecb8::func_ov100_0229e5b8, &Obj_ov100_0229ecb8::func_ov100_0229e54c,
        &Obj_ov100_0229ecb8::func_ov100_0229e4fc};
    func_ov100_0229e374(this);
    (this->*table[state])();
    func_ov100_0229e33c(this);
    return 1;
}
