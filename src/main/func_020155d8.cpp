/* func_020155d8 @ 0x020155d8, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_020155d8Ev
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef int (Obj_020d8bd4::*Pmf)();
int Obj_020d8bd4::func_020155d8()
{
    static Pmf tbl[] = {&Obj_020d8bd4::func_02015760, &Obj_020d8bd4::func_02015688, &Obj_020d8bd4::func_02015654};
    int r = 0;
    unsigned char i = unk_AC;
    if (i < 3) {
        r = (this->*(tbl[i]))();
    }
    return r;
}
