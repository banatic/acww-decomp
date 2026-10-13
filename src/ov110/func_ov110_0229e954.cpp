/* func_ov110_0229e954 @ 0x0229e954, 0xbc bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov110_0229ecb819func_ov110_0229e954Ev
 */

#include "cpp/ov110/Obj_ov110_0229ecb8.h"

int Obj_ov110_0229ecb8::func_ov110_0229e954()
{
    typedef void (Obj_ov110_0229ecb8::*PMF)();
    static PMF tbl[7] = {&Obj_ov110_0229ecb8::func_ov110_0229e718, &Obj_ov110_0229ecb8::func_ov110_0229e68c,
                         &Obj_ov110_0229ecb8::func_ov110_0229e60c, &Obj_ov110_0229ecb8::func_ov110_0229e5d4,
                         &Obj_ov110_0229ecb8::func_ov110_0229e564, &Obj_ov110_0229ecb8::func_ov110_0229e4fc,
                         &Obj_ov110_0229ecb8::func_ov110_0229e4b0};
    func_ov110_0229e330();
    (this->*tbl[state])();
    func_ov110_0229e2f8();
    return 1;
}
