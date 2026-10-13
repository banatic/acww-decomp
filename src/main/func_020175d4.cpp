/* func_020175d4 @ 0x020175d4, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_020175d4EPv
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef void (Obj_020d8bd4::*Pmf)(void *);
void Obj_020d8bd4::func_020175d4(void *arg)
{
    static Pmf tbl[] = {&Obj_020d8bd4::func_020176bc, &Obj_020d8bd4::func_02017674, &Obj_020d8bd4::func_02017654};
    unsigned char i = unk_98;
    if (i < 3) {
        (this->*(tbl[i]))(arg);
    }
}
