/* func_02013c34 @ 0x02013c34, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_02013c34EPv
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef void (Obj_020d8bd4::*Pmf)(void *);
void Obj_020d8bd4::func_02013c34(void *arg)
{
    static Pmf tbl[3] = {&Obj_020d8bd4::func_02013c98};
    unsigned char i = unk_0A;
    if (i < 3) {
        (this->*(tbl[i]))(arg);
    }
}
