/* func_ov110_0229e7cc @ 0x0229e7cc, 0x188 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov110_0229ecb819func_ov110_0229e7ccEv
 */

#include "cpp/ov110/Obj_ov110_0229ecb8.h"

typedef void (Obj_ov110_0229ecb8::*PMF)();

void Obj_ov110_0229ecb8::func_ov110_0229e7cc()
{
    static struct {
        PMF a[16];
        PMF b[6];
    } tbl = {
        {&Obj_ov110_0229ecb8::func_ov110_0229e14c, &Obj_ov110_0229ecb8::func_ov110_0229e0f8,
         &Obj_ov110_0229ecb8::func_ov110_0229e05c, &Obj_ov110_0229ecb8::func_ov110_0229df2c,
         &Obj_ov110_0229ecb8::func_ov110_0229ddb4, &Obj_ov110_0229ecb8::func_ov110_0229dcc0,
         &Obj_ov110_0229ecb8::func_ov110_0229dc40, &Obj_ov110_0229ecb8::func_ov110_0229dbf4,
         &Obj_ov110_0229ecb8::func_ov110_0229dba4, &Obj_ov110_0229ecb8::func_ov110_0229db70,
         &Obj_ov110_0229ecb8::func_ov110_0229db48, &Obj_ov110_0229ecb8::func_ov110_0229db18,
         &Obj_ov110_0229ecb8::func_ov110_0229daec, &Obj_ov110_0229ecb8::func_ov110_0229da98,
         &Obj_ov110_0229ecb8::func_ov110_0229da50, &Obj_ov110_0229ecb8::func_ov110_0229da00},
        {&Obj_ov110_0229ecb8::func_ov110_0229d9c8, &Obj_ov110_0229ecb8::func_ov110_0229d98c,
         &Obj_ov110_0229ecb8::func_ov110_0229d948, &Obj_ov110_0229ecb8::func_ov110_0229d928,
         &Obj_ov110_0229ecb8::func_ov110_0229d8f4, &Obj_ov110_0229ecb8::func_ov110_0229d8b0},
    };
    unsigned char idx;

    idx = subState;
    (this->*tbl.a[idx])();
}
