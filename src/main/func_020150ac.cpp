/* func_020150ac @ 0x020150ac, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_020150acEv
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef int (Obj_020d8bd4::*Pmf)();
int Obj_020d8bd4::func_020150ac()
{
    static Pmf tbl[] = {&Obj_020d8bd4::func_0201516c, &Obj_020d8bd4::func_0201511c};
    int r = 0;
    unsigned char i = unk_AC;
    if (i < 2) {
        r = (this->*(tbl[i]))();
    }
    return r;
}
