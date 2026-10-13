/* func_ov004_0222cafc @ 0x0222cafc, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_02254c5819func_ov004_0222cafcEv
 */

#include "cpp/ov004/Obj_ov004_02254c58.h"

typedef void (Obj_ov004_02254c58::*Pmf)(void);

void Obj_ov004_02254c58::func_ov004_0222cafc()
{
    static Pmf tbl[] = {&Obj_ov004_02254c58::func_ov004_0222cac0, &Obj_ov004_02254c58::func_ov004_0222ca34,
                        &Obj_ov004_02254c58::func_ov004_0222c9b8, &Obj_ov004_02254c58::func_ov004_0222c934};
    unsigned char i = unk_24c;
    if (i < 4) {
        (this->*(tbl[i]))();
    }
}
