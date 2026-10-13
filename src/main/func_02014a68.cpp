/* func_02014a68 @ 0x02014a68, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_02014a68Ev
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef int (Obj_020d8bd4::*Pmf)();
int Obj_020d8bd4::func_02014a68()
{
    static Pmf tbl[] = {&Obj_020d8bd4::func_02014b30, &Obj_020d8bd4::func_02014b14, &Obj_020d8bd4::func_02014ae8};
    unsigned char i = unk_AC;
    if (i < 3) {
        return (this->*(tbl[i]))();
    }
    return 0;
}
