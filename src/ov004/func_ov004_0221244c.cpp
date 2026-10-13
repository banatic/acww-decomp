/* func_ov004_0221244c @ 0x0221244c, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_02250ad819func_ov004_0221244cEv
 */

#include "cpp/ov004/Obj_ov004_02250ad8.h"

typedef void (Obj_ov004_02250ad8::*Pmf)(void);

void Obj_ov004_02250ad8::func_ov004_0221244c()
{
    static Pmf tbl[] = {&Obj_ov004_02250ad8::func_ov004_02212408, &Obj_ov004_02250ad8::func_ov004_022123c4};
    unsigned char i = unk_844;
    if (i < 2) {
        (this->*(tbl[i]))();
    }
}
