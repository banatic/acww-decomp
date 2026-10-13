/* func_ov004_02218ce8 @ 0x02218ce8, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_022510b419func_ov004_02218ce8Ev
 */

#include "cpp/ov004/Obj_ov004_022510b4.h"

typedef void (Obj_ov004_022510b4::*Pmf)(void);

void Obj_ov004_022510b4::func_ov004_02218ce8()
{
    static Pmf tbl[] = {&Obj_ov004_022510b4::func_ov004_02218c74, &Obj_ov004_022510b4::func_ov004_02218c0c,
                        &Obj_ov004_022510b4::func_ov004_02218b90, &Obj_ov004_022510b4::func_ov004_02218b2c};
    unsigned char i = unk_845;
    if (i < 4) {
        (this->*(tbl[i]))();
    }
}
