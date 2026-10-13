/* func_02013d5c @ 0x02013d5c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_02013d5cEPv
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef void (Obj_020d8bd4::*Pmf)(void *);
void Obj_020d8bd4::func_02013d5c(void *arg)
{
    static Pmf tbl[] = {&Obj_020d8bd4::func_020141c4};
    unsigned char i = unk_0A;
    if (i < 1) {
        (this->*(tbl[i]))(arg);
    }
}
