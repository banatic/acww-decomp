/* func_02017370 @ 0x02017370, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_02017370EPv
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef void (Obj_020d8bd4::*Pmf)(void *);
void Obj_020d8bd4::func_02017370(void *arg)
{
    static Pmf tbl[] = {&Obj_020d8bd4::func_020173d8};
    unsigned char i = unk_98;
    if (i < 1) {
        (this->*(tbl[i]))(arg);
    }
}
