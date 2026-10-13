/* func_ov004_0221a1d4 @ 0x0221a1d4, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_02252f2c19func_ov004_0221a1d4Ev
 */

#include "cpp/ov004/Obj_ov004_02252f2c.h"

typedef void (Obj_ov004_02252f2c::*Pmf)(void);

void Obj_ov004_02252f2c::func_ov004_0221a1d4()
{
    static Pmf tbl[] = {&Obj_ov004_02252f2c::func_ov004_0221a17c, &Obj_ov004_02252f2c::func_ov004_0221a150};
    unsigned char i = unk_844;
    if (i < 2) {
        (this->*(tbl[i]))();
    }
}
