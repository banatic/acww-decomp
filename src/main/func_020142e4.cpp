/* func_020142e4 @ 0x020142e4, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_020142e4EPv
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef void (Obj_020d8bd4::*Pmf)(void *);
void Obj_020d8bd4::func_020142e4(void *arg)
{
    static Pmf tbl[] = {&Obj_020d8bd4::func_020144c8, &Obj_020d8bd4::func_020143d4, &Obj_020d8bd4::func_02014360};
    unsigned char i = unk_0A;
    if (i < 3) {
        (this->*(tbl[i]))(arg);
    }
}
