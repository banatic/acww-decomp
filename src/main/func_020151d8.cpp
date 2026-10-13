/* func_020151d8 @ 0x020151d8, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_020151d8Ev
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef int (Obj_020d8bd4::*Pmf)();
int Obj_020d8bd4::func_020151d8()
{
    static Pmf tbl[] = {&Obj_020d8bd4::func_020152a4, &Obj_020d8bd4::func_02015248};
    int r = 0;
    unsigned char i = unk_AC;
    if (i < 2) {
        r = (this->*(tbl[i]))();
    }
    return r;
}
